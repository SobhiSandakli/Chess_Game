
#include "AbsPiece.h"

namespace model
{
	AbsPiece::AbsPiece(
		int x, 
		int y, 
		const Color& color, 
		const std::string& type
	) : x_(x), y_(y), color_(color), type_(type)
	{}

	void AbsPiece::move(int x, int y)
	{
		x_ = x;
		y_ = y;
	}

	bool AbsPiece::isValidMove(int x, int y) const
	{
		const bool isSamePosition = (x == x_) && (y == y_);

		return !isSamePosition && isValidPieceMove(x, y);
	}

}