
#pragma once
#include <QObject>
#include <memory>
#include <unordered_map>

#include <cppitertools/range.hpp>
#include <algorithm>
#include "StartupPositions.h"
#include "King.h"
using namespace std;

namespace model 
{
	constexpr const int width = 8;
	constexpr const int height = 8;

	constexpr const pair defaultPosition(999, 999);

	class Chessboard : public QObject
	{
		Q_OBJECT;

	signals:
		void checkSignal(int x, int y) const;

		void gameover();

		void pieceAdded(int x, int y, string type, string pieceColor);

	public:
		Chessboard();

		bool isValidMove(AbsPiece* piece, int x, int y);


		bool movePiece(AbsPiece* piece, int x, int y);


		void addPiece(AbsPiece* piece);
		 

		inline AbsPiece* getPiece(int x, int y) const { return board_[x][y].get(); };
		
		
		inline const Color& getColor() const { return currentPlayer_; };

		
		void startGame(class StartupPositions* strategy);

	private:

		void initialize(class StartupPositions* strategy);


		void clear();


		bool isCorrectColor(const Color& pieceColor) const;


		bool isLegalMove(AbsPiece* piece, int x, int y) const;


		bool isInsideBoard(int x, int y) const;


		bool isBlockedMove(AbsPiece* piece, int x, int y) const;


		void removePiece(int x, int y);


		void update();


		void updatePossibleMoves(AbsPiece* piece);


		void togglePlayerTurn();

		void nextTurn();


		bool isRivalKingCheck(AbsPiece* piece) const;


		const pair<int, int> getRivalKingPosition(const Color& pieceColor) const;


		bool alliedKingBecomesChecked(AbsPiece* piece, int x, int y);


		const pair<int, int> getAlliedKingPosition(const Color& pieceColor) const;


		void setKingPosition(const AbsPiece* king);


		bool isCheckMate();

		bool isStaleMate();


		unordered_map<AbsPiece*, vector<pair<int, int>>> possibleMoves_;


		unique_ptr<AbsPiece> board_[width][height];


		pair<int, int> whiteKingPosition_;
		pair<int, int> blackKingPosition_;


		Color currentPlayer_;

		friend class Tester;
	};
}