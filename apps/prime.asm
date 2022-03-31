; n=5
; x,c=1,0
; while(c<n):
;     x+=1
;     for i in range(2,x+1):
;         if(x%i==0):
;             break
;     if(i==x):
;         c=c+1
; print(x)

n equ 5 
x equ 1 
c equ 0 
i equ 1 

    CLEAR
    PUSH c
    PUSH x
    STORE
    POP

$PRIME_LOOP:
    LOAD
    PUSH 1
    ADD
    POP 
    POP
    PUSH $R 
    STORE
    POP
    PUSH i

$FOR:
    PUSH 1
    ADD
    POP
    POP
    PUSH $R
    LOAD
    MOD
    JZ $END_FOR
    SUB
    JZ $END_FOR
    POP
    JMP $FOR
$END_FOR:
    SUB
    JZ $TEST_WHILE
    POP
    POP
    PUSH 0
    ADD
    POP
    JMP $NOT_TEST

$TEST_WHILE:
    POP 
    POP
    PUSH 1
    ADD
    POP
    POP
    PUSH $R

$NOT_TEST:
    PUSH n
    PUSH $R
    SUB
    POP
    POP
    JN $PRIME_LOOP
$END:
    POP
    LOAD
    OUT