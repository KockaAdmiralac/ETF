from flask import Flask
from json import loads
from redis import Redis
from redis.exceptions import ConnectionError
from shared.config import ShopConfiguration
from shared.shop_models import Category, ProductCategories, db, Product
from time import sleep

app = Flask(__name__)
app.config.from_object(ShopConfiguration)

def process(product: dict):
    print('Processing product', product, flush=True)
    name, price, quantity, categories = product['name'], product['price'], product['quantity'], product['categories']
    p = Product.query.filter_by(name=name).first()
    if not p:
        print('Inserting product', flush=True)
        p = Product(name=name, price=price, quantity=quantity)
        db.session.add(p)
        db.session.commit()
        for category in categories:
            c = Category.query.filter_by(name=category).first()
            if not c:
                c = Category(name=category)
                db.session.add(c)
                db.session.commit()
            db.session.add(ProductCategories(product_id=p.id, category_id=c.id))
            db.session.commit()
        print('Inserted product', flush=True)
    else:
        print('Updating product', p.price, p.quantity, flush=True)
        current_categories = [c.name for c in p.categories]
        print('Categories comparison:', current_categories, categories, flush=True)
        if set(current_categories) != set(categories):
            print('Rejecting product as invalid.', flush=True)
            return
        # Price calculation formula
        current_quantity = p.quantity
        current_price = p.price
        delivery_quantity = quantity
        delivery_price = price
        new_price = (current_quantity * current_price + delivery_quantity * delivery_price) / (current_quantity + delivery_quantity)
        p.price = new_price
        p.quantity += quantity
        db.session.commit()
        print('Product updated', p.price, p.quantity, flush=True)
        for po in p.orders:
            if po.received == po.requested:
                continue
            sold = min(p.quantity, po.requested - po.received)
            print('Selling', sold, 'products for order', po.order_id, flush=True)
            po.received += sold
            if po.received == po.requested:
                order = po.order
                for order_product in order.products:
                    if order_product.received < order_product.requested:
                        break
                else:
                    print('Order complete', flush=True)
                    order.status = 'COMPLETE'
            p.quantity -= sold
            db.session.commit()
            if p.quantity == 0:
                break

if __name__ == '__main__':
    db.init_app(app)
    connecting_to_redis = True
    while connecting_to_redis:
        try:
            with Redis(app.config['REDIS_HOST']) as redis:
                redis.ping()
                print('Connected to Redis.', flush=True)
                connecting_to_redis = False
                while True:
                    with app.app_context():
                        _, jsonb = redis.blpop('products', 0)
                        process(loads(jsonb))
        except ConnectionError:
            connecting_to_redis = True
            print('Redis not started, waiting...', flush=True)
            sleep(5)
