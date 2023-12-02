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
        friend ostream&  operator<<(ostream& out, const coordinate& c) {
            out << "f: "<< c.file <<" r: "<<c.rank << endl; 
            return out;
        }

        friend class Board;
    private:
        char file;
        char rank;
    
};

class Piece{
    public:

        Piece(): color(-1), type('d'),point(0.0),isUnderAttack(false){};
        Piece(int pColor,char pType,coordinate pLocation,double pPoint) : color(pColor), type(pType),location(pLocation),point(pPoint),isUnderAttack(false){}; 
        
        static Piece createRook(int pColor,coordinate pLocation) { return Piece(pColor,'r',pLocation,5); };
        static Piece createPawn(int pColor,coordinate pLocation) { return Piece(pColor,'p',pLocation,1); };
        static Piece createKnight(int pColor,coordinate pLocation) { return Piece(pColor,'n',pLocation,3); };
        static Piece createBishop(int pColor,coordinate pLocation) { return Piece(pColor,'b',pLocation,3); };
        static Piece createQueen(int pColor,coordinate pLocation) { return Piece(pColor,'q',pLocation,9); };
        static Piece createKing(int pColor,coordinate pLocation) { return Piece(pColor,'k',pLocation,999); };
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
         friend ostream&  operator<<(ostream& out, const Piece& p) {
            out << p.type << " "<< p.location ;
            return out;

         }

    private:
        // 0: black , 1:white,  2:empty
        int color ;
        char type;
        coordinate location;
        double point;
        bool isUnderAttack ;
};

class Board{

    public:
    
        Board(): pieces(8,vector<Piece>(8)){};

        Board& init();

        void print() const;

        bool update(const coordinate cL, const coordinate tL);
        Board& check();
        int saveToFile();
        void setEmpty();
        bool checkValidity(Piece checkingP, coordinate targetLocation);
        void checkUnderAttack() ;


        const vector<Piece>& operator[](int index) const {
            return pieces[index];
        }
        std::vector<Piece>& operator[](int index) {

        return pieces[index];

        }


    private:
           
       vector<vector<Piece>> pieces; // pieces on 8x8 table.
};  

void Board::checkUnderAttack() {

    vector <int> currentLoction;
    int tX = currentLoction[0];
    int tY = currentLoction[1];
    for (vector <Piece> row: pieces){
        for(Piece p: row){

            currentLoction = p.location.coordinateToInt();
            
            switch(p.type){

                case 'p':
                    
                        if( p.location.file != 'a'){
                            if(p.color == 0){
                                if((*this)[tX+1][tY+1].type != 'e'){
                                    (*this)[tX+1][tY+1].isUnderAttack = true;
                                    (*this)[tX+1][tY+1].point = (*this)[tX+1][tY+1].point/2.0;
                                }

                            }
                            else if (p.color == 1){

                            }         
                        }
                        if(p.location.file != 'h'){
                            if(p.color == 0){
                                    
                            }
                            else if (p.color == 1){

                            }    
                        }

                    
                    
                case 'r':

                case 'n':

                case 'b':

                case 'q':

                case 'k':

            }
        }
    }
}



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

    
    int i;
    int stop = cY>tY ? cY:tY; 

    if (checkingP.color == (*this)[tX][tY].color || checkingP.type == 'e'){
        cout << "target is same piece or you choosed empty piece"<<endl;
        return false;
    }

    switch (checkingP.type){
          
        case 'r':
                if(targetLocation.file != checkingP.location.file && targetLocation.rank != checkingP.location.rank ){
                    cout << "piece and target not same line vertically and horizontally"<<endl;
                    return false;
                }
        case 'q':
 
                if(targetLocation.file == checkingP.location.file) {


                    for(i = cX>tX ? tX+1:cX+1; i < stop;i++){
                        
                        if ((*this)[i][tY].type != 'e'){
                            cout << "between two pieces is not empty"<<endl;    
                            return false;
                        }
                    }
                }    
                if(targetLocation.rank == checkingP.location.rank) {
                    
                    for(i=cY>tY ? tY+1:cY+1;i<stop;i++){
   
                        if ((*this)[cX][i].type != 'e'){
                            cout << "between two pieces is not empty"<<endl;
                            return false;
                        }
                    }

                }
                if(checkingP.type == 'r')
                    return true;
        case 'b':
               
                if (abs(cX - tX) == abs(cY - tY)) {

                    int x = cX < tX ? 1 : -1;
                    int y = cY < tY ? 1 : -1;
  
                    for (int i = 1; i < abs(cX - tX); ++i) {
                        if ((*this)[cX + i * x][cY + i * y].type != 'e') 
                            cout << "between two pieces is not empty"<<endl;
                            return false;
                    }
                        return true;
                } 
                else {
                    cout << "two pieces are not diagonal"<<endl;
                    return false;
                }
              
                break;   

        case 'k':
                if((abs(cX -tX)==1 && abs(cY-tY)==1)|| (abs(cX -tX)==1 && abs(cY-tY)==0)|| (abs(cX -tX)==0 && abs(cY-tY)==1))
                    return true;
                else{
                    cout << "target move is not 1 suqare away"<<endl;
                    return false;
                }

                break;
        case 'n':

                if((abs(cX -tX)==1 && abs(cY-tY)==2) ||(abs(cX -tX)==2 && abs(cY-tY)==1) ){

                    return true;
                }
                    
                else {
                    cout << "Knight movement is not L"<<endl;
                    return false;
                }
                    
                break;
        case 'p':
                
                if(abs(tX-cX)== 1 &&(*this)[tX][tY].type == 'e'){

                    return true;
                }

                if(abs(tX-cX)== 2 && ( cX == 1 || cX==6  )&& (*this)[tX][tY].type == 'e'){
                                        
                    return true;
                }
                cout << "pawn movement is not legal"<<endl;
                return false;    
                break;

    }
    return false;

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
                pieces[7][6] = Piece::createKnight(1,coordinate('g','1'));
                pieces[7][1] = Piece::createKnight(1,coordinate('b','1'));
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
        for(int j =0;j<8;++j){
            
            pieces[i][j] = Piece::createEmpty(coordinate('a'+j,8-i+'0'));
        }
            
    

        
    return *this;
}
// cL is current Location , tL is target location
bool Board::update(const coordinate cL, const coordinate tL){

    vector <int> currentLoction = cL.coordinateToInt();
    vector <int> targetLocation = tL.coordinateToInt();

    bool test = (*this).checkValidity((*this).pieces[currentLoction[0]][currentLoction[1]],tL);

    // write check function in here later
    if(test){

        (*this).pieces[currentLoction[0]][currentLoction[1]].location = (*this).pieces[targetLocation[0]][targetLocation[1]] .location;
        (*this).pieces[targetLocation[0]][targetLocation[1]]  =  (*this).pieces[currentLoction[0]][currentLoction[1]] ;
        (*this).pieces[currentLoction[0]][currentLoction[1]] = Piece::createEmpty(cL);
    }
    return test;
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
    cout<<"   ";
    for(int i =0;i<16;++i)
        cout <<"-";
    cout<<endl <<"   ";
    for(int i =0 ;i<8;++i){
        cout<<" "<<static_cast<char>('a'+i);
    }
     cout <<endl;   
}

int main(){

    Board board;

    board.init();
    board.print();
    char cr,cf,tf,tr;
    while(true){
            cout<< "enter move: ";
            cin >>cf>>cr>>tf>>tr;
            cin.clear();
            coordinate cL(cf,cr);
            coordinate tL(tf,tr);
            

            if(board.update(cL,tL))
                board.print();

    }

}




