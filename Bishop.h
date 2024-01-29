
#pragma once

#include <cstdlib>
#include "AbsPiece.h"

namespace model 
{

	class Bishop : public AbsPiece
	{
	public:
		Bishop() = default;
		Bishop(int x, int y, const Color& color);
		virtual ~Bishop() = default;
	
	protected:
		/*
		* Indique si le mouvement correspond � ceux permis par le Fou
		* \param x : Nouvelle position en x
		* \param y : Nouvelle position en y
		* \return La validit� du mouvement
		*/
		bool isValidPieceMove(int x, int y) const override;
	};

}