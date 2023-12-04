#include "chess.h"
int Game::play(Board &board) {
    string input;
    int s;
    int currentPlayer = 1; // 1 for white, 0 for black

    while (true) {
        input = Game::getInput();
        if (input == "quit") {
            cout << "exit" << endl;
            return 0;
        } 
        else if (input == "save") {
            s = board.saveToFile();
            cout << "saved status(0 is success): " << s << endl;
            continue;
        } 
        else if (input == "load") {
            s = board.loadFromFile();
            cout << "load status(1 is success): " << s << endl;
            board.print();
            continue;
        } 
        else if (input == "point") {
            const vector<double> r = board.calculatePoint();
            cout << "POINT -> w: " << r[1] << " b: " << r[0] << endl;
            continue;
        } 
        else if (input == "suggest") {
            board.suggestion(currentPlayer);
        } 
        else if (input == "help") {
            Game::help();
        } else if (input.length() == 4) {
            cin.clear();

            coordinate cL(input[0], input[1]);
            coordinate tL(input[2], input[3]);

            if (cL.ok == false || tL.ok == false) {
                cout << "invalid coordinate, try again" << endl;
                continue;
            }

            // Check if it's the correct player's turn
            if (board.getPiece(cL).getColor() != currentPlayer) {
                cout << "It's not your turn!" << endl;
                continue;
            }



            if (board.update(cL, tL)) {
                board.print();
                currentPlayer = 1 - currentPlayer; // Switch player turns

                if(board.checkMateSim(currentPlayer)){
                    return 0;   
                }
            }

            board.resetAP();
            board.checkUnderAttack();
            
        } else {
            cout << "invalid input." << endl;
        }
    }
    return 0;
}
