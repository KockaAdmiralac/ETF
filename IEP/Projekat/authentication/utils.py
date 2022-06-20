from re import match
from shared.errors import ValidationError

def validate_email(email: str):
    if not match(r'[^@]+@[^@]+\.[^@]{2,}', email):
        raise ValidationError('Invalid email.')
