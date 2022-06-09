from django.urls import path
from .views import index, details

urlpatterns = [
    path('', index, name='index'),
    path('<int:id_dog>', details, name='details')
]
