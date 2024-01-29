
#include "Controller.hpp"

namespace control
{
	Controller::Controller() : board_(new model::Chessboard())
	{
		QObject::connect(board_, & model::Chessboard::checkSignal,
                         this, &control::Controller::forwardCheck);
		QObject::connect(board_, &model::Chessboard::gameover, 
                         this, &control::Controller::forwardGameover);
		QObject::connect(board_, &model::Chessboard::pieceAdded,
                         this, &control::Controller::forwardPieceAdded);
	}


	Controller::~Controller()
	{
		delete board_;
	}


	void Controller::forwardCheck(int x, int y)
	{
		emit notifyCheck(x, y);
	}


	void Controller::forwardGameover()
	{
		emit notifyGameover();
	}


	void Controller::forwardPieceAdded(int x, int y, std::string type, std::string pieceColor)
	{
		emit notifyPieceAdded(x, y, type, pieceColor);
	}


	void Controller::startGame(int strategyNumber)
	{
		model::StartupPositions* strategy = getStrategy(strategyNumber);

		try {
			board_->startGame(strategy);
		}
		catch (model::TooManyKingsException& e) {
			std::cerr << "ERROR: " << e.what() << std::endl;
		}
		delete strategy;
	}


	bool Controller::move(int sourceX, int sourceY, int destinationX, int destinationY)
	{
		model::AbsPiece* piece = board_->getPiece(sourceX, sourceY);
		if (board_->movePiece(piece, destinationX, destinationY)) {
			return true;
		}
		else {
			emit invalidMove(destinationX, destinationY);
			return false;
		}
	}


	bool Controller::isValidTile(int x, int y) const
	{
		const model::AbsPiece* selectedPiece = getPiece(x, y);
		const bool isEmptyTile = selectedPiece == nullptr;
		if (!isEmptyTile) {
			const model::Color currentPlayer = getColor();
			const model::Color selectedPieceColor = selectedPiece->getColor();
			const bool isCorrectColor = selectedPieceColor == currentPlayer;
			if (isCorrectColor) {
				return true;
			}
		}
		return false;
	}


	model::StartupPositions* Controller::getStrategy(int strategyNumber)
	{
		switch (strategyNumber) {
		case 1:
			return new model::StartupPositions1();
			break;
		case 2:
			return new model::StartupPositions2();
			break;
		case 3:
			return new model::StartupPositions3();
			break;
		case 4:
			return new model::StartupPositions4();
			break;
		default:
			return new model::StartupPositions1();
		}
	}
}