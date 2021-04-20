        push R0
        call load_module
        pop
        mov R1, (R0)
        add R1, fun
        call R1
