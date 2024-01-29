#include "Rook.h"

namespace model
{
	Rook::Rook(int x, int y, const Color& color) : 
		AbsPiece(x, y, color, "Rook") 
	{
	}

	bool Rook::isValidPieceMove(int x, int y) const
	{
		const bool isHorizontalMove	= (x != x_) && (y == y_);
		const bool isVerticalMove	= (y != y_) && (x == x_);
		return isHorizontalMove ^ isVerticalMove;
	}
}