#pragma once 
#include "StartupPositions.h"
namespace model 
{
    class StartPositions3 : public StartPositions
    {
        public:
            StartPositions3() = default;

            void set(class Chessboard *board) override;
    }
}