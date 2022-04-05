;int fatorial(int n)
;{
;  int r = 1;
;  for (int i=1; i<=n; i++ )
;    r *= i;
;  return r;
;}

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