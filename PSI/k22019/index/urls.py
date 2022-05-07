from django.urls import path

from . import views

app_name = 'index'
urlpatterns = [
    path('', views.index, name='index'),
    path('trka/<int:trka_id>', views.sektor, name='sektor'),
    path('trka/<int:trka_id>/<int:sektor_id>', views.kupovina, name='kupovina'),
    path('logout', views.signout, name='logout')
]
