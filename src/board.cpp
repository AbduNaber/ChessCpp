
#include "header/chess.h"

vector <coordinate> Board::suggestion(int color){
    vector <coordinate> dummy = {coordinate(),coordinate()};
    return dummy ;
};



Piece Board::getPiece(const coordinate &cL) const{
    vector <int> cLoc = cL.coordinateToInt();

    return (*this)[cLoc[0]][cLoc[1]];


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



/*
    checks under attacks pieces
    pin each pieces to attack 
*/
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
/*calculate the point 
    sum of piece.point
*/
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

bool Board::checkValidity(Piece checkingP, coordinate targetLocation,int flag=1){

    if(targetLocation.file < 'a' || targetLocation.file > 'h' || targetLocation.rank < '1' || targetLocation.rank > '8'){
        if(flag)
            if(flag)
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
            if(flag)
                cout << "target is same piece or you choosed empty piece"<<endl;
        return false;
    }

    switch (checkingP.type){
          
        case 'r':
                if(targetLocation.file != checkingP.location.file && targetLocation.rank != checkingP.location.rank ){
                    if(flag)    
                        cout << "piece and target not same line vertically and horizontally"<<endl;
                    return false;
                }
        // broken movement fix that
        case 'q':
 
                if(targetLocation.file == checkingP.location.file) {
                        

                    for(i = cX>tX ? tX+1:cX+1; i < stop;i++){
                        
                        if ((*this)[i][tY].type != 'e'){
                            if(flag)
                                cout << "between two pieces is not empty"<<endl;    
                            return false;
                        }
                    }
                }    
                if(targetLocation.rank == checkingP.location.rank) {
                    
                    for(i=cY>tY ? tY+1:cY+1;i<stop;i++){
   
                        if ((*this)[cX][i].type != 'e'){
                            if(flag)
                                cout << "between two pieces is not empty"<<endl;
                            return false;
                        }
                    }

                }
                if(checkingP.type == 'r')
                    return true;
        // broken movement fix that
        case 'b':
               
                if (abs(cX - tX) == abs(cY - tY)) {

                    int x = cX < tX ? 1 : -1;
                    int y = cY < tY ? 1 : -1;
  
                    for (int i = 1; i < abs(cX - tX); ++i) {
                        if ((*this)[cX + i * x][cY + i * y].type != 'e') 
                            if(flag)
                                cout << "between two pieces is not empty"<<endl;
                            return false;
                    }
                        return true;
                } 
                else {
                    if(flag)
                    cout << "two pieces are not diagonal"<<endl;
                    return false;
                }
              
                break;   

        case 'k':
                if((abs(cX -tX)==1 && abs(cY-tY)==1)|| (abs(cX -tX)==1 && abs(cY-tY)==0)|| (abs(cX -tX)==0 && abs(cY-tY)==1))
                    return true;
                else{
                    if(flag)
                    cout << "target move is not 1 suqare away"<<endl;
                    return false;
                }

                break;
        case 'n':

                if((abs(cX -tX)==1 && abs(cY-tY)==2) ||(abs(cX -tX)==2 && abs(cY-tY)==1) ){

                    return true;
                }
                    
                else {
                    if(flag)
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
                if(abs(tY-cY)== 1 && abs(cX-tX)== 1 &&(*this)[tX][tY].type != 'e')
                    return true;
                    
                if(flag)
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


bool Board::checkMateSim(int color) const {
    Board temp = (*this);
    // Find the king's location
    coordinate kingLocation;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (temp.pieces[i][j].type == 'k' && temp.pieces[i][j].color == color) {
                kingLocation = temp.pieces[i][j].location;
                break;
            }
        }
    }

    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (temp.pieces[i][j].color == color && temp.pieces[i][j].type != 'k') {
                
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        coordinate currentLocation = temp.pieces[i][j].location;
                        coordinate targetLocation('a' + x, '1' + y);

                        
                        if (currentLocation.ok && targetLocation.ok && temp.checkValidity(pieces[i][j], targetLocation,0)) {

                            
                           

                            
                            temp.update(currentLocation, targetLocation);

                            
                            temp.resetAP();
                            temp.checkUnderAttack();

                            
                            if (!temp.pieces[kingLocation.coordinateToInt()[0]][kingLocation.coordinateToInt()[1]].isUnderAttack) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    // If no legal moves were found for any piece, it's checkmate
    return true;
}



coordinate  Board::kingLocation(int color) const{
    coordinate kingLocation;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (pieces[i][j].type == 'k' && pieces[i][j].color == color) {
                kingLocation = pieces[i][j].location;
                break;
            }
        }
    }
    return kingLocation;
}
