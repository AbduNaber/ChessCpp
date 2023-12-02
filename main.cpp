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

        Piece(): color(-1), type('d'),point(0.0),isUnderAttack(0){};
        Piece(int pColor,char pType,coordinate pLocation,double pPoint) : color(pColor), type(pType),location(pLocation),point(pPoint),isUnderAttack(0){}; 
        
        static Piece createRook(int pColor,coordinate pLocation) { return Piece(pColor,'r',pLocation,5); };
        static Piece createPawn(int pColor,coordinate pLocation) { return Piece(pColor,'p',pLocation,1); };
        static Piece createKnight(int pColor,coordinate pLocation) { return Piece(pColor,'n',pLocation,3); };
        static Piece createBishop(int pColor,coordinate pLocation) { return Piece(pColor,'b',pLocation,3); };
        static Piece createQueen(int pColor,coordinate pLocation) { return Piece(pColor,'q',pLocation,9); };
        static Piece createKing(int pColor,coordinate pLocation) { return Piece(pColor,'k',pLocation,0); };
        static Piece createEmpty(coordinate pLocation) { return Piece(2,'e',pLocation,0); };
        
        friend class Board;
                
        const Piece& operator=(const Piece& o){
            color = o.color;
            type = o.type;
            location = o.location;
            point = o.point;
            isUnderAttack = o.isUnderAttack;
            return *this;
        };


    private:
        // 0: black , 1:white,  2:empty
        int color ;
        char type;
        coordinate location;
        double point;
        int isUnderAttack;
};

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
        


    int i,stop;
    if (checkingP.color == (*this)[tX][tY].color || checkingP.type == 'e'){

        return false;
    }


    
    switch (checkingP.type){
          
        case 'r':
                if(targetLocation.file != checkingP.location.file && targetLocation.rank != checkingP.location.rank ){
                   
                    return false;
                }
        case 'q':
                if(targetLocation.file == checkingP.location.file) {
                    
                    i= cX>tX ? tX+1:cX+1 ;
                    stop = cX>tX ? cX:tX; 
                    for(i; i < stop;i++){
                        
                        if ((*this)[i][tY].type != 'e'){
                            
                            return false;
                        }
                    }
                if(targetLocation.rank == checkingP.location.rank) {
                    i= cY>tY ? tY+1:cY+1 ;
                    stop = cY>tY ? cY:tY; 
                    for(int i;i<stop;i++){
                        cout <<i<<stop<<endl;    
                        if ((*this)[i][cX].type != 'e'){
                           
                            return false;
                        }
                    }

                }
                if(checkingP.type == 'r')
                    return true;
        case 'b':
                if( abs(cX-tX)== abs(cY-tY)){
                    for(int x = cX+1 , y = cY+1 ; x < tX && y <tY ; ++x, ++y   ){
                        if((*this)[x][y].type != 'e'){
                           
                            return false;
                        }
                    }
                    return true;
                    
                    
                }
                else 
                    return false;

                break;   

        case 'k':
                if((abs(cX -tX)==1 && abs(cY-tY)==1)|| (abs(cX -tX)==1 && abs(cY-tY)==0)|| (abs(cX -tX)==0 && abs(cY-tY)==1))
                    return true;
                else{
                    return false;
                }

                break;
        case 'n':
                if((abs(cX -tX)==1 && abs(cY-tY)==2) ||(abs(cX -tX)==2 && abs(cY-tY)==1) )
                    return true;
                else 
                    false;
                break;
        case 'p':
                
                cout << cY <<cX << endl;
                cout << tY <<tX << endl;

                
                cout << (*this)[tX][tY].type << endl;
                cout << abs(tX-cX) << endl;
                if(abs(tX-cX)== 1 &&(*this)[tX][tY].type == 'e'){
                                        cout << "2test"<<endl;
                    cout << "is here "<< endl ;
                    return true;
                }

                if(abs(tX-cX)== 2 && ( cY == 1 || cY==6  )&& (*this)[tX][tY].type == 'e'){
                                        cout << "1test"<<endl;
                    return true;
                }

                cout << "test"<<endl;
                return false;    
                break;


    }
    return false;

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


// cL is current Location , tL is target location
Board& Board::update(const coordinate cL, const coordinate tL){ 
    vector <int> currentLoction = cL.coordinateToInt();
    vector <int> targetLocation = tL.coordinateToInt();


    bool test = (*this).checkValidity((*this).pieces[currentLoction[0]][currentLoction[1]],tL);
    cout << test<<endl;


    // write check function in here later
    if(test){

        (*this).pieces[targetLocation[0]][targetLocation[1]]  =  (*this).pieces[currentLoction[0]][currentLoction[1]] ;
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
    while(true){
            cout<< "enter move: ";
            cin >>cf>>cr>>tf>>tr;
            coordinate cL(cf,cr);
            coordinate tL(tf,tr);


            board.update(cL,tL);
            board.print();

    }

}




