from django.urls import path

from .views import index, encoding, guest_json, owner_json, telegram

urlpatterns = [
    path('', index, name='index'),
    path('encoding/<str:filename>/', encoding, name='encoding'),
    path('guest/json/<str:phone>/', guest_json, name='guest-json'),
    path('owner/json/<str:email>/', owner_json, name='owner-json'),
    path('telegram/', telegram, name='telegram')
]