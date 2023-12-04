
#include "header/chess.h"



using namespace std;
coordinate::coordinate(char pFile, char pRank):  file(pFile) , rank(pRank){
            if(file <'a' || file > 'h' || rank > '8' || rank < '1'){

                
                ok = false;

            }
            else    
                ok = true;

        };
ostream&  operator<<(ostream& out, const coordinate& c) {
            out << "f: "<< c.file <<" r: "<<c.rank << endl; 
            return out;
        }
vector<int> coordinate::coordinateToInt() const {
            
            // convert coordinant system to vector index for checking piece and target location
            int y = file - 97;
            int x = 8- (rank -'0') ; 
            vector<int> result= {x,y};
            return result;

    }

const Piece& Piece::operator=(const Piece& o){
            color = o.color;
            type = o.type;
            location = o.location;
            point = o.point;
            isUnderAttack = o.isUnderAttack;
            return *this;
}

ostream&  operator<<(ostream& out, const Piece& p) {
            out << p.type << " "<< p.location <<" p:"<<p.point<<" c:"<<p.color<< " a: "<<p.isUnderAttack;
            return out;

}