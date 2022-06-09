from django.shortcuts import render
from django.http import HttpRequest, HttpResponse

from .models import Dogadjaj
from .forms import SearchForm
from django.contrib import messages
from django.db.models import Q
from random import randrange

def index(request: HttpRequest) -> HttpResponse:
    form = SearchForm(request.GET)
    highlight_otkazani = True
    events = None
    if form.is_valid() and request.GET:
        naziv = form.cleaned_data['naziv']
        otkazan = form.cleaned_data['otkazan']
        grad = form.cleaned_data['grad']
        kategorija = form.cleaned_data['kategorija']
        if naziv == '' and not otkazan and grad == '' and kategorija == '':
            messages.error(request, 'Morate uneti bar jedan kriterijum pretraživanja.')
        else:
            query = Q()
            if otkazan:
                query = Q(je_otkazan=True)
                highlight_otkazani = False
            if naziv != '':
                query = query & Q(naziv__icontains=naziv)
            if grad != '':
                query = query & Q(id_lokacije__grad__ime_grada=grad)
            if kategorija != '':
                query = query & Q(id_kategorije__naziv=kategorija)
            events = Dogadjaj.objects.filter(query).all()
    return render(request, 'index.html', {
        'form': form,
        'events': events,
        'highlight_otkazani': highlight_otkazani
    })

def ocena():
    return randrange(100, 500) / 100

def details(request: HttpRequest, id_dog: int) -> HttpResponse:
    return render(request, 'details.html', {
        'event': Dogadjaj.objects.filter(id_dog=id_dog).first(),
        'ocena': ocena
    })

