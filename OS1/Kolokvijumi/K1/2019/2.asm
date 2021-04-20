dispatch:   push r0
            load r0, running
            store (r0)+offsR1, r1
            store (r0)+offsR2, r2
            ...
            store (r0)+offsR31, r31
            pop r1
            store (r0)+offsR0, r1
            pop r1
            store (r0)+offsPC, r1
            pop r1
            store (r0)+offsPSW, r1

            call scheduler

            load r0, running
            load r1, (r0)+offsPSW
            push r1
            load r1, (r0)+offsPC
            push r1
            load r1, (r0)+offsR1
            ...
            load r0, (r0)+offsR0

            iret
