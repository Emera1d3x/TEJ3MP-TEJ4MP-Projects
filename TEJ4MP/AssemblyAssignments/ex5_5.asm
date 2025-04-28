                             MVI A,00
                             
                             STA 1020
                             
                             
                             MVI A,02
                             
                             STA 1021
                             
                             
                             MVI A,42
                             
                             STA 1022
                             
                             
                             MVI A,07
                             
                             STA 1023
                             
                             
                             MVI A,33
                             
                             STA 1024
                             
                             
                             MVI A,8F
                             
                             STA 1025
                             
                             
                             MVI A,41
                             
                             STA 1026
                             
                             
                             MVI A,A6
                             
                             STA 1027
                             
                             
                             LXI H,1020
                             
                             
                             LXI D,1200
                             
                             
                             MVI B,08
                             
NEXT : 
                             MOV A,M
                             MOV E,A
                             RAL
                             RAL
                             JC STORE
                             
                             
                             MOV A,E
                             RAR
                             RAR
                             RAR
                             JC SKIP
                             
                             
STORE : 
                             MOV A,E
                             STAX D
                             INX D
SKIP : 
                             INX H
                             DCR B
                             JNZ NEXT
                             
                             
                             HLT
