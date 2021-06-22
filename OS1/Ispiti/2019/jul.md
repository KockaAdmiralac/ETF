# Jul 2019
## 1. zadatak
Multiprocesorski računarski sistem je sistem u kojem učestvuju više procesora koji dele istu operativnu memoriju. Simetričan multiprocesorski računarski sistem jeste računarski sistem u kom ne postoje procesori koji su gazda i sluga, već su svi ravnopravni.

## 2. zadatak

## 3. zadatak
Isto kao u junu.

## 4. zadatak

## 5. zadatak
Zato što je dovlačenje i upisivanje na disk pri svakoj promeni konteksta jako neefikasno - ta memorija je spora.

## 6. zadatak
Kada se svi segmenti alocirane memorije pomere da budu jedan za drugim umesto rasprostranjeni po memorijskom prostoru.

## 7. zadatak
VA(32): Page(21) Offset(11)

## 8. zadatak
...

## 9. zadatak

## 10. zadatak
```cpp
const unsigned long FAT_SIZE = ...;
unsigned long FAT[FAT_SIZE];

void truncate(FCB* file) {
    for (unsigned long i = 0; i < file->size; ++i) {
        unsigned long next = FAT[b];
        FAT[b] = 0;
        // ?? Na šta pokazuje fat_free_head kad nema slobodnih blokova
        if (fat_free_tail) {
            FAT[fat_free_tail] = b;
            fat_free_tail = b;
        } else {
            fat_free_head = b;
            fat_free_tail = b;
        }
        b = next;
    }
    file->size = 0;
    file->head = 0;
}
```
