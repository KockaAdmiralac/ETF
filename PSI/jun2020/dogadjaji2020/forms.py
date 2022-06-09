from django.forms import Form, fields, RadioSelect
from .models import Grad, Kategorija

class SearchForm(Form):
    naziv = fields.CharField(required=False)
    otkazan = fields.BooleanField(required=False)

    def __init__(self, *args, **kwargs):
        super(Form, self).__init__(*args, **kwargs)
        self.fields['grad'] = fields.ChoiceField(choices=[('', 'Izaberite grad...')] + [(grad.ime_grada, grad.ime_grada) for grad in Grad.objects.all()], required=False)
        self.fields['kategorija'] = fields.ChoiceField(choices=[(kategorija.naziv, kategorija.naziv) for kategorija in Kategorija.objects.all()], required=False, widget=RadioSelect)
