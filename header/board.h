#pragma ONCE
#include "piece.h"
class Board{

    public:
    
        Board(): pieces(8,vector<Piece>(8)){};

        Board& init();

        void print() const;
        
        bool update(const coordinate cL, const coordinate tL);
        Board& check();
        int saveToFile()const;
        bool loadFromFile();
        bool checkValidity(Piece checkingP, coordinate targetLocation,int flag);
        void checkUnderAttack() ;
        vector <double> calculatePoint() const ;
        void isCheckMate();
        bool checkMateSim(int color) const;
        coordinate  kingLocation(int color) const;
        Piece getPiece(const coordinate &cL) const;
        vector <coordinate> suggestion(int color);
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
