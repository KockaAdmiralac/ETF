from django.contrib import messages
from django.contrib.auth import authenticate, login
from django.contrib.auth.decorators import login_required
from django.contrib.auth.forms import AuthenticationForm
from django.http import HttpRequest, HttpResponseForbidden
from django.shortcuts import redirect, render
from django.db.models import Q
from .forms import PredmetSearchForm
from .models import Nastavnik, Predmet, Student

def index(request: HttpRequest):
    login_form = AuthenticationForm(request=request, data=request.POST or None)
    is_authenticated = request.user.is_authenticated
    if request.method == 'POST':
        if login_form.is_valid():
            user = authenticate(username=login_form.cleaned_data['username'], password=login_form.cleaned_data['password'])
            if user:
                login(request, user)
                is_authenticated = True
        else:
            messages.error('Greška!')
    if is_authenticated:
        if Nastavnik.objects.filter(id=request.user.id).exists():
            return redirect('nastavnik')
        else:
            return redirect('student')

    return render(request, 'estudent/index.html', {
        'login_form': login_form
    })

@login_required(login_url='index')
def student(request: HttpRequest):
    if not Student.objects.filter(id=request.user.id).exists():
        return HttpResponseForbidden('Pristup resursu je dozvoljen samo studentima.')
    search_form = PredmetSearchForm(request.GET)
    naziv = search_form.data.get('naziv', '')
    tip_predmeta = search_form.data.get('tip_predmeta', '')
    predmeti = []
    if search_form.is_valid():
        if naziv != '' and tip_predmeta != '':
            predmeti = Predmet.objects.filter(Q(naziv__contains=naziv) & Q(tip=tip_predmeta))
        elif naziv != '':
            predmeti = Predmet.objects.filter(naziv__contains=naziv)
        elif tip_predmeta != '':
            predmeti = Predmet.objects.filter(tip=tip_predmeta)
        else:
            predmeti = Predmet.objects.all()
    return render(request, 'estudent/student.html', {
        'predmeti': predmeti,
        'search_form': search_form,
        'student': Student.objects.get(id=request.user.id)
    })

@login_required(login_url='index')
def nastavnik(request: HttpRequest):
    if not Nastavnik.objects.filter(id=request.user.id).exists():
        return HttpResponseForbidden('Pristup resursu je dozvoljen samo nastavnicima.')
    return render(request, 'estudent/nastavnik.html', {
        #
    })
