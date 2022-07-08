import datetime

from rafting.models import *


def init():
    putanje = []
    putanje.append(RaftingPutanja(
        naziv="Gornji tok reke tare",
        cena=35
    ))
    putanje.append(RaftingPutanja(
        naziv="Donji tok reke tare",
        cena=30
    ))
    putanje.append(RaftingPutanja(
        naziv="Tara i Drina",
        cena=50
    ))
    [x.save() for x in putanje]

    dodatne_aktivnosti = []
    dodatne_aktivnosti.append(DodatnaAktivnost(
        naziv="Pesacka tura",
        cena=20
    ))
    dodatne_aktivnosti.append(DodatnaAktivnost(
        naziv="Jeep safari",
        cena=35
    ))
    dodatne_aktivnosti.append(DodatnaAktivnost(
        naziv="Kanjoning",
        cena=40
    ))
    dodatne_aktivnosti.append(DodatnaAktivnost(
        naziv="Voznja kvadovima",
        cena=50
    ))
    [x.save() for x in dodatne_aktivnosti]

    cenovnik = []
    cenovnik.append(CenovnikNocenja(
        min_broj_nocenja=1,
        max_broj_nocenja=2,
        cena_po_nocenju=25
    ))
    cenovnik.append(CenovnikNocenja(
        min_broj_nocenja=3,
        max_broj_nocenja=4,
        cena_po_nocenju=20
    ))
    cenovnik.append(CenovnikNocenja(
        min_broj_nocenja=5,
        max_broj_nocenja=20,
        cena_po_nocenju=18
    ))
    [x.save() for x in cenovnik]

    prijave = []
    prijave.append(Prijava(
        nosilac_prijave='tasha',
        broj_nocenja=3,
        broj_gostiju=4,
        cena=800,
        rafting_putanja=putanje[2],
    ))
    [x.save() for x in prijave]
    prijave[0].obuhvata.add(dodatne_aktivnosti[2])
    prijave[0].obuhvata.add(dodatne_aktivnosti[3])

    print("Success")
