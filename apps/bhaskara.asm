; as 3 constantes sao os coeficientes do polinomio Ax^2 + Bx + C

A equ 1
B equ 2
C equ -3

; raizes de x^2 + 2x - 3 = 0

    CLEAR

    PUSH    A
    PUSH    2
    MUL
    POP
    POP
    PUSH    $R

    PUSH    A
    PUSH    C
    MUL
    POP
    POP
    PUSH    $R

    PUSH    -4
    MUL
    POP
    POP
    PUSH    $R

    PUSH    2
    PUSH    B
    POW
    POP
    POP
    PUSH    $R

    ADD
    POP
    POP
    PUSH    $R

    SQRT
    POP
    PUSH    $R
    STORE

    PUSH    B
    PUSH    0
    SUB
    POP
    POP
    PUSH    $R

    ADD
    POP
    POP
    PUSH    $R

    DIV
    POP
    POP
    PUSH    $R ; primeira raiz

    PUSH    A
    PUSH    2
    MUL
    POP
    POP
    PUSH    $R

    LOAD

    PUSH    B
    PUSH    0
    SUB
    POP
    POP
    PUSH    $R

    SUB
    POP
    POP
    PUSH    $R

    DIV
    POP
    POP
    PUSH    $R ; segunda raiz


