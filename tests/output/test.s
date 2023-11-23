    .text
    .globl  main
    .type   main, @function
square:
    enter   $(8 * 12), $0

    mov     %rdi, -16(%rbp)
    mov     %rsi, -8(%rbp)
    movl    $0, %eax
    movl    %eax, -24(%rbp)

beginwhile1:
    movl    -24(%rbp), %eax
    movl    -8(%rbp), %ebx
    cmpl    %ebx, %eax
    movl    $0, %ebx
    movl    $1, %eax
    cmovl   %eax, %ebx
    movl    %ebx, -32(%rbp)

    cmpl    $0, -32(%rbp)
    je      endwhile2

    mov     -24(%rbp), %rdi
    call    print_int
    movl    %eax, -40(%rbp)

    movl    -16(%rbp), %eax
    movl    $2, %ebx
    imul    %eax, %ebx
    movl    %ebx, -56(%rbp)

    movl    -56(%rbp), %eax
    movl    %eax, -16(%rbp)

    movl    -24(%rbp), %eax
    addl    $1, %eax
    movl    %eax, -72(%rbp)

    movl    -72(%rbp), %eax
    movl    %eax, -24(%rbp)

    jmp    beginwhile1

endwhile2:
    movl    -16(%rbp), %eax
    movl    $2, %ebx
    xor     %rdx, %rdx
    idiv    %ebx
    mov     %rdx, -88(%rbp)

    movl    -88(%rbp), %eax
    movl    $0, %ebx
    cmpl    %eax, %ebx
    movl    $0, %ebx
    movl    $1, %eax
    cmove   %eax, %ebx
    movl    %ebx, -88(%rbp)

    cmpl    $0, -88(%rbp)
    je      endthen3

    movl    $1, %eax

    leave
    ret
    jmp    endelse4

endthen3:
    movl    $0, %eax

    leave
    ret
endelse4:
    leave
    ret
main:
    enter   $(8 * 6), $0

    movl    $1, %eax
    movl    %eax, -8(%rbp)

    movl    $1, %eax
    movl    %eax, -16(%rbp)

    mov     -16(%rbp), %rdi
    mov     $10, %rsi
    call    square
    movl    %eax, -32(%rbp)

    movl    -32(%rbp), %eax
    movl    %eax, -8(%rbp)

    mov     -8(%rbp), %rdi
    call    print_bool
    movl    %eax, -40(%rbp)

    leave
    ret
