from csv import DictWriter
import os

ESPB = {}
with open('ESPB.csv', encoding='utf-8') as f:
    for line in f:
        stripped = line.strip()
        if stripped == '':
            continue
        predmet, bodova = stripped.split(';')
        ESPB[predmet] = int(bodova)
        

# Read all grades.
csv_filenames = sorted([file for file in os.listdir('data') if file[-4:] == '.csv'])
studenti = {}
predmeti = set()
for filename in csv_filenames:
    predmet, rok= filename[:-4].split('-')
    predmeti.add(predmet)
    with open(f'data/{filename}', 'r', encoding='utf-8') as file:
        for line in file:
            linija = line.strip()
            if linija == '':
                continue
            indeks, ocena = linija.split(';')
            if ocena == '' or int(ocena) <= 5:
                continue
            if not indeks in studenti:
                studenti[indeks] = {}
            studenti[indeks][predmet] = (int(ocena), int(rok), int(int(ocena) * ESPB[predmet] * 1.1 if int(rok) < 3 else 1))

# Generate table data.
table = []
columns = ['Indeks', 'Ime'] + list(predmeti) + ['Suma', 'Prosek']
with open('imena.csv', encoding='utf-8') as f:
    for line in f:
        stripped = line.strip()
        if stripped == '':
            continue
        indeks, ime = stripped.split(';')
        student = {
            'Indeks': indeks,
            'Ime': ime
        }
        student['Suma'] = 0
        student['Prosek'] = 0
        if indeks in studenti:
            for predmet, ocena in studenti[indeks].items():
                student[predmet] = ocena[0]
                student['Prosek'] += ocena[0]
                student['Suma'] += ocena[2]
        student['Prosek'] = student["Prosek"] / len(studenti[indeks].items()) if len(studenti[indeks].items())>5 else 0
        table.append(student)

table.sort(key = lambda x : x['Prosek'], reverse = True)

# Write table to file.
with open('rezultati.csv', 'w', encoding='utf-8', newline='') as rezultati:
    writer = DictWriter(rezultati, fieldnames=columns, delimiter=';')
    writer.writeheader()
    for data in table:
        writer.writerow(data)
