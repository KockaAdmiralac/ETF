f:      load r1, #0
        load r2, (n)
        cmp r1, r2
        jz ret
        sub r2, 1
        push(n)
        store (n), r1
        call f
        pop(n)
        add r0, 1
ret:    iret
