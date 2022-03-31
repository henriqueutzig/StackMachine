n equ 3 ; n = 3
x equ 1 ; x = 1
c equ 0 ; c = 0
i equ 1 ; i = 1

    CLEAR
    PUSH c ; STACK = [0]
    PUSH x ; STACK = [1, 0]

$PRIME_LOOP:
    PUSH 1
    ADD ; x += 1
    POP
    POP
    PUSH $R
    PUSH i

$FOR:
    PUSH 1 
    ADD ; i += 1
    POP
    POP
    PUSH $R
    MOD
    JZ $END_FOR
    JMP $FOR
$END_FOR:
    SUB
    JZ $TEST_WHILE
    JMP $NOT_TEST

$TEST_WHILE:
    POP
    POP
    PUSH 1
    ADD

$NOT_TEST:
    POP
    POP
    PUSH n
    PUSH $R
    SUB
    POP
    POP
    JN $PRIME_LOOP
    JMP $END
$END:
    POP
    POP
    OUT