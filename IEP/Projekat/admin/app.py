from flask import Flask, jsonify
from flask_jwt_extended import JWTManager
from shared.config import ShopConfiguration
from shared.shop_models import OrderProducts, Product, db, Category
from shared.utils import check_is_admin
from sqlalchemy import desc, func

app = Flask(__name__)
app.config.from_object(ShopConfiguration)
jwt = JWTManager(app)

@app.route('/productStatistics', methods=['GET'])
@check_is_admin()
def product_statistics():
    return jsonify(statistics=[{
        'name': p.name,
        'sold': int(OrderProducts
            .query
            .with_entities(func.sum(OrderProducts.requested))
            .filter_by(product_id=p.id)
            .first()
            [0] or 0),
        'waiting': int(OrderProducts
            .query
            .with_entities(func.sum(OrderProducts.requested - OrderProducts.received))
            .filter_by(product_id=p.id)
            .first()
            [0] or 0)
    } for p in Product.query.filter(Product.orders.any()).all()])

@app.route('/categoryStatistics', methods=['GET'])
@check_is_admin()
def category_statistics():
    return jsonify(statistics=[t[0] for t in db.session
        .query(Category.name)
        .outerjoin(Category.products)
        .outerjoin(Product.orders)
        .order_by(desc(func.sum(OrderProducts.requested)), Category.name)
        .group_by(Category.id)
        .all()
    ])

if __name__ == '__main__':
    db.init_app(app)
    app.run('0.0.0.0', 5004, debug=True)
