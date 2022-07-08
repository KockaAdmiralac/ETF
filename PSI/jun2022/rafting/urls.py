from django.urls import path
from .views import index, review

urlpatterns = [
    path('', index, name='index'),
    path('review', review, name='review')
]
