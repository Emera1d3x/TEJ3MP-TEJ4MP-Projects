MVI A,00
MVI D,00
MVI H,00
MVI L,00                             
MVI A,56                             
ADI C5                             
MOV L,A
MVI A,82                             
ACI 93                             
JNC JUMPER                             
INR D
JUMPER : 
MOV H,A
MVI A,00                             
HLT
