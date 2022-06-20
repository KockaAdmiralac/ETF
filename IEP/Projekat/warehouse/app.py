from csv import reader
from flask import Flask, request, Response
from flask_jwt_extended import JWTManager
from json import dumps
from redis import Redis
from shared.config import ShopConfiguration
from shared.errors import MissingField, ValidationError
from shared.shop_models import db
from shared.utils import check_is_warehouse
from tempfile import NamedTemporaryFile

app = Flask(__name__)
app.config.from_object(ShopConfiguration)
jwt = JWTManager(app)

@app.route('/update', methods=['POST'])
@check_is_warehouse()
def update():
    if not request.files or not 'file' in request.files:
        raise MissingField('file')
    values: list[str] = []
    with NamedTemporaryFile(suffix='.csv') as tf:
        request.files['file'].save(tf.name)
        with open(tf.name) as f:
            csv_file = reader(f)
            for index, row in enumerate(csv_file):
                if len(row) != 4:
                    raise ValidationError(f'Incorrect number of values on line {index}.')
                categories = row[0].split('|')
                name = row[1]
                quantity = 0
                price = 0.0
                try:
                    quantity = int(row[2])
                    price = float(row[3])
                except ValueError:
                    # Error reporting happens below
                    pass
                if quantity <= 0:
                    raise ValidationError(f'Incorrect quantity on line {index}.')
                if price <= 0:
                    raise ValidationError(f'Incorrect price on line {index}.')
                values.append(dumps({
                    'name': name,
                    'quantity': quantity,
                    'price': price,
                    'categories': categories
                }))
    with Redis(app.config['REDIS_HOST']) as client:
        client.rpush('products', *values)
    return Response(status=200)

if __name__ == '__main__':
    db.init_app(app)
    app.run('0.0.0.0', 5002, debug=True)
