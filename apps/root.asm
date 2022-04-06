;n = 9
;r = n
;while (r * r > n)
;   r = r - 1
;print(r)

n equ 9

    CLEAR
    PUSH n
    PUSH n
    PUSH n

$SQRT_LOOP:
    MUL
    POP
    POP
    PUSH n
    PUSH $R
    SUB
    JZ $END
    JN $END
    POP
    POP
    PUSH -1
    ADD
    POP
    POP
    PUSH $R
    PUSH $R
    PUSH $R
    JMP $SQRT_LOOP
$END:
    POP
    POP
    OUT
