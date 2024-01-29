/*
* Fichier contenant les tests unitaires sur le mod�le
* \file UnitTests.cpp
* \author Erreur-404 et Mo-LK
* \date 25 avril 2022
* Cr�� le 25 avril 2022
*/

#include "Tester.hpp"
#include "King.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "StartupPositions1.hpp"
#include "StartupPositions2.hpp"
#include "StartupPositions3.hpp"
#include "StartupPositions4.hpp"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

namespace model 
{
	TEST(Chessboard, King) {
		Chessboard board;
		King* king = new King(5, 5, Color::black);
		board.addPiece(king);
		bool isValid = board.isValidMove(king, 6, 6);
		EXPECT_TRUE(isValid);
		isValid = board.isValidMove(king, 5, 6);
		EXPECT_TRUE(isValid);
		isValid = board.isValidMove(king, 0, 0);
		EXPECT_FALSE(isValid);
		isValid = board.isValidMove(king, 5, 5);
		EXPECT_FALSE(isValid);

		King* enemyKing = new King(6, 6, Color::white);
		board.addPiece(enemyKing);
		isValid = board.isValidMove(king, 6, 6);
		EXPECT_TRUE(isValid);
	}

	TEST(Chessboard, Bishop) {
		Chessboard board;
		Bishop* bishop = new Bishop(4, 4, Color::white);
		board.addPiece(bishop);
		bool isValid = board.isValidMove(bishop, 7, 1);
		EXPECT_TRUE(isValid);
		isValid = board.isValidMove(bishop, 0, 0);
		EXPECT_TRUE(isValid);
		isValid = board.isValidMove(bishop, 0, 4);
		EXPECT_FALSE(isValid);
		isValid = board.isValidMove(bishop, 4, 0);
		EXPECT_FALSE(isValid);
		isValid = board.isValidMove(bishop, 4, 4);
		EXPECT_FALSE(isValid);

		Bishop* enemyBishop = new Bishop(1, 1, Color::black);
		board.addPiece(enemyBishop);
		isValid = board.isValidMove(bishop, 0, 0);
		EXPECT_FALSE(isValid);
		isValid = board.isValidMove(bishop, 1, 1);
		EXPECT_TRUE(isValid);
	}

	TEST(Chessboard, Rook) {
		Chessboard board;
		Rook* rook = new Rook(4, 4, Color::black);
		board.addPiece(rook);
		bool isValid = board.isValidMove(rook, 0, 4);
		EXPECT_TRUE(isValid);
		isValid = board.isValidMove(rook, 4, 0);
		EXPECT_TRUE(isValid);
		isValid = board.isValidMove(rook, 0, 0);
		EXPECT_FALSE(isValid);
		isValid = board.isValidMove(rook, 7, 1);
		EXPECT_FALSE(isValid);
		isValid = board.isValidMove(rook, 4, 4);
		EXPECT_FALSE(isValid);

		Rook* enemyRook = new Rook(2, 4, Color::white);
		board.addPiece(enemyRook);
		isValid = board.isValidMove(rook, 0, 4);
		EXPECT_FALSE(isValid);
		isValid = board.isValidMove(rook, 2, 4);
		EXPECT_TRUE(isValid);
	}

	TEST(Chessboard, Turn) {
		Chessboard board;
		King* whiteKing = new King(7, 7, Color::white);
		King* blackKing = new King(0, 0, Color::black);
		board.addPiece(whiteKing);
		board.addPiece(blackKing);

		bool isValid = board.movePiece(blackKing, 1, 1);
		EXPECT_FALSE(isValid);
		isValid = board.movePiece(whiteKing, 6, 6);
		EXPECT_TRUE(isValid);

		isValid = board.movePiece(whiteKing, 5, 5);
		EXPECT_FALSE(isValid);
		isValid = board.movePiece(blackKing, 1, 1);
		EXPECT_TRUE(isValid);

		isValid = board.movePiece(blackKing, 2, 2);
		EXPECT_FALSE(isValid);
		Color currentPlayer = board.getColor();
		EXPECT_EQ(currentPlayer, Color::white);
	}

	TEST(Chessboard, Check) {
		Chessboard board;
		King* king = new King(0, 0, Color::white);
		Bishop* enemyBishop = new Bishop(5, 5, Color::black);
		board.addPiece(king);
		board.addPiece(enemyBishop);

		bool isValid = board.isValidMove(king, 1, 1);
		EXPECT_FALSE(isValid);
		isValid = board.isValidMove(king, 0, 1);
		EXPECT_TRUE(isValid);
	}

	TEST(Chessboard, BlockedCheckMate) {
		Chessboard board;
		Bishop* attacker = new Bishop(3, 4, Color::white);
		board.addPiece(new King(3, 0, Color::black));
		board.addPiece(new Bishop(2, 0, Color::black));
		board.addPiece(new Bishop(5, 2, Color::black));
		board.addPiece(new Rook(5, 0, Color::black));

		board.addPiece(new King(3, 7, Color::white));
		board.addPiece(new Bishop(1, 3, Color::white));
		board.addPiece(attacker);
		board.addPiece(new Rook(2, 6, Color::white));
		board.addPiece(new Rook(4, 6, Color::white));

		board.movePiece(attacker, 5, 2);
		Tester tester;
		EXPECT_FALSE(tester.testIsCheckMate(board));
	}

	TEST(Chessboard, CheckMate) {
		Chessboard board;
		Bishop* attacker = new Bishop(3, 4, Color::white);
		board.addPiece(new King(3, 0, Color::black));
		board.addPiece(new Bishop(2, 0, Color::black));
		board.addPiece(new Bishop(5, 2, Color::black));

		board.addPiece(new King(3, 7, Color::white));
		board.addPiece(new Bishop(1, 3, Color::white));
		board.addPiece(attacker);
		board.addPiece(new Rook(2, 6, Color::white));
		board.addPiece(new Rook(4, 6, Color::white));

		board.movePiece(attacker, 5, 2);
		Tester tester;
		EXPECT_TRUE(tester.testIsCheckMate(board));
	}

	TEST(StartupPositions, Strategy1){
		Chessboard board;
		StartupPositions1 strategy;

		board.startGame(&strategy);
		bool isRook = typeid(Rook) == typeid(*board.getPiece(0, 0));
		EXPECT_TRUE(isRook);

		isRook = typeid(Rook) == typeid(*board.getPiece(7, 0));
		EXPECT_TRUE(isRook);

		bool isBishop = typeid(Bishop) == typeid(*board.getPiece(2, 0));
		EXPECT_TRUE(isBishop);

		isBishop = typeid(Bishop) == typeid(*board.getPiece(5, 0));
		EXPECT_TRUE(isBishop);

		bool isKing = typeid(King) == typeid(*board.getPiece(3, 0));
		EXPECT_TRUE(isKing);

		isRook = typeid(Rook) == typeid(*board.getPiece(0, 7));
		EXPECT_TRUE(isRook);

		isRook = typeid(Rook) == typeid(*board.getPiece(7, 7));
		EXPECT_TRUE(isRook);

		isBishop = typeid(Bishop) == typeid(*board.getPiece(2, 7));
		EXPECT_TRUE(isBishop);

		isBishop = typeid(Bishop) == typeid(*board.getPiece(5, 7));
		EXPECT_TRUE(isBishop);

		isKing = typeid(King) == typeid(*board.getPiece(3, 7));
		EXPECT_TRUE(isKing);
	}

	TEST(StartupPositions, Strategy2) {
		Chessboard board;
		StartupPositions2 strategy;

		board.startGame(&strategy);

		bool isBishop = typeid(Bishop) == typeid(*board.getPiece(0, 0));
		EXPECT_TRUE(isBishop);

		bool isKing = typeid(King) == typeid(*board.getPiece(3, 0));
		EXPECT_TRUE(isKing);

		bool isRook = typeid(Rook) == typeid(*board.getPiece(7, 7));
		EXPECT_TRUE(isRook);

		isKing = typeid(King) == typeid(*board.getPiece(3, 7));
		EXPECT_TRUE(isKing);
	}

	TEST(StartupPositions, Strategy3) {
		Chessboard board;
		StartupPositions3 strategy;

		board.startGame(&strategy);
		bool isRook = typeid(Rook) == typeid(*board.getPiece(3, 4));
		EXPECT_TRUE(isRook);

		isRook = typeid(Rook) == typeid(*board.getPiece(5, 4));
		EXPECT_TRUE(isRook);

		bool isBishop = typeid(Bishop) == typeid(*board.getPiece(4, 5));
		EXPECT_TRUE(isBishop);

		isBishop = typeid(Bishop) == typeid(*board.getPiece(4, 3));
		EXPECT_TRUE(isBishop);

		bool isKing = typeid(King) == typeid(*board.getPiece(4, 4));
		EXPECT_TRUE(isKing);

		isRook = typeid(Rook) == typeid(*board.getPiece(0, 4));
		EXPECT_TRUE(isRook);

		isRook = typeid(Rook) == typeid(*board.getPiece(7, 4));
		EXPECT_TRUE(isRook);

		isBishop = typeid(Bishop) == typeid(*board.getPiece(4, 0));
		EXPECT_TRUE(isBishop);

		isBishop = typeid(Bishop) == typeid(*board.getPiece(4, 7));
		EXPECT_TRUE(isBishop);

		isKing = typeid(King) == typeid(*board.getPiece(7, 7));
		EXPECT_TRUE(isKing);
	}

	TEST(StartupPositions, Strategy4) {
		Chessboard board;
		StartupPositions4 strategy;

		board.startGame(&strategy);
		bool isRook = typeid(Rook) == typeid(*board.getPiece(1, 0));
		EXPECT_TRUE(isRook);

		isRook = typeid(Rook) == typeid(*board.getPiece(0, 1));
		EXPECT_TRUE(isRook);

		bool isBishop = typeid(Bishop) == typeid(*board.getPiece(1, 1));
		EXPECT_TRUE(isBishop);

		isBishop = typeid(Bishop) == typeid(*board.getPiece(2, 2));
		EXPECT_TRUE(isBishop);

		bool isKing = typeid(King) == typeid(*board.getPiece(0, 0));
		EXPECT_TRUE(isKing);

		isRook = typeid(Rook) == typeid(*board.getPiece(6, 7));
		EXPECT_TRUE(isRook);

		isRook = typeid(Rook) == typeid(*board.getPiece(7, 6));
		EXPECT_TRUE(isRook);

		isBishop = typeid(Bishop) == typeid(*board.getPiece(6, 6));
		EXPECT_TRUE(isBishop);

		isBishop = typeid(Bishop) == typeid(*board.getPiece(5, 5));
		EXPECT_TRUE(isBishop);

		isKing = typeid(King) == typeid(*board.getPiece(7, 7));
		EXPECT_TRUE(isKing);
	}

	TEST(King, exception) {
		Chessboard board;
		King* firstKing = new King(0, 0, Color::white);
		King* secondKing = new King(7, 7, Color::black);
		// Cette ligne �met une erreur puisque j'y instancie une variable, mais
		// je ne l'utilise pas. C'est toutefois tout � fait normale puisque 
		// c'est l'instantiation de la variable que je souhaite tester et non
		// son utilisation
		EXPECT_THROW(King* thirdKing = new King(4, 4, Color::white), TooManyKingsException);
		delete firstKing;
		delete secondKing;
	}

	TEST(Chessboard, OutsideBoardMove) {
		Chessboard board;
		Bishop* bishop = new Bishop(0, 0, Color::white);
		board.addPiece(bishop);
		EXPECT_FALSE(board.movePiece(bishop, 64, 64));
	}
}

#endif