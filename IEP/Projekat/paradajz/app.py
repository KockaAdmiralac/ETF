from flask import Flask
from flask_migrate import Migrate, init, migrate, upgrade
from shared.auth_models import db, Role, User
from shared.config import AuthenticationConfiguration
from sqlalchemy.exc import OperationalError
from sqlalchemy_utils import database_exists, create_database
from sys import exit
from time import sleep

app = Flask(__name__)
app.config.from_object(AuthenticationConfiguration)
migrateObject = Migrate(app, db)

connecting_to_db = True

while connecting_to_db:
    try:
        if not database_exists(app.config['SQLALCHEMY_DATABASE_URI']):
            create_database(app.config['SQLALCHEMY_DATABASE_URI'])
        else:
            print('Database already exists')
            exit(0)

        connecting_to_db = False
        db.init_app(app)

        with app.app_context() as context:
            print('Database initialization started', flush=True)
            # Database migration
            init()
            migrate(message='Initial migration')
            upgrade()
            # Initial roles
            adminRole = Role(name='admin')
            userRole = Role(name='user')
            warehouseRole = Role(name='warehouse')
            db.session.add(adminRole)
            db.session.add(userRole)
            db.session.add(warehouseRole)
            db.session.commit()
            # Admin user
            admin = User(email='admin@admin.com', password='1', forename='admin', surname='admin', role=adminRole.id)
            db.session.add(admin)
            db.session.commit()
            print('Initialization complete.', flush=True)
    except OperationalError as error:
        if '2003' in str(error):
            connecting_to_db = True
            print('Database not started yet, waiting...', flush=True)
            sleep(5)
        else:
            raise error
