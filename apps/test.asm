;loop example
CLEAR 
PUSH 1
PUSH 10
SUB
POP
PUSH $R
JZ 11
JMP 3 ; executa a instrucao indicada. 3 eh a instrucao 3 comecando por 0 (nao eh a linha no arquivo)
; neste caso eh a SUB, entao pula pra SUB e executa ela.