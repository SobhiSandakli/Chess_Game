#pragma once 
#include "StartupPositions.h"
namespace model 
{
    class StartPositions2 : public StartPositions
    {
        public:
            StartPositions2() = default;

            void set(class Chessboard *board) override;
    }
}