class Configuration:
    REDIS_HOST = 'redis'
    JWT_SECRET_KEY = 'zaki@etf.bg.ac.rs'
    JWT_ACCESS_TOKEN_EXPIRES = 60 * 60
    JWT_REFRESH_TOKEN_EXPIRES = 30 * 24 * 60 * 60
    UPLOAD_FOLDER = '/tmp'

class AuthenticationConfiguration(Configuration):
    SQLALCHEMY_DATABASE_URI = 'mysql+pymysql://root:root@auth_db/auth'

class ShopConfiguration(Configuration):
    SQLALCHEMY_DATABASE_URI = 'mysql+pymysql://root:root@shop_db/shop'
