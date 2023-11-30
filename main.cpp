#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;


class coordinate;
class Piece;
class Board;


class coordinate{

    public:

        coordinate():  file('a') , rank('1'){};
        coordinate(char pFile, char pRank):  file(pFile) , rank(pRank){
            if(file <'a' || file > 'h' || rank > '8' || rank < '1'){

                cout<< "invalide coordinant";
                exit(1);

            }

        };
        coordinate setCoordinate(char f,char r);
        vector <char> getCoordinate() const{return {file,rank};};
        

         vector<int> coordinateToInt() const {
            
            // convert coordinant system to vector index for checking piece and target location
            int y = file - 97;
            int x = 8- (rank -'0') ; 
            vector<int> result= {x,y};
            return result;

        }


        friend class Board;
    private:
        char file;
        char rank;
    
};




class Piece{
    public:

        Piece(): color(-1), type('d'),point(0),isUnderAttack(0){};
        Piece(int pColor,char pType,coordinate pLocation,int pPoint) : color(pColor), type(pType),location(pLocation),point(pPoint),isUnderAttack(0){}; 
        
        static Piece createRook(int pColor,coordinate pLocation) { return Piece(pColor,'r',pLocation,5); };
        static Piece createPawn(int pColor,coordinate pLocation) { return Piece(pColor,'p',pLocation,1); };
        static Piece createKnight(int pColor,coordinate pLocation) { return Piece(pColor,'n',pLocation,3); };
        static Piece createBishop(int pColor,coordinate pLocation) { return Piece(pColor,'b',pLocation,3); };
        static Piece createQueen(int pColor,coordinate pLocation) { return Piece(pColor,'q',pLocation,9); };
        static Piece createKing(int pColor,coordinate pLocation) { return Piece(pColor,'k',pLocation,0); };
        static Piece createEmpty(coordinate pLocation) { return Piece(2,'e',pLocation,0); };
        
        friend class Board;
        
        // if movement is done return 1 , if not return 0
        int moveRook(coordinate targetLocation);
        int movepawn(coordinate targetLocation);
        int moveKnight(coordinate targetLocation);
        int moveBishop(coordinate targetLocation);
        int moveQueen(coordinate targetLocation);

        
        const Piece& operator=(const Piece& o){
            color = o.color;
            type = o.type;
            location = o.location;
            point = o.point;
            return *this;
        };


    private:
        // 0: black , 1:white,  2:empty
        int color ;
        char type;
        coordinate location;
        int point;
        int isUnderAttack;
};

int Piece::moveBishop(coordinate targetLocation){
    /* 
    Bishop has L type movement.
    */

    

       
    
}





class Board{

    public:
    
        Board(): pieces(8,vector<Piece>(8)){};

        Board& init();

        void print() const;

        Board& update(const coordinate cL, const coordinate tL);
        Board& check();
        int saveToFile();
        void setEmpty();
        bool checkValidity(Piece checkingP, coordinate targetLocation);

        const vector<Piece>& operator[](int index) const {
            return pieces[index];
        }
        std::vector<Piece>& operator[](int index) {

        return pieces[index];

        }


    private:
       
       
       vector<vector<Piece>> pieces; // pieces on 8x8 table.
};  



bool Board::checkValidity(Piece checkingP, coordinate targetLocation){

    if(targetLocation.file < 'a' || targetLocation.file > 'h' || targetLocation.rank < '1' || targetLocation.rank > '8'){
        cout << "target location is out of bond, please enter valid move";
        return false;
    }





    // convert coordinant system to vector index for checking piece and target location   
    vector <int> c = checkingP.location.coordinateToInt();
    vector <int> t = targetLocation.coordinateToInt();

    int cY= c[1];
    int cX = c[0] ; 

    int tY = t[1];
    int tX = t[0]; 



    switch (checkingP.type){

        case 'r':
                if(targetLocation.file != checkingP.location.file && targetLocation.rank != checkingP.location.rank){
                    cout << "movement is not valid";
                    return false;
                }
                if(targetLocation.file == checkingP.location.file) {
                    for(int i=cX;i<tX;i++){

                        if ((*this)[i][tY].type != 'e'){
                            cout << "movement is not valid";
                            return false;
                        }
                    }
                if(targetLocation.rank == checkingP.location.rank) {
                    for(int i=cY;i<tY;i++){

                        if ((*this)[i][tX].type != 'e'){
                            cout << "movement is not valid";
                            return false;
                        }
                    }

                }
               else 
                    return true;
                         
                break;
        case 'k':
                
                break;
        case 'q':
                break;

        case 'n':
                if((abs(cX -tX)==1 && abs(cY-tY)==2) ||(abs(cX -tX)==2 && abs(cY-tY)==1) )
                    return true;
                else 
                    false;
                break;

        case 'b':

                if( abs(cX-tX)== abs(cY-tY))
                    return true;
                else  
                    return false;
                break;

        case 'p':
                if(abs(tY-cY)== 1 &&(*this)[tX][tY].type == 'e')
                    return true;
                if(abs(tY-cY)== 2 && ( cY == 1 || cY==6  )&& (*this)[tX][tY].type == 'e')
                    return true;
                else 
                    false;    
                break;


    }
    return 1;

}
}

Board& Board::init(){


    const vector<char> layout = {'r','n','b','q','k','b','n','r'}; // inital layout for first line 
    
    for(auto c : layout){
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


// cL is for piece location that will check , tL is target location
Board& Board::update(const coordinate cL, const coordinate tL){ 
    vector <int> currentLoction = cL.coordinateToInt();
    vector <int> targetLocation = tL.coordinateToInt();

    // write check function in here later
    if(true){

        (*this).pieces[targetLocation[0]][targetLocation[1]]  =     (*this).pieces[currentLoction[0]][currentLoction[1]] ;
        (*this).pieces[currentLoction[0]][currentLoction[1]] = Piece::createEmpty(cL);


    }
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
    char cr,cf,tf,tr;



    cout<< "enter move: ";
    cin >>cf>>cr>>tf>>tr;
    coordinate cL(cf,cr);
    coordinate tL(tf,tr);
    board.update(cL,tL);
    board.print();





}