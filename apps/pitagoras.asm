; pitagoras na forma a^2 = b^2 + c^2
; a = hipotenusa, b = cateto oposto e c = cateto adjacente (ou vice-versa)

CLEAR

; b = 12, cateto oposto
PUSH	12
PUSH	12
MUL ; b^2
POP
POP
PUSH	$R

; c = 5, cateto adjacente
PUSH	5
PUSH	5
MUL ; c^2
POP
POP
PUSH	$R

ADD ; b^2 + c^2
POP
POP
PUSH	$R

SQRT ; a = sqrt(b^2 + c^2)
POP
PUSH 	$R

OUT ; resultado a, hipotenusa