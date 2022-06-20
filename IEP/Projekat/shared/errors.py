from flask import Response, jsonify
from json import dumps
from werkzeug.exceptions import BadRequest

class MissingField(BadRequest):
    def __init__(self, field: str):
        self.field: str = field

    def get_response(self, *args, **kwargs) -> Response:
        r = Response(dumps({
            'message': f'Field {self.field} is missing.'
        }), status=400)
        r.content_type = 'application/json'
        return r

class MissingAuthorizationHeader(BadRequest):
    def get_response(self, *args, **kwargs) -> Response:
        r = Response(dumps({
            'msg': 'Missing Authorization Header'
        }), status=401)
        r.content_type = 'application/json'
        return r

class ValidationError(BadRequest):
    def __init__(self, message: str):
        self.message: str = message

    def get_response(self, *args, **kwargs) -> Response:
        r = Response(dumps({
            'message': self.message
        }), status=400)
        r.content_type = 'application/json'
        return r
