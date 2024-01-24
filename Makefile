exe: *.cpp structs/dict/*.cpp structs/game/*.cpp structs/player/*.cpp minimax/*.cpp
	gcc *.cpp structs/dict/*.cpp structs/game/*.cpp structs/player/*.cpp minimax/*.cpp -lstdc++ -o p4.exe
structs: structs/*.cpp
	gcc structs/*.cpp -lstdc++ -o structs.exe
minimax: minimax/*.cpp
	gcc minimax/*.cpp -lstdc++ -o minimax.exe
clean:
	rm *.exe

test: test/*.cpp
	gcc test/*.cpp -lstdc++ -o test/test.exe