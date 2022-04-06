;n = 5
;r = 1;
;for (i=1; i<=n; i++)
;   r *= i;
;print(r)

n equ 5
r equ 1
i equ 1

    CLEAR
    PUSH r 
    PUSH i
    PUSH n
    SUB
    JN $END
    POP
    STORE
    POP
    
$FAT_LOOP:
    LOAD
    MUL
    POP
    POP
    PUSH $R
    LOAD
    PUSH 1
    ADD
    POP
    POP
    PUSH $R
    PUSH n
    SUB
    JN $END
    POP
    STORE
    POP
    JMP $FAT_LOOP

$END:
    POP
    POP
    OUT
