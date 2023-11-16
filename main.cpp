#include <iostream>
#include <vector>
#include <string>

using namespace std;


class coordinate;
class Piece;
class Board;


class coordinate{

    public:

        coordinate():  file('a') , rank('1'){};
        coordinate(char pFile, char pRank):  file(pFile) , rank(pRank){};
        
        
        coordinate setCoordinate(char f,char r);
        coordinate getCoordinate(char f,char r) const;

    private:
        char file;
        char rank;
    
};




class Piece{
    public:

        Piece(): color(-1), type('d'),point(-1){};
        Piece(int pColor,char pType,coordinate pLocation,int pPoint) : color(pColor), type(pType),location(pLocation),point(pPoint){}; 
        
        static Piece createRook(int pColor,coordinate pLocation) { return Piece(pColor,'r',pLocation,5); };
        static Piece createPawn(int pColor,coordinate pLocation) { return Piece(pColor,'p',pLocation,1); };
        static Piece createKnight(int pColor,coordinate pLocation) { return Piece(pColor,'k',pLocation,3); };
        static Piece createBishop(int pColor,coordinate pLocation) { return Piece(pColor,'b',pLocation,3); };
        static Piece createQueen(int pColor,coordinate pLocation) { return Piece(pColor,'q',pLocation,9); };
        static Piece createEmpty(coordinate pLocation) { return Piece(2,'e',pLocation,0); };
        

        Piece& moveRook();
        Piece& movepawn();
        Piece& moveKnight();
        Piece& moveBishop();
        Piece& moveQueen();



    private:
        // 0: white , 1:black 2:empty
        const int color ;
        const char type;
        coordinate location;
        const int point;
};







class Board{

    public:
    
        Board(): pieces(64){};
        Board& init();
        void print() const;
        Board& update();
        Board& check();
        int saveToFile();
        void setEmpty();


    private:
       const char layout[8] = {'r','n','b','q','k','b','n','r'}; // inital layout for first line 
       
       vector<Piece> pieces; // pieces on 8x8 table.
};  




int main(){



}