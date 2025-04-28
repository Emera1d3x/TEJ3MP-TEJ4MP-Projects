MVI A,00
STA 0200                             
MVI A,0B                             
LOOP : 
CPI 16
JNC ENDLOOP                             
MOV B,A
LDA 0200
ADD B
STA 0200                             
MOV A,B
ADI 02
JMP LOOP                             
ENDLOOP : 
HLT
