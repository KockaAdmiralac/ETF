from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.contrib import messages
from django.contrib.auth import login, authenticate, logout
from django.contrib.auth.decorators import login_required
from django.contrib.auth.forms import AuthenticationForm
from .models import Trka, Sektor
from .forms import SektorForm

def index(request):
    auth_form = AuthenticationForm(request=request, data=request.POST or None)
    if auth_form.is_valid():
        user = authenticate(username=auth_form.cleaned_data['username'], password=auth_form.cleaned_data['password'])
        if user:
            login(request, user)
            messages.info(request, 'Login successful')
            return redirect('index:index')
    elif request.method == 'POST':
        messages.error(request, 'Login failed')
    return render(request, 'index/index.html', {
        'auth_form': auth_form,
        'trke': Trka.objects.all()
    })

@login_required(login_url='index')
def sektor(request, trka_id):
    form = SektorForm(trka_id, request.POST or None)
    if request.method == 'POST':
        if form.is_valid():
            return redirect('index:kupovina', trka_id, form.cleaned_data['sektor_id'])
        else:
            messages.error(request, 'Invalid form')
    return render(request, 'index/sektor.html', {
        'form': form
    })

@login_required(login_url='index')
def kupovina(request, trka_id, sektor_id):
    pass

@login_required(login_url='index')
def signout(request):
    logout(request)
    return redirect('index:index')
