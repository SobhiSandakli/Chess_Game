
#pragma once
#include "QObject"

#include "Chessboard.hpp"

#include "StartupPositions1.hpp"
#include "StartupPositions2.hpp"
#include "StartupPositions3.hpp"
#include "StartupPositions4.hpp"

namespace control
{
	class Controller : public QObject
	{
		Q_OBJECT

	public slots:
		void forwardCheck(int x, int y);

		void forwardGameover();

		void forwardPieceAdded(int x, int y, std::string type, std::string pieceColor);

	signals:
		void invalidMove(int x, int y);

		void notifyCheck(int x, int y);

		void notifyPieceAdded(int x, int y, std::string type, std::string pieceColor);

		void notifyGameover();

	public:
		Controller();
		~Controller();
		void startGame(int strategyNumber);

		bool move(int sourceX, int sourceY, int destinationX, int destinationY);

		inline const model::Color& getColor() const { return board_->getColor(); };

		inline model::AbsPiece* getPiece(int x, int y) const { return board_->getPiece(x, y); }

		bool isValidTile(int x, int y) const;

	private:
		model::StartupPositions* getStrategy(int strategyNumber);

		model::Chessboard* board_;
	};
}