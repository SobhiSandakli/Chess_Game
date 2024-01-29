
#pragma once

#include "AbsPiece.h"

namespace model 
{

	class Rook : public AbsPiece
	{
	public:
		Rook() = default;
		Rook(int x, int y, const Color& color);
		virtual ~Rook() = default;

	protected:
		bool isValidPieceMove(int x, int y) const override;
	};

}