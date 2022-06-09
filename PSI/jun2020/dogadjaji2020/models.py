# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models


class Dogadjaj(models.Model):
    id_dog = models.AutoField(primary_key=True)
    naziv = models.CharField(max_length=32)
    id_lokacije = models.ForeignKey('Lokacija', models.DO_NOTHING, db_column='id_lokacije')
    id_kategorije = models.ForeignKey('Kategorija', models.DO_NOTHING, db_column='id_kategorije')
    datum = models.DateField()
    vreme = models.TimeField()
    broj_interesenata = models.IntegerField()
    je_otkazan = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'dogadjaj'


class Grad(models.Model):
    ime_grada = models.CharField(primary_key=True, max_length=32)

    class Meta:
        managed = False
        db_table = 'grad'


class Kategorija(models.Model):
    naziv = models.CharField(primary_key=True, max_length=32)

    class Meta:
        managed = False
        db_table = 'kategorija'


class Lokacija(models.Model):
    naziv_lokacije = models.CharField(max_length=20)
    grad = models.ForeignKey(Grad, models.DO_NOTHING, db_column='grad')
    adresa = models.CharField(max_length=32)
    max_kapacitet = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'lokacija'
