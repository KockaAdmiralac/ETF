# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models
from django.contrib.auth.models import AbstractUser


class Drzava(models.Model):
    iddrz = models.AutoField(db_column='IdDrz', primary_key=True)  # Field name made lowercase.
    naziv = models.CharField(db_column='Naziv', max_length=45)  # Field name made lowercase.

    class Meta:
        db_table = 'Drzava'


class Karta(models.Model):
    idkar = models.AutoField(db_column='idKar', primary_key=True)  # Field name made lowercase.
    idsek = models.ForeignKey('Sektor', models.DO_NOTHING, db_column='IdSek')  # Field name made lowercase.
    username = models.ForeignKey('Korisnik', models.DO_NOTHING, db_column='Username')  # Field name made lowercase.
    broj_karata = models.IntegerField(db_column='Broj_karata', blank=True, null=True)  # Field name made lowercase.

    class Meta:
        db_table = 'Karta'


class Korisnik(AbstractUser):
    godina_rodjenja = models.IntegerField(db_column='Godina_rodjenja', null=True)  # Field name made lowercase.

class Rezultat(models.Model):
    idrez = models.AutoField(db_column='IdRez', primary_key=True)  # Field name made lowercase.
    ukupno_vreme = models.TimeField(db_column='Ukupno_vreme')  # Field name made lowercase.
    najbrzi_krug = models.TimeField(db_column='Najbrzi_krug')  # Field name made lowercase.
    broj_poena = models.IntegerField(db_column='Broj_poena')  # Field name made lowercase.
    vozac_broj = models.ForeignKey('Vozac', models.DO_NOTHING, db_column='Vozac_Broj')  # Field name made lowercase.
    idtrk = models.ForeignKey('Trka', models.DO_NOTHING, db_column='IdTrk')  # Field name made lowercase.

    class Meta:
        db_table = 'Rezultat'


class Sektor(models.Model):
    idsek = models.AutoField(db_column='IdSek', primary_key=True)  # Field name made lowercase.
    naziv = models.CharField(db_column='Naziv', max_length=45, blank=True, null=True)  # Field name made lowercase.
    broj_redova = models.IntegerField(db_column='Broj_redova', blank=True, null=True)  # Field name made lowercase.
    broj_sedista = models.IntegerField(db_column='Broj_sedista', blank=True, null=True)  # Field name made lowercase.
    cena = models.IntegerField(db_column='Cena', blank=True, null=True)  # Field name made lowercase.
    idtrk = models.ForeignKey('Trka', models.DO_NOTHING, db_column='IdTrk')  # Field name made lowercase.

    class Meta:
        db_table = 'Sektor'


class Staza(models.Model):
    naziv = models.CharField(db_column='Naziv', primary_key=True, max_length=45)  # Field name made lowercase.
    godina_otvaranja = models.IntegerField(db_column='Godina_otvaranja')  # Field name made lowercase.
    duzina = models.IntegerField(db_column='Duzina')  # Field name made lowercase.
    max_broj_posetilaca = models.IntegerField(db_column='Max_broj_posetilaca', blank=True, null=True)  # Field name made lowercase.
    adresa = models.CharField(db_column='Adresa', max_length=45)  # Field name made lowercase.

    class Meta:
        db_table = 'Staza'


class Tim(models.Model):
    idtim = models.AutoField(db_column='IdTim', primary_key=True)  # Field name made lowercase.
    naziv = models.CharField(db_column='Naziv', max_length=45, blank=True, null=True)  # Field name made lowercase.

    class Meta:
        db_table = 'Tim'


class TipKarte(models.Model):
    kategorija = models.CharField(db_column='Kategorija', primary_key=True, max_length=1)  # Field name made lowercase.
    idsek = models.ForeignKey(Sektor, models.DO_NOTHING, db_column='IdSek')  # Field name made lowercase.

    class Meta:
        db_table = 'Tip_karte'
        unique_together = (('kategorija', 'idsek'),)


class Trka(models.Model):
    idtrk = models.AutoField(db_column='IdTrk', primary_key=True)  # Field name made lowercase.
    naziv = models.CharField(db_column='Naziv', max_length=45)  # Field name made lowercase.
    staza = models.ForeignKey(Staza, models.DO_NOTHING, db_column='Staza')  # Field name made lowercase.
    broj_krugova = models.IntegerField(db_column='Broj_krugova')  # Field name made lowercase.
    datum = models.DateField(db_column='Datum')  # Field name made lowercase.

    class Meta:
        db_table = 'Trka'


class Vozac(models.Model):
    broj = models.IntegerField(db_column='Broj', primary_key=True)  # Field name made lowercase.
    ime = models.CharField(db_column='Ime', max_length=45)  # Field name made lowercase.
    prezime = models.CharField(db_column='Prezime', max_length=45)  # Field name made lowercase.
    godina_rodjenja = models.IntegerField(db_column='Godina_rodjenja')  # Field name made lowercase.
    iddrz = models.ForeignKey(Drzava, models.DO_NOTHING, db_column='IdDrz')  # Field name made lowercase.
    idtim = models.ForeignKey(Tim, models.DO_NOTHING, db_column='IdTim')  # Field name made lowercase.

    class Meta:
        db_table = 'Vozac'
