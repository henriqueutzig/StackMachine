CLEAR ; limpa a pilha e configura o PC para o endere�o zero
PUSH 4 ; empurra o n�mero 4 na pilha, a pilha � [4]
PUSH 8 ; empurra o n�mero 8 na pilha, a pilha � [4, 8]
ADD ; soma os dois valores no topo da pilha e empurra o resultado
POP ; remove o primeiro operando da pilha
POP ; remove o segundo operando da pilha
PUSH $R ; empurra o resultado para a pilha
PUSH 12
SUB
JZ 3
OUT ; imprime o topo da pilha na tela