# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models
from django.contrib.auth.models import AbstractUser


class DrziPredmet(models.Model):
    nastavnik_id = models.ForeignKey('Nastavnik', models.DO_NOTHING, db_column='id')
    sifrapredmet = models.ForeignKey('Predmet', models.DO_NOTHING, db_column='sifrapredmet')

    class Meta:
        db_table = 'drzi_predmet'
        unique_together = (('nastavnik_id', 'sifrapredmet'),)


class Korisnik(AbstractUser):
    class Meta:
        db_table = 'korisnik'


class Nastavnik(models.Model):
    id = models.OneToOneField(Korisnik, on_delete=models.CASCADE, primary_key=True, db_column='id')
    titula = models.CharField(max_length=5)
    zvanje = models.CharField(max_length=32)

    class Meta:
        db_table = 'nastavnik'


class Polaganje(models.Model):
    idprijave = models.AutoField(primary_key=True)
    user_student = models.ForeignKey('Student', models.DO_NOTHING, db_column='user_student')
    user_nastavnik = models.ForeignKey(Nastavnik, models.DO_NOTHING, db_column='user_nastavnik')
    sifra_predmet = models.ForeignKey('Predmet', models.DO_NOTHING, db_column='sifra_predmet')
    datum_unosa = models.DateField()
    ocena = models.IntegerField()
    ponistio = models.IntegerField()

    class Meta:
        db_table = 'polaganje'


class Predmet(models.Model):
    sifra = models.CharField(primary_key=True, max_length=16)
    naziv = models.CharField(max_length=255)
    espb = models.IntegerField(db_column='ESPB')  # Field name made lowercase.
    tip = models.CharField(max_length=1)
    semestar = models.IntegerField()

    def get_tip(self):
        return self.tip == 'i' and 'Izborni' or 'Obavezni'

    class Meta:
        db_table = 'predmet'


class SlusaPredmet(models.Model):
    student_id = models.ForeignKey(Korisnik, models.DO_NOTHING, db_column='id')
    sifrapredmet = models.ForeignKey(Predmet, models.DO_NOTHING, db_column='sifrapredmet')

    class Meta:
        db_table = 'slusa_predmet'
        unique_together = (('student_id', 'sifrapredmet'),)


class Student(models.Model):
    id = models.OneToOneField(Korisnik, on_delete=models.CASCADE, primary_key=True, db_column='id')
    godina_upisa = models.IntegerField()
    broj_indeksa = models.IntegerField()
    odsek = models.CharField(max_length=32)

    class Meta:
        db_table = 'student'
