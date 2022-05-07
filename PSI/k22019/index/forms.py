from django.forms import Form, fields
from .models import Sektor

class SektorForm(Form):
    def __init__(self, trka_id: int, *args, **kwargs):
        super(Form, self).__init__(*args, **kwargs)
        sektori = Sektor.objects.filter(idtrk=trka_id)
        choices = [(sektor.idsek, sektor.naziv) for sektor in sektori]
        self.fields['sektor_id'] = fields.ChoiceField(choices=choices, label='Sektor')
