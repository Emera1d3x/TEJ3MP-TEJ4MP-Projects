                             LXI H,0120
                             
                             
                             MVI C,0B
                             
                             MVI A,20
                             
STORE_LOOP : 
                             MOV M,A
                             INX H
                             INR A
                             DCR C
                             JNZ STORE_LOOP
                             
                             
                             LXI H,0120
                             
                             
                             MVI C,0B
                             
                             MVI A,22
                             
SEARCH_LOOP : 
                             CMP M
                             JZ FOUND
                             
                             
                             INX H
                             DCR C
                             JNZ SEARCH_LOOP
                             
                             
NOT_FOUND : 
                             MVI A,00
                             
                             STA 1001
                             
                             
                             JMP END
                             
                             
FOUND : 
                             MVI A,01
                             
                             STA 1001
                             
                             
END : 
                             HLT
