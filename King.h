
#pragma once

#include <stdexcept>
#include "AbsPiece.h"

namespace model 
{

	class King : public AbsPiece
	{
	public:
		King() = default;
		King(int x, int y, const Color& color);
		virtual ~King();

	protected:
		/*
		* Indique si le mouvement correspond � ceux permis par le Roi
		* \param x : Nouvelle position en x
		* \param y : Nouvelle position en y
		* \return La validit� du mouvement
		*/
		bool isValidPieceMove(int x, int y) const override;

	private:
		/* Le nombre de rois pr�sents sur l'�chiquier */
		static int numberOfKings_;
	};


	/* Erreur lanc�e lorsqu'on tente d'ins�rer plus de 2 rois */
	class TooManyKingsException: public std::logic_error
	{
	public:
		using std::logic_error::logic_error;
	};
}