.global my_arr, my_arr_length
.extern find_max
.section ivt
.word start
.skip 2
.word isr_timer, isr_terminal
.skip 6
.word isr_custom
.section text
.equ term_out, 0xFF00
.equ term_in, 0xFF02
.equ tim_cfg, 0xFF10
.equ letter_o, 79
.equ letter_e, 69
.equ my_offset, 4
.equ my_arr_length, my_arr_end-my_arr
start:
    ldr r2, $0x7
    str r2, tim_cfg
    ldr r0, $1                  # r0 = 1
    ldr r1, $my_var             # r1 = 0
    str r0, [r1]                # my_var = 1
    ldr r1, $letter_t           # r1 = offset(letter_t)
    ldr r0, [r1+4]              # r0 = 1
    ldr r1, [r1+my_offset]      # r1 = 1
    cmp r0, r1                  # equal
    int r2
    jeq should_jump_eq
    ldr r0, $letter_e           # should not happen
    str r0, term_out
    halt
should_jump_eq:                 # should happen
    add r0, r1                  # r0 = 2
    cmp r0, r1                  # not equal
    jne should_jump_neq
    ldr r0, $letter_e           # should not happen
    str r0, term_out
    halt
should_jump_neq:                # should happen
    or r0, r1                   # r0 = 3
    jgt should_jump_grt
    ldr r0, $letter_e           # should not happen
    str r0, term_out
    halt
should_jump_grt:                # should happen
    shl r0, r1                  # r0 = 6
    shr r1, r1                  # r1 = 0
    test r0, r1
    jeq should_jump_zero
    ldr r0, $letter_e           # should not happen
    str r0, term_out
    halt
should_jump_zero:               # should happen
    call %find_max
    ldr r1, $48
    add r0, r1
    str r0, term_out
inf_loop:
    jmp inf_loop
    halt
isr_timer:
    push r0
    ldr r0, %letter_t
    str r0, term_out
    pop r0
    halt                        # timeout after 60s and exit
isr_terminal:
    push r0
    ldr r0, $letter_o
    str r0, term_out
    ldr r0, term_in
    str r0, term_out
    pop r0
    iret
isr_custom:
    push r0
    push r1
    ldr r0, letter_c
    ldr r1, letter_t
    str r0, term_out
    cmp r0, r1
    pop r1
    pop r0
    iret
.section data
letter_t: .word 84
letter_c: .word 67
my_var: .word 0
my_arr:
    .word 4
    .word 3
    .word 4
    .word 8
    .word 1
    .word 0
    .word 6
    .word 3
my_arr_end:
