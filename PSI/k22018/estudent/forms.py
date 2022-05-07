from django.forms import fields, Form

class PredmetSearchForm(Form):
    naziv = fields.CharField(required=False)
    tip_predmeta = fields.ChoiceField(choices=[
        ('', '---'),
        ('o', 'Obavezni'),
        ('i', 'Izborni')
    ], required=False)
