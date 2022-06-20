from flask import Flask, request, jsonify
from flask_jwt_extended import JWTManager, get_jwt_identity
from sqlalchemy import and_
from shared.config import ShopConfiguration
from shared.errors import ValidationError
from shared.shop_models import Order, OrderProducts, Product, db, Category
from shared.utils import check_is_customer, require_field

app = Flask(__name__)
app.config.from_object(ShopConfiguration)
jwt = JWTManager(app)

@app.route('/search', methods=['GET'])
@check_is_customer()
def search():
    name = request.args.get('name', '')
    category = request.args.get('category', '')
    categories = Category.query.filter(and_(Category.name.contains(category), Category.products.any(Product.name.contains(name))))
    products = Product.query.filter(and_(Product.name.contains(name), Product.categories.any(Category.name.contains(category))))
    return jsonify(
        categories=[c.name for c in categories],
        products=[{
            'categories': [c.name for c in p.categories],
            'id': p.id,
            'name': p.name,
            'price': p.price,
            'quantity': p.quantity
        } for p in products]
    )

@app.route('/order', methods=['POST'])
@check_is_customer()
def order():
    requests = require_field(request, 'requests')
    processed_requests = []
    for number, r in enumerate(requests):
        if not 'id' in r:
            raise ValidationError(f'Product id is missing for request number {number}.')
        if not 'quantity' in r:
            raise ValidationError(f'Product quantity is missing for request number {number}.')
        if not isinstance(r['id'], int) or r['id'] <= 0:
            raise ValidationError(f'Invalid product id for request number {number}.')
        if not isinstance(r['quantity'], int) or r['quantity'] <= 0:
            raise ValidationError(f'Invalid product quantity for request number {number}.')
        product = Product.query.filter_by(id=r['id']).first()
        if not product:
            raise ValidationError(f'Invalid product for request number {number}.')
        processed_requests.append((product, r['quantity']))
    o = Order(status='COMPLETE', price=0.0, user=get_jwt_identity())
    db.session.add(o)
    db.session.commit()
    for p, quantity in processed_requests:
        o.price += quantity * p.price
        sold = min(p.quantity, quantity)
        p.quantity -= sold
        if sold != quantity:
            o.status = 'PENDING'
        op = OrderProducts(order_id=o.id, product_id=p.id, requested=quantity, received=sold, price=p.price)
        db.session.add(op)
        db.session.commit()
    return jsonify(id=o.id)

@app.route('/status', methods=['GET'])
@check_is_customer()
def status():
    return jsonify(orders=[{
        'products': [{
            'categories': [c.name for c in p.product.categories],
            'name': p.product.name,
            'price': p.price,
            'received': p.received,
            'requested': p.requested
        } for p in o.products],
        'price': o.price,
        'status': o.status,
        'timestamp': o.timestamp.isoformat()
    } for o in Order.query.filter_by(user=get_jwt_identity())])

if __name__ == '__main__':
    db.init_app(app)
    app.run('0.0.0.0', 5003, debug=True)

