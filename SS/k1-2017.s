.intel_syntax noprefix

.global main
.extern printf
.extern scanf
.extern _exit
.extern malloc

.data
message_start:
.asciz "%d"
message2_start:
.asciz "%d\n"
length:
.int 0
.int 0
search:
.int 0
.int 0

.text
callee:
    mov rax, [rbp-8]    # search
    mov rcx, [rbp-16]   # length
    mov rdx, [rbp-24]   # addr
    push rbx
    mov rbx, 0
    cmp rcx, 0
    je endloop2
startloop2:
    cmp [rdx], rax
    jne skipmov
    mov rax, rbx
skipmov:
    add rbx, 1
    add rdx, 8
    cmp rbx, rcx
    jne startloop2
endloop2:
    pop rbx
    ret

main:
    push rbp
    mov rbp, rsp

    # input array length
    mov rdi, offset message_start
    mov rsi, offset length
    call scanf
    mov rcx, length
    cmp rcx, 0
    je endloop

    # allocate memory
    mov rdi, length
    shl rdi, 3
    call malloc

    # fill
    mov rbx, 1
    mov rcx, length
    add rcx, 1
    mov rdx, rax
startloop:
    mov [rax], rbx
    add rax, 8
    add rbx, 1
    cmp rcx, rbx
    jne startloop
endloop:
    mov rbx, rdx

    # input searched element
    mov rdi, offset message_start
    mov rsi, offset search
    call scanf

    # entry
    push rbp
    mov rbp, rsp
    # callee args
    mov rax, search
    push rax
    mov rax, length
    push rax
    push rbx
    # call
    call callee
    # exit
    add rsp, 24
    leave

    mov rdi, rbx
    mov rbx, rax
    call free

    mov rdi, offset message2_start
    mov esi, ebx
    call printf

    # syscall
    mov rdi, 0
    call _exit

    leave
