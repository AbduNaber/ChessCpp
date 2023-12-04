#include "chess.h"


int main(){ 

    Board board;

    board.init(); // init the board
    board.print(); // print initalized board
    Game::play(board); // start the game
    
    return 0;
}


