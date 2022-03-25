; o caractere ponto-e-vírgula denota que estas palavras são comentários
CLEAR ; limpa a pilha e configura o PC para o endereço zero
PUSH 4 ; empurra o número 4 na pilha, a pilha é [4]
PUSH 8 ; empurra o número 8 na pilha, a pilha é [4, 8]
ADD ; soma os dois valores no topo da pilha e empurra o resultado
POP ; remove o primeiro operando da pilha
POP ; remove o segundo operando da pilha
PUSH $R ; empurra o resultado para a pilha
OUT ; imprime o topo da pilha na tela