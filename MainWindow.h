/**
* Fichier contenant la fen�tre principale. C'est elle qui affiche le jeu et qui re�oit les demandes de l'utilisateur.
* \file MainWindow.hpp
* \author Erreur-404 et Mo-LK
* \date 19 avril 2022
* Cr�� le 13 avril 2022
*/

#pragma once
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QTextFormat>
#include <QMenu>
#include <QMenuBar>
#include <QIcon>
#include <QPixmap>
#include <QGraphicsView>
#include <QLabel>
#include <QFont>
#include <QMessageBox>

#include <iostream>
#include <string>
#include <cppitertools/range.hpp>

#include "Tile.hpp"
#include "Controller.hpp"
#include "PositionSelectionWindow.hpp"

namespace view
{	
	constexpr const int margin = 100;
	
	constexpr const int chessboardWidth = 8;
	constexpr const int chessboardHeigth = 8;

	const std::string startupPositionString = "Startup Position ";
	constexpr const int startupPositionStringLength = 17;
	
	constexpr const int playerTurnDisplayerHeight = 70;
	constexpr const int playerTurnDisplayerWidth = 70;
	constexpr const int playerTurnDisplayerX = 30;
	constexpr const int playerTurnDisplayerY = 30;

	constexpr const int gameoverMessageWidth = 200;
	constexpr const int gameoverMessageHeight = 50;
	constexpr const int gameoverMessageX = 415;
	constexpr const int gameoverMessageY = 40;
	constexpr const int gameoverMessageSize = 20;


	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public slots:

		void buttonClicked();

		void invalidMove(int x, int y);
		
		void assignCheckTile(int x, int y);

		void addPiece(int x, int y, std::string type, std::string pieceColor);

		void gameover();

		void selectStartupPosition();

		void displayPositionSelectionWindow();

	public:
		MainWindow();
		~MainWindow();

		void setUi();

	private:
		void initializeMainWindow();

		void initializeBoard();

		void initializePlayerTurnDisplayer();

		void initializeMenuBar();

		void displayPrompt(int positionNumber);

		void startGame(int piecesPositionNumber);

		void switchColor(const model::Color& color);

		void clear();

		void clearBoard();

		void movePiece(int destinationX, int destinationY);

		void moveIcon(Tile* destinationTile);

		void setSourceTileDefaultColor();

		void setCheckedTileColor();
		
		Tile* sourceTile_;

		Tile* checkedTile_;

		QList<Tile*> tiles_;

		control::Controller* controller_;

		QLabel* playerTurnDisplayer_;
		
		QLabel* gameoverMessage_;

		class PositionSelectionWindow* positionSelectionWindow_;
	};
}