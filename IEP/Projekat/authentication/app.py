from authentication.utils import validate_email
from flask import Flask, request, Response, jsonify
from flask_jwt_extended import JWTManager, create_access_token, jwt_required, create_refresh_token, get_jwt, get_jwt_identity
from re import search
from shared.auth_models import db, User, Role
from shared.config import AuthenticationConfiguration
from shared.errors import ValidationError
from shared.utils import check_is_admin, require_field

app = Flask(__name__)
app.config.from_object(AuthenticationConfiguration)
jwt = JWTManager(app)

@app.route('/register', methods=['POST'])
def register():
    # Field presence validation
    forename = require_field(request, 'forename')
    surname = require_field(request, 'surname')
    email = require_field(request, 'email')
    password = require_field(request, 'password')
    is_customer = require_field(request, 'isCustomer')
    # Email validation
    validate_email(email)
    # Password validation
    if len(password) < 8 or len(password) > 256 or search(r'\d', password) is None or search(r'[A-Z]', password) is None or search(r'[a-z]', password) is None:
        raise ValidationError('Invalid password.')
    # Uniqueness
    if User.query.filter_by(email=email).first():
        raise ValidationError('Email already exists.')
    # Insert
    role_id = 2 if is_customer else 3
    user = User(email=email, password=password, forename=forename, surname=surname, role=role_id)
    db.session.add(user)
    db.session.commit()
    # Respond
    return Response(status=200)

@app.route('/login', methods=['POST'])
def login():
    # Field presence validation
    email = require_field(request, 'email')
    password = require_field(request, 'password')
    # Email validation
    validate_email(email)
    # Credential validation
    user = User.query.filter_by(email=email, password=password).first()
    if not user:
        raise ValidationError('Invalid credentials.')
    # Logging in
    claims = {
        'forename': user.forename,
        'surname': user.surname,
        'roles': [Role.query.filter_by(id=user.role).first().name]
    }
    return jsonify(
        accessToken = create_access_token(identity=user.email, additional_claims=claims),
        refreshToken = create_refresh_token(identity=user.email, additional_claims=claims)
    )

@app.route('/refresh', methods=['POST'])
@jwt_required(refresh=True)
def refresh():
    identity = get_jwt_identity()
    refreshClaims = get_jwt()
    claims = {
        'forename': refreshClaims['forename'],
        'surname': refreshClaims['surname'],
        'roles': refreshClaims['roles']
    }
    return jsonify(accessToken=create_access_token(identity=identity, additional_claims=claims))

@app.route('/delete', methods=['POST'])
@check_is_admin()
def delete():
    # Field presence validation
    email = require_field(request, 'email')
    # Email validation
    validate_email(email)
    # Existence
    user = User.query.filter_by(email=email).first()
    if not user:
        raise ValidationError('Unknown user.')
    # Deletion
    db.session.delete(user)
    db.session.commit()
    return Response(status=200)

if __name__ == '__main__':
    db.init_app(app)
    app.run('0.0.0.0', 5001, debug=True)
