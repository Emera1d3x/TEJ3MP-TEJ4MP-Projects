MVI A,01                             
STA 0100
LDA 0100                             
CPI 1E                             
JM ELSE                             
MVI A,0A                             
STA 0100                             
JMP END                             
ELSE : 
MVI A,14
STA 0100
END : 
HLT
