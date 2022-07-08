from django.db import models

class RaftingPutanja(models.Model):
    naziv = models.CharField(max_length=100)
    cena = models.IntegerField()

    class Meta:
        db_table = 'RaftingPutanja'

class DodatnaAktivnost(models.Model):
    naziv = models.CharField(max_length=100)
    cena = models.IntegerField()

    class Meta:
        db_table = 'DodatnaAktivnost'

class Prijava(models.Model):
    nosilac_prijave = models.CharField(max_length=100)
    broj_nocenja = models.IntegerField()
    broj_gostiju = models.IntegerField()
    cena = models.IntegerField()
    rafting_putanja = models.ForeignKey(RaftingPutanja, on_delete=models.CASCADE)

    obuhvata = models.ManyToManyField(DodatnaAktivnost)

    class Meta:
        db_table = 'Prijava'

class CenovnikNocenja(models.Model):
    min_broj_nocenja = models.IntegerField()
    max_broj_nocenja = models.IntegerField()
    cena_po_nocenju = models.IntegerField()

    class Meta:
        db_table = 'CenovnikNocenja'
