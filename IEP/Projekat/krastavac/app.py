from flask import Flask
from flask_migrate import Migrate, init, migrate, upgrade
from shared.config import ShopConfiguration
from shared.shop_models import db
from sqlalchemy.exc import OperationalError
from sqlalchemy_utils import database_exists, create_database
from time import sleep

app = Flask(__name__)
app.config.from_object(ShopConfiguration)
migrateObject = Migrate(app, db)

connecting_to_db = True

while connecting_to_db:
    try:
        if not database_exists(app.config['SQLALCHEMY_DATABASE_URI']):
            create_database(app.config['SQLALCHEMY_DATABASE_URI'])

        db.init_app(app)
        connecting_to_db = False

        with app.app_context() as context:
            print('Database initialization started')
            init()
            migrate(message='Initial migration')
            upgrade()
            print('Initialization complete.')
    except OperationalError as error:
        if '2003' in str(error):
            connecting_to_db = True
            print('Database not started yet, waiting...', flush=True)
            sleep(5)
        else:
            raise error
