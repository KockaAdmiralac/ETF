! inicijalizacija simulacije
dc x.1, x.9996
dc x.0, x.9998
onkp false, x.1, x.1
onkp false, x.1, x.1
onkp true, x.1, x.1
ondma x.1, x.1
ondma x.1, x.1
ondma x.1, x.1
ondma x.1, x.1
kpreg 1.1, r0, x.1
kpreg 1.1, r1, x.2
kpreg 1.1, r2, x.3
kpreg 1.1, r3, x.4
kpreg 1.1, r4, x.5
kpreg 1.1, r5, x.6
kpreg 1.1, r6, x.7
kpreg 1.1, r7, x.8
kpreg 2.1, r0, x.9
kpreg 2.1, r1, x.a
kpreg 2.1, r2, x.b
kpreg 2.1, r3, x.c
kpreg 2.1, r4, x.d
kpreg 2.1, r5, x.e
kpreg 2.1, r6, x.f
kpreg 2.1, r7, x.10
reg pc, x.4000
reg ivtp, x.4000
reg sp, x.9000
! kraj inicijalizacije
! 0368/2019
! A = 8 mod 4 = 0
! B = 6 mod 4 = 2
! C = 3 mod 4 = 3
! A0: Inicijalizacija IV tabele
org x.4000
ldimm x.0, r0
mvrir r0, ivtp
ldimm x.500, r0
stmem x.0, r0
ldimm x.1000, r0
stmem x.1, r0
ldimm x.1500, r0
stmem x.2, r0
ldimm x.2000, r0
stmem x.3, r0
ldimm x.2500, r0
stmem x.4, r0
ldimm x.3000, r0
stmem x.5, r0
! A0: Postavljanje ulaza u registre periferija
ldimm x.0, r0
stmem x.f102, r0
ldimm x.1, r0
stmem x.f142, r0
ldimm x.2, r0
stmem x.f202, r0
ldimm x.3, r0
stmem x.f002, r0
ldimm x.4, r0
stmem x.f042, r0
ldimm x.5, r0
stmem x.f0C2, r0
! A0: Transfer niza
ldimm x.8, r1    ! KP1.1 broj podataka
ldimm x.5000, r2 ! KP1 adresa
ldimm x.8, r3    ! KP2.1 broj podataka
ldimm x.6000, r4 ! KP2 adresa
ldimm x.0, r5    ! KP2 semafor
ldimm x.1, r6    ! Privremena jedinica
ldimm x.5, r0    ! ulaz, start=1
stmem x.F100, r0
ldimm x.F, r0    ! ulaz, start=1, enable=1, nivo=1
stmem x.F200, r0
load1:
ldmem x.F101, r0 ! Čitanje status registra
tst r0, r6        ! Ispitivanje bita spremnosti
beql load1
ldmem x.F103, r0 ! Čitanje podatka
stri [r2], r0     ! Upis u niz
inc r2
dec r1
bneq load1
load2:
cmp r5, r6
bneq load2
! B2: Poziv potprograma prvi put
ldimm x.9996, r0
push r0
ldimm x.8, r0
push r0
ldimm x.5000, r0
push r0
jsr process
pop r0
pop r0
pop r0
! B2: Poziv potprograma drugi put
ldimm x.9998, r0
push r0
ldimm x.8, r0
push r0
ldimm x.6000, r0
push r0
jsr process
pop r0
pop r0
pop r0
! C3: Slanje DMA
ldimm x.8, r0    ! Count registri
stmem x.f004, r0
ldimm x.1, r0
stmem x.f044, r0
ldimm x.5000, r0 ! AR1 registri
stmem x.f005, r0
ldimm x.9999, r0
stmem x.f045, r0
ldimm x.1, r1     ! Semafor
ldimm x.0, r2     ! Poređenje s nulom
ldimm x.2e, r0    ! Pokretanje DMA1.1
stmem x.f000, r0
loopdma:
cmp r1, r2
bneq loopdma
ldimm x.1, r1
ldimm x.8e, r0    ! Pokretanje DMA1.2
stmem x.f040, r0
loopdma2:
cmp r1, r2
bneq loopdma2
halt

! B2: Potprogram
process:
push r0
mvrpl r0, sp
push r1
push r2
push r3
push r4
push r5
push r6
push r7
! B2: Učitavanje argumenata
ldrid [r0] x.2, r1 ! Pokazivač na početak niza
ldrid [r0] x.3, r2 ! Veličina niza
ldrid [r0] x.4, r3 ! Zahtev za obradu
ldrid [r3] x.0, r4 ! Operacija
ldrid [r1] x.0, r5 ! Minimalni/maksimalni element
ldimm x.0, r6      ! Poređenje sa 0
cmp r2, r6         ! Ako je niz dužine 0, završi
beql endprocess
! B2: Iteracija kroz niz
processiter:
inc r1
dec r2
beql endprocess
cmp r4, r6
beql checkmin
! B2: Proveravamo maksimalni element
ldrid [r1] x.0, r7
cmp r5, r7
bleq success
jmp processiter
! B2: Proveravamo minimalni element
checkmin:
ldrid [r1] x.0, r7
cmp r5, r7
bleq processiter
! B2: Uslov ispunjen
success:
mvrrl r5, r7
jmp processiter
! B2: Povratak iz potprograma
endprocess:
inc r3
stri [r3], r5
pop r7
pop r6
pop r5
pop r4
pop r3
pop r2
pop r1
pop r0
rts

! A0: Prekidna rutina
org x.1500
push r0
cmp r5, r6
bneq transfer
jmp endintr   ! Već smo pročitali sve iz KP2.1
ldimm x.0, r0
stmem x.F200, r0
transfer:
ldmem x.F203, r0
stri [r4], r0
inc r4
dec r3
bneq endintr
ldimm x.1, r5
endintr:
pop r0
rti

! C3: Prekidna rutina DMA1.1
org x.2000
dec r1
stmem x.f000, r2
rti

! C3: Prekidna rutina DMA1.2
org x.2500
dec r1
stmem x.f040, r2
rti
