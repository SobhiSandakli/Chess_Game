
#include "King.h"

namespace model 
{
	int King::numberOfKings_ = 0;

	King::King(int x, int y, const Color& color) : 
		AbsPiece(x, y, color, "King")
	{ 
		if (King::numberOfKings_ < 2)
			King::numberOfKings_++;
		else
			throw TooManyKingsException("Two kings already exist");
	}

	King::~King()
	{
		King::numberOfKings_--;
	}

	bool King::isValidPieceMove(int x, int y) const
	{
		const bool isValidX = (x_ - 1 <= x) && (x <= x_ + 1);
		const bool isValidY = (y_ - 1 <= y) && (y <= y_ + 1);
		return isValidX && isValidY;
	}

}