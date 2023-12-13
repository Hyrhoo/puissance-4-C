exe: *.c */*.c
	gcc *.c */*.c -o p4.exe
structs: structs/*.c
	gcc structs/*.c -o structs.exe
clean:
	rm *.exe