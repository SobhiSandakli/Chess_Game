#include "StartupPositions2.h"
namespace model 
{
    void StartupPositions2::set (class Chessboard* board)
    {
        board->addPiece(new King (3,0, Color::black));
        board->addPiece(new Bishop(0,0, Color::black));

        board->addPiece(new King (3,7,Color::white));
        board->addPiece(new Rook(7,7,Color::white));

    }
}