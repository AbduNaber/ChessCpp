#pragma ONCE

#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "board.h"



using namespace std;

// game for play chess
class Game{
    public:

        //prints help message
        static void help(){
            cout << "help "<<endl;
        };
        
        static int play(Board & board);

        //get input for play
        static string getInput(){
                string input;
                cout<< "enter move: ";
                cin >>input;
                return input;
    
            }

        private:
           
    
};


