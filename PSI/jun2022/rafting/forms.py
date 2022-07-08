from django.forms import CheckboxSelectMultiple, Form, fields
from .models import DodatnaAktivnost, RaftingPutanja

class IndexForm(Form):
    rafting_putanja = fields.ChoiceField(choices=[(p.naziv, p.naziv) for p in RaftingPutanja.objects.all()])
    nosilac_prijave = fields.CharField(max_length=100)
    broj_nocenja = fields.IntegerField(min_value=1)
    broj_gostiju = fields.IntegerField(min_value=2, max_value=10)
    dodatne_aktivnosti = fields.MultipleChoiceField(choices=[(a.naziv, a.naziv) for a in DodatnaAktivnost.objects.all()],
        widget=CheckboxSelectMultiple, required=False)
