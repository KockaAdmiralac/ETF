from .forms import IndexForm
from .models import CenovnikNocenja, DodatnaAktivnost, Prijava, RaftingPutanja
from django.contrib.messages import error, info
from django.db.models import Q
from django.http import HttpRequest, HttpResponse
from django.shortcuts import redirect, render

def index(request: HttpRequest) -> HttpResponse:
    if request.POST:
        form = IndexForm(request.POST)
    else:
        form = IndexForm(initial={
            'rafting_putanja': request.session.get('rafting_putanja'),
            'nosilac_prijave': request.session.get('nosilac_prijave'),
            'broj_nocenja': request.session.get('broj_nocenja'),
            'broj_gostiju': request.session.get('broj_gostiju'),
            'dodatne_aktivnosti': request.session.get('dodatne_aktivnosti')
        })
    if form.is_valid():
        rafting_putanja = form.cleaned_data['rafting_putanja']
        nosilac_prijave = form.cleaned_data['nosilac_prijave']
        broj_nocenja = form.cleaned_data['broj_nocenja']
        broj_gostiju = form.cleaned_data['broj_gostiju']
        dodatne_aktivnosti = form.cleaned_data['dodatne_aktivnosti']
        request.session['rafting_putanja'] = rafting_putanja
        request.session['nosilac_prijave'] = nosilac_prijave
        request.session['broj_nocenja'] = broj_nocenja
        request.session['broj_gostiju'] = broj_gostiju
        request.session['dodatne_aktivnosti'] = dodatne_aktivnosti
        if broj_nocenja < 1 + len(dodatne_aktivnosti):
            error(request, 'Noćenja mora biti barem onoliko koliko ima dodatnih aktivnosti, plus jedno noćenje za rafting.')
        else:
            cena_po_nocenju = CenovnikNocenja.objects.filter(
                Q(min_broj_nocenja__lte=broj_nocenja) &
                Q(max_broj_nocenja__gte=broj_nocenja)
            ).first().cena_po_nocenju
            cena_rafting_ture = RaftingPutanja.objects.get(naziv=rafting_putanja).cena
            ukupna_cena_dodatnih_aktivnosti = sum([DodatnaAktivnost.objects.get(naziv=aktivnost).cena for aktivnost in dodatne_aktivnosti])
            request.session['cena'] = broj_gostiju * (cena_rafting_ture + ukupna_cena_dodatnih_aktivnosti + broj_nocenja * cena_po_nocenju)
            return redirect('review')
    return render(request, 'index.html', {
        'form': form
    })

def review(request: HttpRequest) -> HttpResponse:
    if request.POST and request.POST['confirmed'] == '1':
        if 'cena' not in request.session:
            return redirect('index')
        prijava = Prijava()
        prijava.nosilac_prijave = request.session['nosilac_prijave']
        prijava.broj_nocenja = request.session['broj_nocenja']
        prijava.broj_gostiju = request.session['broj_gostiju']
        prijava.cena = request.session['cena']
        prijava.rafting_putanja = RaftingPutanja.objects.get(naziv=request.session['rafting_putanja'])
        prijava.save()
        for aktivnost in request.session['dodatne_aktivnosti']:
            prijava.obuhvata.add(DodatnaAktivnost.objects.get(naziv=aktivnost))
        prijava.save()
        request.session.clear()
        info(request, 'Prijava uspešna!')
        return redirect('index')
    return render(request, 'review.html', {
        'cena': request.session.get('cena', 0)
    })
