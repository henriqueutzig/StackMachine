;loop example
CLEAR 
PUSH 1
PUSH 10
SUB
POP
PUSH $R
JZ 11
JMP 2 ; executa a proxima instrucao apos a indicada. 2 eh a instrucao 2 comecando por 0
; neste caso eh a PUSH 10, entao pula pra executar SUB