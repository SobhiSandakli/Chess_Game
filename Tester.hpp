#pragma once
#include "ChessBoard.h"

namespace model
{
    class Tester
    {
        public:
            Tester() = default;

            inline bool testIsCheckMate(Chessboard& board) {return board.isCheckMate()}

    };
}