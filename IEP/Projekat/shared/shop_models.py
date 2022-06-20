from flask_sqlalchemy import SQLAlchemy
from sqlalchemy.sql import func

db = SQLAlchemy()

class ProductCategories(db.Model):
    __tablename__ = 'product_categories'
    id = db.Column(db.Integer, primary_key=True)
    product_id = db.Column(db.Integer, db.ForeignKey('product.id'), nullable=False)
    category_id = db.Column(db.Integer, db.ForeignKey('category.id'), nullable=False)

class Category(db.Model):
    __tablename__ = 'category'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(256), nullable=False, unique=True)
    products = db.relationship('Product', secondary=ProductCategories.__table__, back_populates='categories')

class Product(db.Model):
    __tablename__ = 'product'
    id = db.Column(db.Integer, primary_key=True)
    categories = db.relationship('Category', secondary=ProductCategories.__table__, back_populates='products')
    name = db.Column(db.String(256), nullable=False)
    price = db.Column(db.Float, nullable=False)
    quantity = db.Column(db.Integer, nullable=False)
    orders = db.relationship('OrderProducts', back_populates='product')

class OrderProducts(db.Model):
    __tablename__ = 'order_products'
    id = db.Column(db.Integer, primary_key=True)
    order_id = db.Column(db.Integer, db.ForeignKey('order.id'), nullable=False)
    product_id = db.Column(db.Integer, db.ForeignKey('product.id'), nullable=False)
    product = db.relationship('Product', back_populates='orders')
    order = db.relationship('Order', back_populates='products')
    received = db.Column(db.Integer, nullable=False)
    requested = db.Column(db.Integer, nullable=False)
    price = db.Column(db.Float, nullable=False)

class Order(db.Model):
    __tablename__ = 'order'
    id = db.Column(db.Integer, primary_key=True)
    products = db.relationship('OrderProducts', back_populates='order')
    status = db.Column(db.String(256), nullable=False)
    price = db.Column(db.Float, nullable=False)
    user = db.Column(db.String(256), nullable=False)
    timestamp = db.Column(db.DateTime, server_default=func.now())
