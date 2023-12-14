exe: *.c structs/*.c minimax/*.c
	gcc *.c structs/*.c minimax/*.c -o p4.exe
structs: structs/*.c
	gcc structs/*.c -o structs.exe
minimax: minimax/*.c
	gcc minimax/*.c -o minimax.exe
clean:
	rm *.exe

test: test/*.c
	gcc test/*.c -o test/test.exe