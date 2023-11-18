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

        Piece(): color(-1), type('d'),point(0){};
        Piece(int pColor,char pType,coordinate pLocation,int pPoint) : color(pColor), type(pType),location(pLocation),point(pPoint){}; 
        
        static Piece createRook(int pColor,coordinate pLocation) { return Piece(pColor,'r',pLocation,5); };
        static Piece createPawn(int pColor,coordinate pLocation) { return Piece(pColor,'p',pLocation,1); };
        static Piece createKnight(int pColor,coordinate pLocation) { return Piece(pColor,'n',pLocation,3); };
        static Piece createBishop(int pColor,coordinate pLocation) { return Piece(pColor,'b',pLocation,3); };
        static Piece createQueen(int pColor,coordinate pLocation) { return Piece(pColor,'q',pLocation,9); };
        static Piece createKing(int pColor,coordinate pLocation) { return Piece(pColor,'k',pLocation,0); };
        static Piece createEmpty(coordinate pLocation) { return Piece(2,'e',pLocation,0); };
        
        friend class Board;
        Piece& moveRook();
        Piece& movepawn();
        Piece& moveKnight();
        Piece& moveBishop();
        Piece& moveQueen();

        Piece& operator=(const Piece& o);


    private:
        // 0: black , 1:white,  2:empty
        int color ;
        char type;
        coordinate location;
        int point;
};


    Piece& Piece::operator=(const Piece& o){

        color = o.color;
        type = o.type;

        location = o.location;
        point = o.point;

        return *this;
    }




class Board{

    public:
    
        Board(): pieces(8,vector<Piece>(8)){};
        Board& init();
        void print() const;
        Board& update();
        Board& check();
        int saveToFile();
        void setEmpty();


    private:
       
       
       vector<vector<Piece>> pieces; // pieces on 8x8 table.
};  

Board& Board::init(){
    const vector<char> layout = {'r','n','b','q','k','b','n','r'}; // inital layout for first line 
    
    for(auto c:layout){
        switch(c){
            case 'r':
                pieces[0][0] = Piece::createRook(0,coordinate('a','8'));
                pieces[0][7] = Piece::createRook(0,coordinate('h','8'));
                pieces[7][0] = Piece::createRook(1,coordinate('a','1'));
                pieces[7][7] = Piece::createRook(1,coordinate('h','1'));
                break;
            case 'n':
                pieces[0][6] = Piece::createKnight(0,coordinate('g','8'));
                pieces[0][1] = Piece::createKnight(0,coordinate('b','8'));
                pieces[7][6] = Piece::createKnight(1,coordinate('b','1'));
                pieces[7][1] = Piece::createKnight(1,coordinate('g','1'));
                break;
            case 'b':
                pieces[0][2] = Piece::createBishop(0,coordinate('c','8'));
                pieces[0][5] = Piece::createBishop(0,coordinate('f','8'));
                pieces[7][2] = Piece::createBishop(1,coordinate('c','1'));
                pieces[7][5] = Piece::createBishop(1,coordinate('f','1'));
                break;
            case 'q':
                
                pieces[0][3] = Piece::createQueen(0,coordinate('d','8'));
                pieces[7][3] = Piece::createQueen(1,coordinate('d','1'));
                break;
            case 'k':
                pieces[0][4] = Piece::createKing(0,coordinate('e','8'));
                pieces[7][4] = Piece::createKing(1,coordinate('e','1'));
                break;

        }
    }
    for (int i =0;i<8;++i){
        pieces[1][i] = Piece::createPawn(0,coordinate('a'+i,'7'));
        pieces[6][i] = Piece::createPawn(1,coordinate('a'+i,'2'));

    }
    for (int i= 2 ; i<6;++i)
        for(int j =0;j<8;++j)
            pieces[i][j] = Piece::createEmpty(coordinate('a'+j,6-i+'0'));
    

        
    return *this;
}


void Board::print() const{

    for(int i =0;i<8;++i){
        cout << 8-i << " |";
        for(int j=0;j<8;++j){

            if( pieces[i][j].color == 2) {
                cout<<" "<<".";
            }
            else if(pieces[i][j].color == 1 ){
                 cout<<" "<< static_cast<char>(pieces[i][j].type-32) ;
            }
            else if(pieces[i][j].color == 0){
                cout<<" "<< pieces[i][j].type;
            }

        }
        cout << endl;
    }  
}

int main(){

    Board board;
    board.init();
    board.print();

}