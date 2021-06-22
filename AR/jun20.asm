; 3. zadatak, jun 2020.

strcpy:         PUSH BP
                ST SP, BP
                PUSH R1
                PUSH R2
                PUSH R3
                PUSH R4
                ; Determine string length
                LD R1, (BP)3        ; destination address
                LD R2, (BP)2        ; source address
                LD R3, #-1          ; string length
                LD R2, R4           ; copy of source address
                LOCC R3, R2, #0     ; locate end of string
                SUB R2, R2, R4      ; subtract start address to determine length
                INC R2              ; null character
                ; Copy the string
                MOVC R2, R4, #0, R2, R1
                ; Clean up
                POP R4
                POP R3
                POP R2
                POP R1
                POP BP
                RTS

; 4. zadatak, jun 2020.

adrA                            ; adresa niza A
cntA                            ; broj elemenata niza A preostao za učitavanje
sem                             ; da li je prenos na PER1 ili DMA završen
cnt                             ; pomoćni brojač u obradi
prev                            ; prethodni element niza u obradi
min                             ; minimalni element podniza u obradi
value                           ; lokacija u memoriji za izvorišnu adresu DMA u memset

                LD #1000h
                ST adrA
                LD #0
                ST cntA
                ST sem
; učitavanje sa PER0
                LD #8001h       ; Start=1, I/~O=1
                OUT FF00h
per0_loop:      IN FF01h
                AND #0001h
                JZ per0_loop
                IN FF02h
                CMP STOP
                JZ per0_exit
                ST (adrA)
                LD cntA
                INC
                ST cntA
                JMP per0_loop
per0_exit:      LD #0000h
                OUT FF00h
; obrada
                CALL Obrada
; slanje PER1
                LD #8012h       ; Start=1, Cycle Stealing=1, Enable=1
                ST FF20h
                LD #0
per1_loop:      LD sem
                CMP #1
                JZ per1_loop
; brisanje niza
                LD cntA
                PUSH
                LD #0
                ST sem
                PUSH
                LD #1000
                PUSH
                CALL memset
                POP
                POP
                POP
                HALT
; obrada niza
Obrada:         LD #1000
                ST adrA
                LD cntA
                ST cnt
                LD #0
                ST min
                ST prev
obrada_loop:    LD (adrA)
                CMP prev
                JLSS obrada_less
                LD min
                ST (adrA)
                JMP obrada_next
obrada_less:    ST min
obrada_next:    LD adrA
                INC
                ST adrA
                LD cnt
                DEC
                ST cnt
                JNZ obrada_loop
                RTS
; postavljanje memorije
memset:         PUSH
                LD BP
                PUSH
                LD SP
                ST BP
                LD (BP)5
                OUT FF35h
                LD (BP)4
                ST value
                LD (BP)3
                OUT FF34h
                LD #value
                OUT FF33h
                LD #8032h       ; Start=1, Cycle Stealing=1, Enable=1, Same=1
                OUT FF30h
memset_loop:    LD sem
                CMP #1
                JZ memset_loop
                POP
                ST BP
                POP
                RTS
dma_intr:
dma1_intr:      PUSH
                LD #1
                ST sem
                POP
                RTI
