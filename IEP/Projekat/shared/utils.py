from functools import wraps
from flask_jwt_extended import get_jwt, verify_jwt_in_request
from shared.errors import MissingAuthorizationHeader, MissingField

def require_field(request, field: str):
    value = request.json.get(field, '')
    if value == '':
        raise MissingField(field)
    return value

def check_role(role: str):
    def inner_func(func):
        @wraps(func)
        def decorator(*args, **kwargs):
            verify_jwt_in_request()
            claims = get_jwt()
            if 'roles' not in claims or not isinstance(claims['roles'], list) or role not in claims['roles']:
                raise MissingAuthorizationHeader()
            return func(*args, **kwargs)
        return decorator
    return inner_func

def check_is_admin():
    return check_role('admin')

def check_is_customer():
    return check_role('user')

def check_is_warehouse():
    return check_role('warehouse')
