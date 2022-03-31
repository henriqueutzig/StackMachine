;loop example
TOTAL_LOOP equ 11

CLEAR 
PUSH 1
PUSH TOTAL_LOOP
SUB
POP
PUSH $R
JZ 11
JMP 3 ; executa a instrucao indicada. 3 eh a instrucao 3 comecando por 0 (nao eh a linha no arquivo)
; neste caso eh a SUB, entao pula pra SUB e executa ela.