
#include "Bishop.h"

namespace model 
{
	Bishop::Bishop(int x, int y, const Color& color) : 
		AbsPiece(x, y, color, "Bishop") 
	{ 
	}

	bool Bishop::isValidPieceMove(int x, int y) const
	{
		return abs(y - y_) == abs(x - x_);
	}
}						