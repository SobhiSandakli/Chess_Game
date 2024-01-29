#include "StartupPositions4.h"

namespace model 
{
    void StartupPosition4::set(class ChessBoard* board)
    {
        board->addPiece(new King (0 , 0 , Color::black ));
        board->addPiece(new Bishop (1 , 1, Color::black));
        board->addPiece(new Bishop (2 , 2, Color::black));
        board->addPiece(new Rock (1 , 0 , Color::black));
        board->addPiece(new Rock (0 , 1 , Color::black));
    
        board->addPiece(new King (7 , 7 , Color::white));
        board->addPiece(new Bishop (6 , 6 , Color::white));
        board->addPiece(new Bishop (5 , 5 , Color::white));
        board->addPiece(new Rook (6 , 7 , Color::white));
        board->addPiece(new Rook (7 , 6 , Color::white));
        
    }
}