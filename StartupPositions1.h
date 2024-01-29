#pragma once 
#include "StartupPositions.h"
namespace model 
{
    class StartPositions1 : public StartPositions
    {
        public:
            StartPositions1() = default;

            void set(class Chessboard *board) override;
    }
}