# Jun 2019
## 1. zadatak
Distribuiranim računarskim sistemom se smatra računarski sistem u kom učestvuju više procesora koji komuniciraju preko mreže i svaki od njih ima svoju operativnu memoriju. Primer ovakvog sistema bi bili LAN i WAN mreže.

## 2. zadatak
U `dispatch()` se koristi:
```cpp
if (setjmp(running->context) == 0) {
    Scheduler::put(running);
    running = Scheduler::get();
    longjmp(running->context, 1);
}
```
tako da `Event::signal()` izgleda nešto poput:
```cpp
if (blocked) {
    Scheduler::put(blocked);
    blocked = 0;
    // dispatch();
}
```

## 3. zadatak
```cpp
int thread_create (void(*fun)(void*), void* arg);

struct SumContext {
    int* array;
    size_t size;
    long* result;
};

void wrapper(void* context) {
    SumContext* ctx = (SumContext*) context;
    long result = 0;
    for (size_t i = 0; i < ctx->size; ++i) {
        result += ctx->array[i];
    }
    *ctx->result = result;
    delete context;
}

int sum(int array[], size_t size, long* result) {
    SumContext* context = new SumContext;
    context->array = array;
    context->size = size;
    context->result = result;
    return thread_create(wrapper, context);
}
```

## 4. zadatak
Isto kao svi prethodni zadaci iz ovoga.

## 5. zadatak
Dynamic Link Library (DLL) je format fajla sa izvršnim kodom koji se učitava u program prilikom njegovog pokretanja nakon što se pročita iz fajl sistema, za razliku od statičkih biblioteka čiji se sadržaj ugrađuje u sam kod programa. Osnovni motiv za njegovo korišćenje je to da više procesa može da koristi isti kod iz istog fajla umesto da svaki drži svoju kopiju tog koda. Ovo daje više prednosti:
1. Može da se ažurira DLL odvojeno od samih programa koji ga koriste, u slučaju bagova pri implementaciji (u suprotnom bi svaki program morao odvojeno da se ažurira)
2. Operativni sistem može čuva jednu kopiju ovog koda u operativnoj memoriji i da mehanizmom virtuelne memorije koristi tu kopiju u svim procesima u kojima je potrebna
3. Smanjuje se zauzeće izvršnih programa na disku

## 6. zadatak
Problemi kontinualne alokacije memorije su interna i eksterna fragmentacija, koji se odnose na to da pri alociranju ostaju previše mali segmenti memorije nealocirani koji se ne mogu nizašta iskoristiti. Interna fragmentacija jeste kada se ti fragmenti nalaze unutar memorijskog prostora jednog procesa, dok je eksterna kada se ti fragmenti nalaze van procesa.

## 7. zadatak
Proces je pokušao da pristupi memoriji za koju nije pozvao odgovarajući sistemski poziv kako bi mu se obezbedila alokacija, ili mu je taj zahtev odbijen. Takođe je moguće da se ovo desi prilikom dereferenciranja pokazivača na *null* u nekim operativnim sistemima.

## 8. zadatak
Sinhroni poziv usluge je onaj koji blokira proces od daljeg izvršavanja dok se ulazno/izlazna operacija ne završi u potpunosti, i ne dozvoljava korisniku da radi nešto drugo u svom programu tom prilikom. Asinhroni poziv usluge je onaj koji odmah vraća kontrolu pozivaocu, pa on može da odluči kada da reaguje na rezultat tog poziva.

## 9. zadatak
1. Ne
2. Da

## 10. zadatak
1. Indeks se može ulančati u više blokova
2. Indeks se može organizovati u više nivoa
