;--------------------------------------------------------
; Sehan Munir
; TEJ4MP, Mr. TEACHER
; 2025-04-15
; MSBytes are Left (Lower index)
; Unit 5 - 8085 Assembly Language (Pt. 6)
; Program with 3 subroutines:
;   1. STORE_DATA - Saves certain data into memory (specified in assignment)
;   2. SORT_ARRAY - Sorts array of 2-byte integers in ascending order starting at location (1120H and 1121H). The number of elements is specified at location 1100H (max value is 5)
;   3. SEARCH_ARRAY - Searches for a 2-byte value in the array (value specified at 1160H and 1161H). If found, location 1165 is specified with 1, else its 2.
;--------------------------------------------------------
MAIN:   
	CALL STORE_DATA ; Method 1 Used
	CALL SORT_ARRAY ; Method 2 Used
	CALL SEARCH_ARRAY ; Method 2 Used
	HLT; End Program
; ------------------------------------------------------
; Subroutine: STORE_DATA
; Purpose: Saves certain data into memory (specified in assignment)
;          - Number of Elements (Location 1110H)
;          - 2-byte Integers (Locations 1120H and 1121H and onwards)
;          - Search Key (Location 1160H 1161H)
; ------------------------------------------------------
STORE_DATA:
	; (Number of Elements)/////////
	MVI A,05H;
	STA 1110H; Store at 1110H
	; (Element 1: 12A3H)///////////
	MVI A,12H; High byte
	STA 1120H; High byte
	MVI A,A3H; Low byte
	STA 1121H; Low byte; 
	; (Element 2: 32CFH)///////////
	MVI A,32H; High byte
	STA 1122H; High byte
	MVI A,CFH; Low byte
	STA 1123H; Low byte
	; (Element 3: 01BDH)///////////
	MVI A,01H; High byte
	STA 1124H; High byte
	MVI A,BDH; Low byte
	STA 1125H; Low byte
	; (Element 4: AF23H)///////////
	MVI A,AFH; High byte
	STA 1126H; High byte
	MVI A,23H; Low byte
	STA 1127H; Low byte
	; (Element 5: CE89H)///////////
	MVI A,CEH; High byte
	STA 1128H; High byte
	MVI A,89H; Low byte
	STA 1129H; Low byte
	; (Search Key: 01BD)///////////
	MVI A,01H; High byte
	STA 1160H; High byte
	MVI A,BDH; Low byte
	STA 1161H; Low byte
	RET; End Method ///////////
; ------------------------------------------------------
; Subroutine: SORT_ARRAY
; Purpose: Sort 2-byte integer array in ascending order using Bubble Sort
;          - 2-byte Integers (Locations 1120H and 1121H and onwards)
;          - Number of Elements (Location 1110H)
; ------------------------------------------------------
SORT_ARRAY: ; Starting
	LXI H,1120H;
	LDA 1110H;
	MOV B,A;
	DCR B;
OUTER: ; Outer Loop (has changes)
	LXI H,1120H
	MOV C,B
LOOP: ; Inner Loop
	MOV A,M
	INX H
	INX H
	CMP M ; Compares adjacent MSBytes
	JC LAST
	JZ LSB_SWAP
MSB_SWAP: ; Swaps MSByte (And also LSByte)
	MOV D,M
	MOV M,A
	DCX H
	DCX H
	MOV M,D
	INX H
	MOV A,M
	INX H
	INX H
	MOV D,M
	MOV M,A
	DCX H
	DCX H
	MOV M,D
	INX H
LAST: ; Checking when outer loop finishes
	DCR C
	JNZ LOOP
	DCR B
	JNZ OUTER
	RET
LSB_SWAP: ; Swaps LSBytes if required
	DCX H
	MOV A,M
	INX H
	INX H
	CMP M
	JC NEXT
	DCX H
	DCX H
	DCX H
	MOV A,M
	INX H
	INX H
	JMP MSB_SWAP
NEXT:
	DCX H
	JMP NEXT
; ------------------------------------------------------
; Subroutine: SEARCH_ARRAY
; Purpose: Searches for a 2-byte value in the array (value specified at 1160H and 1161H). If found, location 1165 is specified with 1, else its 2.
; ------------------------------------------------------
SEARCH_ARRAY:
	LDA 1110H       ; Load number of elements
	MOV C,A  
	LDA 1160H       ; Load search MSB
	MOV D,A         ; D = search MSB
	LDA 1161H       ; Load search LSB
	MOV E,A         ; E = search LSB
	LXI H,1120H     ; Point to start of array
SEARCH_LOOP: ; searches byte by byte 
	MOV A,M   
	CMP D       
	JNZ NOT_FOUND_YET
	INX H
	MOV A,M    
	CMP E        
	JZ FOUND    
	DCX H 
NOT_FOUND_YET:
	INX H
	INX H
	DCR C
	JNZ SEARCH_LOOP
NOT_FOUND: ; If not found my end of loop, indicate info
	MVI A,02H
	STA 1165H
	RET
FOUND: ; If found, indicate info
	MVI A,01H
	STA 1165H
	RET
