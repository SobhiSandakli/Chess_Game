#include "StartupPositions3.h"

namespace model 
{
    void StartPosition3::set(class ChessBoard* board)
    {
        board->addPiece(new King ( 4 , 4 , Color::black ) );
        board->addPiece(new Bishop ( 4 , 5 , Color::black ) );
        board->addPiece(new Bishop ( 4 , 3 , Color::black ) );
        board->addPiece(new Rook ( 3 , 4 , Color::black ) );
        board->addPiece(new Rook ( 5 , 4 , Color::black ) );

        board->addPiece(new King ( 7 , 7 , Color::white ) );
        board->addPiece(new Bishop ( 4 , 0 , Color::white ) );
        board->addPiece(new Bishop ( 4 , 7 , Color::white ) );
        board->addPiece(new Rook ( 0, 4 , Color::white ) );
        board->addPiece(new Rook ( 7, 4 , Color::white ) );
    
    
    }
}