;loop example
count equ 11

    CLEAR 
    PUSH 1
    PUSH count
$MAIN_LOOP:
    SUB
    POP
    PUSH $R
    JZ $END
    JMP $MAIN_LOOP 
$END:
