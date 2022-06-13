.global find_max
.extern my_arr_length, my_arr
.section text
find_max:
    push r1
    push r2
    push r3
    push r4
    # Initialization
    ldr r4, $2
    ldr r3, $my_arr_length
    ldr r1, $0
    ldr r0, $0xFFFF
    # Main loop
max_loop:
    ldr r2, [r1+my_arr]
    cmp r2, r0
    jgt is_max
    jmp max_continue
is_max:
    ldr r0, [r1+my_arr]
max_continue:
    add r1, r4
    cmp r1, r3
    jne %max_loop
    # Cleanup
    pop r4
    pop r3
    pop r2
    pop r1
    ret
