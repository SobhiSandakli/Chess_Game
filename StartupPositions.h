
#pragma once

#include <iostream>

#include "ChessBoard.h"
#include "Bishop.h"
#include "Rook.h"

namespace model
{
	class StartupPositions
	{
	public:
		StartupPositions() = default;
		virtual ~StartupPositions() = default;

		virtual void set(class Chessboard* board) = 0;
	};
}