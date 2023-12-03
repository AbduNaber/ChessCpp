#include <iostream>
#include <fstream>
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

                
                ok = false;

            }
            else    
                ok = true;

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
        ~coordinate(){};
        bool ok; // valid move
    private:
        char file;
        char rank;
        
    
};

class Piece{
    public:

        Piece(): color(-1), type('d'),point(0.0),isUnderAttack(false){};
        Piece(int pColor,char pType,coordinate pLocation,double pPoint) : color(pColor), type(pType),location(pLocation),point(pPoint),isUnderAttack(false){}; 
        
        static Piece createRook(int pColor,coordinate pLocation) { return Piece(pColor,'r',pLocation,5.0); };
        static Piece createPawn(int pColor,coordinate pLocation) { return Piece(pColor,'p',pLocation,1.0); };
        static Piece createKnight(int pColor,coordinate pLocation) { return Piece(pColor,'n',pLocation,3.0); };
        static Piece createBishop(int pColor,coordinate pLocation) { return Piece(pColor,'b',pLocation,3.0); };
        static Piece createQueen(int pColor,coordinate pLocation) { return Piece(pColor,'q',pLocation,9.0); };
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
         friend ostream&  operator<<(ostream& out, const Piece& p) {
            out << p.type << " "<< p.location <<" p:"<<p.point<<" c:"<<p.color<< " a: "<<p.isUnderAttack;
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
        int saveToFile()const;
        bool loadFromFile();
        bool checkValidity(Piece checkingP, coordinate targetLocation);
        void checkUnderAttack() ;
        vector <double> calculatePoint() const ;
        void CheckMate();
        bool checkMateSim() const;
        const vector<Piece>& operator[](int index) const {
            return pieces[index];
        }
        std::vector<Piece>& operator[](int index) {

        return pieces[index];

        }
        void resetAP();

    private:
           
       vector<vector<Piece>> pieces; // pieces on 8x8 table.
};  

bool Board::loadFromFile(){

    ifstream inF("board.txt");

    if (!inF.is_open()) {
            cout << "Error opening the board.txt"<< endl;
            return false;
        }
    for(int row =0 ; row<8; ++row){
        string line;
        getline(inF, line);

        if(line.size() != 19 ){
            cout << "1corrupted file";
            return false;
        }
         int col = 0;
            for (int i = 4; i < line.size(); ++i) {
                
                if(line[i] == ' ')
                    continue;

                char pieceChar = line[i];
                
                // Assuming Piece::createEmpty creates an empty piece
                pieces[row][col] = Piece::createEmpty(coordinate(row, col));

                // Check the character and create the corresponding piece
                switch (pieceChar) {
                    case 'r':
                        pieces[row][col] = Piece::createRook(0, coordinate(row, col));
                        break;
                    case 'n':
                        pieces[row][col] = Piece::createKnight(0, coordinate(row, col));
                        break;
                    case 'b':
                        pieces[row][col] = Piece::createBishop(0, coordinate(row, col));
                        break;
                    case 'q':
                        pieces[row][col] = Piece::createQueen(0, coordinate(row, col));
                        break;
                    case 'k':
                        pieces[row][col] = Piece::createKing(0, coordinate(row, col));
                        break;
                    case 'p':
                        pieces[row][col] = Piece::createPawn(0, coordinate(row, col));
                        break;
                    case 'R':
                        pieces[row][col] = Piece::createRook(1, coordinate(row, col));
                        break;
                    case 'N':
                        pieces[row][col] = Piece::createKnight(1, coordinate(row, col));
                        break;
                    case 'B':
                        pieces[row][col] = Piece::createBishop(1, coordinate(row, col));
                        break;
                    case 'Q':
                        pieces[row][col] = Piece::createQueen(1, coordinate(row, col));
                        break;
                    case 'K':
                        pieces[row][col] = Piece::createKing(1, coordinate(row, col));
                        break;
                    case 'P':
                        pieces[row][col] = Piece::createPawn(1, coordinate(row, col));
                        break;
                    case '.':
                        pieces[row][col] = Piece::createEmpty(coordinate(row, col));
                        break;
                    default:
                        
                        return false;
                }

                ++col;
            }
        }

        inF.close();
        cout << "succses";
        return true;


    }

int Board::saveToFile()const{

    ofstream outF("board.txt");
    if (!outF.is_open()) {
        cerr << "Error opening the board file!" << std::endl;
        return 1;
    }

    for(int i =0;i<8;++i){
        outF<< 8-i << " |";
        for(int j=0;j<8;++j){

            if( pieces[i][j].color == 2) {
                outF<<" "<<".";
            }
            else if(pieces[i][j].color == 1 ){
                 outF<<" "<< static_cast<char>(pieces[i][j].type-32) ;
            }
            else if(pieces[i][j].color == 0){
                outF<<" "<< pieces[i][j].type;
            }

        }
        outF << endl;
    } 
    outF<<"   ";
    for(int i =0;i<16;++i)
        outF <<"-";
    outF<<endl <<"   ";
    for(int i =0 ;i<8;++i){
        outF<<" "<<static_cast<char>('a'+i);
    }
    outF <<endl; 
    return 0;
};

void Board::checkUnderAttack() {
    vector<int> currentLocation;
    int tX, tY, tP;

    for (vector<Piece> row : pieces) {
        for (Piece p : row) {

            if (p.type == 'e')
                continue;

            currentLocation = p.location.coordinateToInt();
            tX = currentLocation[0];
            tY = currentLocation[1];
            tP = (*this)[tX][tY].color == 0 ? 1 : -1;

            switch (p.type) {
                case 'p':
                    
                    if (p.location.file != 'a' && tX + tP >= 0 && tX + tP < 8 && tY - 1 >= 0) {
                        
                        if ((*this)[tX + tP][tY - 1].type != 'e' && (*this)[tX][tY].color != (*this)[tX + tP][tY - 1].color) {
                            
                            (*this)[tX + tP][tY - 1].isUnderAttack = true;
                            
                            (*this)[tX + tP][tY - 1].point /= 2.0;
                        }
                    }

                    if (p.location.file != 'h' && tX + tP >= 0 && tX + tP < 8 && tY + 1 < 8) {
                        if ((*this)[tX + tP][tY + 1].type != 'e' && (*this)[tX][tY].color != (*this)[tX + tP][tY + 1].color) {
                             
                            (*this)[tX + tP][tY + 1].isUnderAttack = true;
                            
                            (*this)[tX + tP][tY + 1].point /= 2.0;
                        }
                    }

                    break;

                case 'n':
                
                    for (int i : {-1, 1}) {
                        for (int j : {-2, 2}) {
                            int targetX = tX + i;
                            int targetY = tY + j;
                            if (targetX >= 0 && targetX < 8 && targetY >= 0 && targetY < 8 && (*this)[targetX][targetY].type != 'e') {
                                if ((*this)[targetX][targetY].color != p.color) {
                                    
                                    (*this)[targetX][targetY].isUnderAttack = true;
                                    (*this)[targetX][targetY].point /= 2.0;
                                }
                            }

                            targetX = tX + j;
                            targetY = tY + i;

                            if (targetX >= 0 && targetX < 8 && targetY >= 0 && targetY < 8 && (*this)[targetX][targetY].type != 'e') {
                                if ((*this)[targetX][targetY].color != p.color) {
                                    
                                    (*this)[targetX][targetY].isUnderAttack = true;
                                    (*this)[targetX][targetY].point /= 2.0;
                                }
                            }
                        }
                    }
                    break;

                case 'q':
                case 'r':
                    for (int i = tX + 1; i < 8; i++) {
                        if ((*this)[i][tY].type != 'e') {
                            if ((*this)[i][tY].color != p.color) {
                                (*this)[i][tY].isUnderAttack = true;
                                cout <<"5"<<endl;
                                (*this)[i][tY].point /= 2.0;
                            }
                            break;
                        }
                    }
                    for (int i = tX - 1; i >= 0; i--) {
                        if ((*this)[i][tY].type != 'e') {
                            if ((*this)[i][tY].color != p.color) {
                                (*this)[i][tY].isUnderAttack = true;
                                (*this)[i][tY].point /= 2.0;
                            }
                            break;
                        }
                    }
                    for (int j = tY + 1; j < 8; j++) {
                        if ((*this)[tX][j].type != 'e') {
                            if ((*this)[tX][j].color != p.color) {
                                (*this)[tX][j].isUnderAttack = true;
                                (*this)[tX][j].point /= 2.0;
                            }
                            break;
                        }
                    }
                    for (int j = tY - 1; j >= 0; j--) {
                        if ((*this)[tX][j].type != 'e') {
                            if ((*this)[tX][j].color != p.color) {
                                (*this)[tX][j].isUnderAttack = true;
                                (*this)[tX][j].point /= 2.0;
                            }
                            break;
                        }
                    }
                    if ((*this)[tX][tY].type == 'r')
                        break;

                case 'b':
                    for (int i = 1; tX + i < 8 && tY + i < 8; ++i) {
                        if ((*this)[tX + i][tY + i].type != 'e') {
                            if ((*this)[tX + i][tY + i].color != p.color) {
                                (*this)[tX + i][tY + i].isUnderAttack = true;
                                (*this)[tX + i][tY + i].point /= 2.0;
                            }
                            break;
                        }
                    }

                    for (int i = 1; tX - i >= 0 && tY + i < 8; ++i) {
                        if ((*this)[tX - i][tY + i].type != 'e') {
                            if ((*this)[tX - i][tY + i].color != p.color) {
                                (*this)[tX - i][tY + i].isUnderAttack = true;
                                (*this)[tX - i][tY + i].point /= 2.0;
                            }
                            break;
                        }
                    }

                    for (int i = 1; tX + i < 8 && tY - i >= 0; ++i) {
                        if ((*this)[tX + i][tY - i].type != 'e') {
                            if ((*this)[tX + i][tY - i].color != p.color) {
                                (*this)[tX + i][tY - i].isUnderAttack = true;
                                (*this)[tX + i][tY - i].point /= 2.0;
                            }
                            break;
                        }
                    }

                    for (int i = 1; tX - i >= 0 && tY - i >= 0; ++i) {
                        if ((*this)[tX - i][tY - i].type != 'e') {
                            if ((*this)[tX - i][tY - i].color != p.color) {
                                (*this)[tX - i][tY - i].isUnderAttack = true;
                                (*this)[tX - i][tY - i].point /= 2.0;
                            }
                            break;
                        }
                    }
                    break;

                case 'k':
                    for (int i = -1; i <= 1; ++i) {
                        for (int j = -1; j <= 1; ++j) {
                            int targetX = tX + i;
                            int targetY = tY + j;

                            if (targetX >= 0 && targetX < 8 && targetY >= 0 && targetY < 8) {
                                if ((*this)[targetX][targetY].type != 'e' && (*this)[targetX][targetY].color != p.color) {
                                    (*this)[targetX][targetY].isUnderAttack = true;
                                    (*this)[targetX][targetY].point /= 2.0;
                                }
                            }
                        }
                    }
                    break;
            }
        }
    }
}

 vector <double> Board::calculatePoint() const {

        double whitePoints = 0.0;
        double blackPoints = 0.0;

        for (const vector<Piece>& row : pieces) {
            for (const Piece& p : row) {

                if (p.color == 0) {
                    blackPoints += p.point;

                } 
                else if (p.color == 1) {
                    whitePoints += p.point;
                }
            }
        }
        vector <double> result = {blackPoints,whitePoints};
        return result;
 }

void Board::resetAP() {

    for (vector<Piece>& row : pieces) {
        for (Piece& p : row) {
                switch (p.type) {
                    case 'p':
                        p.point = 1.0;
                        break;
                    case 'n':
                        p.point = 3.0;
                        break;
                    case 'b':
                        p.point = 3.0;
                        break;
                    case 'r':
                        p.point = 5.0;
                        break;
                    case 'q':
                        p.point = 9.0;
                        break;
                    

                }
            p.isUnderAttack = false;
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
    cout << (*this).pieces[targetLocation[0]][targetLocation[1]]<<endl;
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
/*

void Board::CheckMate(){
    for (vector<Piece> &row : pieces) {
        for (Piece& p :row) {

            if(p.type != 'k')
                continue;
            
            while(p.isUnderAttack == true){

                string input;
                cout << "enter move: ";
                cin >> input;
                if( input.size() != 4){
                    continue;
                }

                coordinate cL(input[0],input[1]);

                coordinate tL(input[2],input[3]);

                if(!cL.ok || !tL.ok ){
                    cout << "enter valid move! "<<endl;
                    continue;
                }

                if(update(cL,tL))
                    print();
                
                resetAP();
                checkUnderAttack();

                
            }
            
            return;

        }
    }
}
*/
bool Board::checkMateSim() const{
     
};

class Game{
    public:

        static void help(){
            cout << "help "<<endl;
        };
        
        static int play(Board & board);
        static string getInput(){
                string input;
                cout<< "enter move: ";
                cin >>input;
                return input;
    
            }
        private:
            
    
};
int Game::play(Board & board){

    string input;
    int s;
    while(true){
    input = Game::getInput();
    if(input == "quit"){
                cout << "exit"<<endl;
                return 0;
            }
            else if(input == "save"){
                 
                s = board.saveToFile();
                cout << "saved status(0 is success): "<<s<<endl;
                continue;
            }  
            else if (input =="load"){
                s = board.loadFromFile();
                cout << "load status(1 is success): "<<s<<endl;
                board.print();
                continue;
            }  
            else if(input == "point"){
                const vector <double> r = board.calculatePoint();
                cout << "POINT -> w: " << r[1] << " b: "<< r[0]<<endl;
                continue;
            }

            else if(input == "suggest"){

            }
            else if(input == "help"){
                Game::help();
            }

            else if(input.length() == 4){
                cin.clear();

                coordinate cL(input[0],input[1]);

                coordinate tL(input[2],input[3]);
                cout << cL;
                cout <<tL<<endl;
                if(cL.ok == false || tL.ok == false ){
                    
                    cout << "invalid coordinatee try again"<<endl;
                    continue;
                }

                if(board.update(cL,tL))
                    board.print();

                board.resetAP();
                board.checkUnderAttack();
                board.CheckMate();
                

            }
            else {
                cout << "invalid input. "<<endl;
            }
}
    return 0;
}


int main(){ 

    Board board;

    board.init();
    board.print();
    Game::play(board);
    
    


}




