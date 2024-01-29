#pragma once 
#include "StartupPositions.h"
namespace model 
{
    class StartPositions4 : public StartPositions
    {
        public:
            StartPositions4() = default;

            void set(class Chessboard *board) override;
    }
}