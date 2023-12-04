
#pragma ONCE


using namespace std;

class coordinate{

    public:

        coordinate():  file('a') , rank('1'){};

        coordinate(char pFile, char pRank);
        coordinate setCoordinate(char f,char r);
        vector <char> getCoordinate() const{return {file,rank};};
        

         vector<int> coordinateToInt() const ;
        friend ostream&  operator<<(ostream& out, const coordinate& c);
    	
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
                
        const Piece& operator=(const Piece& o);
         friend ostream&  operator<<(ostream& out, const Piece& p);
        int getColor() const{ return color;};

    private:
        // 0: black , 1:white,  2:empty
        int color ;
        char type;
        coordinate location;
        double point;
        bool isUnderAttack ;
};