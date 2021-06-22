; 2. zadatak, jul 2020.

                LOAD R0, C
                LOAD R1, B
                LOAD R2, A
                LOAD R3, #1
                LOAD R4, #0
loop:           DEC R0
                CMP R0, R4
                JLSS end
                LOAD R5, (R1, R0)
                CMP R5, R4
                JLEQ else
                STORE R3, (R2, R0)
                JMP loop
else:           STORE R4, (R2, R0)
                JMP loop
end:            ...


; 3. zadatak, jul 2020.

strchr:         PUSH BP
                STORE SP, BP
                PUSH R1
                PUSH R2
                PUSH R3
                STORE R1, #-1
                STORE R2, (BP)2
                STORE R3, (BP)3
                STORE R0, R2
                LOCC R1, R2, #0
                SUB R2, R2, R0
                DEC R2
                LOCC R2. R0, R3
                DEC R0
                POP R3
                POP R2
                POP R1
                POP BP
                RTS


; 4. zadatak, jul 2020.


adrA
cntA
cntSeq
sem

main:           LD #1000h
                ST adrA
                LD #0h
                ST cntA
                ST sem
                ST cntSeq
                LD #8003h
                OUT FF00h
per0_loop:      LD sem
                JZ per0_loop
                IN FF02h
                ST (adrA)
                LD adrA
                INC
                ST adrA
                PUSH
                LD cntA
                INC
                ST cntA
                CALL checkValue
                CMP #1
                JZ per0_checked
                CMP #MAX_NUM
                JNZ per0_loop
                JMP per0_next
per0_chcked:    POP
                LD cntSq
                INC
                ST cntSeq
                CMP #3
                JNZ per0_loop
per0_next:      LD #0
                OUT FF00h
                ST sem
                LD cntA
                PUSH
                LD #1000
                PUSH
                CALL sendSyncData
                POP
                POP
                JMP main
checkValue:     LD (SP)2
                AND #8001h
                RTS
sendSyncData:   PUSH
                LD BP
                PUSH
                LD SP
                ST BP
                LD (BP)3
                ST FF23h
                LD (BP)4
                ST FF24h
                LD #8002h
                OUT FF10h
                LD #8102
                OUT FF20h
ssd_loop:       LD sem
                JZ ssd_loop
                LD #0
                ST FF10h
                ST FF20h
                POP
                ST BP
                POP
                RTS
per0_intr:
dma1_intr:      PUSH
                LD #1
                ST sem
                POP
                RTI
