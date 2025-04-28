                             MVI A,03
                             
                             STA 0250
                             
                             
                             MVI A,02
                             
                             STA 0251
                             
                             
                             MVI A,06
                             
                             STA 0252
                             
                             
                             MVI A,01
                             
                             STA 0253
                             
                             
                             MVI B,03
                             
LOOP1 : 
                             LXI H,0250
                             
                             
                             MOV C,B
LOOP2 : 
                             MOV A,M
                             INX H
                             CMP M
                             JNC NO_SWAP
                             
                             
                             MOV D,M
                             MOV M,A
                             DCX H
                             MOV M,D
                             INX H
NO_SWAP : 
                             DCR C
                             JNZ LOOP2
                             
                             
                             DCR B
                             JNZ LOOP1
                             
                             
                             HLT
