; os 3 elementos na pilha sao os coeficientes do polinomio Ax^2 + Bx + C
; x^2 + 2x - 3
CLEAR

; ------------ primeira raiz ------------- ;
PUSH    1 ; A
PUSH    2
MUL
POP
POP
PUSH    $R

PUSH    1 ; A
PUSH    -3 ;C
MUL
POP
pOp
PUSH    $R

PUSH    -4
MUL
POP
POP
PUSH    $R

PUSH    2
PUSH    2 ;B
POW
POP
POP
PUSH    $R

ADD
POP
POP
PUSH    $R

SQRT
POP
PUSH    $R

PUSH    2 ;B
PUSH    0
SUB
POP
POP
PUSH    $R

ADD
POP
POP
PUSH    $R

DIV
POP
POP
PUSH    $R

; ------------ segunda raiz ------------- ;

PUSH    1 ; A
PUSH    2
MUL
POP
POP
PUSH    $R

PUSH    1 ; A
PUSH    -3 ;C
MUL
POP
POP
PUSH    $R

PUSH    -4
MUL
POP
POP
PUSH    $R

PUSH    2
PUSH    2 ;B
POW
POP
POP
PUSH    $R

ADD
POP
POP
PUSH    $R

SQRT
POP
PUSH    $R

PUSH    2 ;B
PUSH    0
SUB
POP
POP
PUSH    $R

SUB
POP
POP
PUSH    $R

DIV
POP
POP
PUSH    $R

; --------------- resultados ---------------;

OUT     ; raiz 2
POP
OUT     ; raiz 1