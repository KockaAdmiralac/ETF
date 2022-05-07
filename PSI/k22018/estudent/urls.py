from django.urls import path, include
from .views import index, student, nastavnik

urlpatterns = [
    path('', index, name='index'),
    path('student/', student, name='student'),
    path('nastavnik/', nastavnik, name='nastavnik')
]
