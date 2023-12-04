all: clean compile run

compile: main.cpp chess.cpp piece.cpp board.cpp 
	
	@g++ -o chess main.cpp piece.cpp board.cpp chess.cpp -std=c++11
run:
	
	@./chess
	
clean:
	
	@rm -f *.o
	@rm -f chess