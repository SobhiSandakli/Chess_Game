
#include "Chessboard.h"

namespace model
{
	/************************************************************************/
	/*                                                                      */
	/*                   D�FINITION DES M�THODES PUBLIQUES                  */
	/*                                                                      */
	/************************************************************************/
	
	Chessboard::Chessboard() :
		whiteKingPosition_(defaultPosition),
		blackKingPosition_(defaultPosition),
		currentPlayer_(Color::white)
	{
		for (int i : iter::range(width)) {
			for (int j : iter::range(height)) {
				board_[i][j] = nullptr;
			}
		}
	}


	bool Chessboard::isValidMove(AbsPiece* piece, int x, int y)
	{
		return  isLegalMove(piece, x, y) &&
			!alliedKingBecomesChecked(piece, x, y);
	}


	bool Chessboard::movePiece(AbsPiece* piece, int x, int y)
	{
		const bool isValid = isValidMove(piece, x, y) &&
			isCorrectColor(piece->getColor());
		if (isValid) {
			removePiece(x, y);

			auto [previousX, previousY] = piece->getPosition();
			board_[x][y] = move(board_[previousX][previousY]);
			piece->move(x, y);

			if (piece->getType() == "King") {
				setKingPosition(piece);
			}
			nextTurn();

			bool isCheck = isRivalKingCheck(piece);

			const bool isGameOver = (isCheck && isCheckMate()) || isStaleMate();
			if (isGameOver) {
				emit gameover();
			}

			return true;
		}
		return false;
	}


	void Chessboard::addPiece(AbsPiece* piece)
	{
		auto [x, y] = piece->getPosition();
		board_[x][y] = unique_ptr<AbsPiece>(piece);

		if (piece->getType() == "King")
			setKingPosition(piece);
		if (piece->getColor() == Color::white)
			emit pieceAdded(x, y, piece->getType(), "White");
		else
			emit pieceAdded(x, y, piece->getType(), "Black");
	}
	

	void Chessboard::startGame(StartupPositions* strategy)
	{
		clear();
		currentPlayer_ = Color::white;
		initialize(strategy);
		update();
	}


	/************************************************************************/
	/*                                                                      */
	/*                    D�FINITION DES M�THODES PRIV�ES                   */
	/*                                                                      */
	/************************************************************************/

	void Chessboard::initialize(StartupPositions* strategy)
	{
		strategy->set(this);
	}


	void Chessboard::clear()
	{
		for (int i : iter::range(width)) {
			for (int j : iter::range(height)) {
				removePiece(i, j);
			}
		}
	}


	bool Chessboard::isCorrectColor(const Color& pieceColor) const
	{
		return pieceColor == currentPlayer_ ? true : false;
	}


	bool Chessboard::isLegalMove(AbsPiece* piece, int x, int y) const
	{
		return  piece->isValidMove(x, y) &&
			isInsideBoard(x, y) &&
			!isBlockedMove(piece, x, y);
	}


	bool Chessboard::isInsideBoard(int x, int y) const
	{
		const bool isInsideX = (0 <= x) && (x <= width);
		const bool isInsideY = (0 <= y) && (y <= height);
		return isInsideX && isInsideY;
	}


	bool Chessboard::isBlockedMove(AbsPiece* piece, int newX, int newY) const
	{
		const auto [x, y] = piece->getPosition();
		const int displacementX = newX - x;
		const int displacementY = newY - y;

		int xMultiplier = 0;
		int yMultiplier = 0;
		if (displacementX != 0) {
			xMultiplier = abs(displacementX) / displacementX;
		}
		if (displacementY != 0) {
			yMultiplier = abs(displacementY) / displacementY;
		}

		int i = xMultiplier;
		int j = yMultiplier;
		bool isLastTile = false;
		bool hasSameColor = false;
		while (!isLastTile) {
			if ((i == displacementX) && (j == displacementY))
				isLastTile = true;

			const AbsPiece* currentTile = board_[x + i][y + j].get();
			if (currentTile != nullptr) {
				hasSameColor = currentTile->getColor() == piece->getColor();
				if (hasSameColor) {
					return true;
				}
				else {
					return isLastTile ? false : true;
				}
			}

			i += 1 * xMultiplier;
			j += 1 * yMultiplier;
		}

		return false;
	}


	void Chessboard::removePiece(int x, int y)
	{
		const bool isEmptyTile = (board_[x][y] == nullptr);
		if (!isEmptyTile)
			board_[x][y].reset();
	}


	void Chessboard::update()
	{
		possibleMoves_.clear();

		AbsPiece* currentTile = nullptr;
		for (int x : iter::range(width)) {
			for (int y : iter::range(height)) {
				currentTile = board_[x][y].get();
				if (currentTile != nullptr) {
					updatePossibleMoves(currentTile);
				}
			}
		}
	}


	void Chessboard::updatePossibleMoves(AbsPiece* piece)
	{
		for (int x : iter::range(width)) {
			for (int y : iter::range(height)) {
				if (isValidMove(piece, x, y)) {
					possibleMoves_[piece].push_back(pair<int, int>(x, y));
				}
			}
		}
	}


	void Chessboard::togglePlayerTurn()
	{
		if (currentPlayer_ == Color::white)
			currentPlayer_ = Color::black;
		else
			currentPlayer_ = Color::white;
	}


	void Chessboard::nextTurn()
	{
		update();
		togglePlayerTurn();
	}


	bool Chessboard::isRivalKingCheck(AbsPiece* piece) const
	{
		Color pieceColor = piece->getColor();
		auto [rivalKingX, rivalKingY] = getRivalKingPosition(pieceColor);
		const bool canReachKing = isLegalMove(piece, rivalKingX, rivalKingY);
		if (canReachKing) {
			emit checkSignal(rivalKingX, rivalKingY);
			return true;
		}
		return false;
	}


	const pair<int, int> Chessboard::getRivalKingPosition(const Color& pieceColor) const
	{
		if (pieceColor == Color::white)
			return blackKingPosition_;
		else
			return whiteKingPosition_;
	}


	bool Chessboard::alliedKingBecomesChecked(AbsPiece* piece, int x, int y)
	{
		unique_ptr<AbsPiece> pieceBackup = move(board_[x][y]);
		const auto [previousX, previousY] = piece->getPosition();
		
		pair<int, int> kingPosition;
		if (piece->getType() == "King") {
			kingPosition = pair<int, int>(x, y);
		}
		else {
			kingPosition = getAlliedKingPosition(piece->getColor());
		}
		const auto [kingX, kingY] = kingPosition;
		
		board_[x][y] = move(board_[previousX][previousY]);

		const auto revert = [&]() {
			board_[previousX][previousY] = move(board_[x][y]);
			board_[x][y] = move(pieceBackup); 
		};

		for (int i : iter::range(width)) {
			for (int j : iter::range(height)) {
				AbsPiece* tile = board_[i][j].get();
				const bool isPiece = tile != nullptr;
				const bool isEnemyPiece = 
					isPiece && 
					(tile->getColor() != piece->getColor());
				const bool canReachKing = 
					isEnemyPiece && 
					isLegalMove(tile, kingX, kingY);
				if (canReachKing) {
					revert();
					return true;
				}
			}
		}
		revert();
		return false;
	}


	const pair<int, int> Chessboard::getAlliedKingPosition(const Color& pieceColor) const
	{
		if (pieceColor == Color::white)
			return whiteKingPosition_;
		else
			return blackKingPosition_;
	}


	void Chessboard::setKingPosition(const AbsPiece* king)
	{
		auto [x, y] = king->getPosition();
		const pair<int, int> newKingPosition = pair<int, int>(x, y);

		const Color pieceColor = king->getColor();
		if (pieceColor == Color::black)
			blackKingPosition_ = newKingPosition;
		else if (pieceColor == Color::white)
			whiteKingPosition_ = newKingPosition;
	}


	bool Chessboard::isCheckMate()
	{
		AbsPiece* piece = nullptr;
		auto [x, y] = defaultPosition;
		for (auto it : possibleMoves_) {
			piece = it.first;
			if (piece->getColor() == currentPlayer_) {
				for (auto move : it.second) {
					x = move.first;
					y = move.second;
					if (!alliedKingBecomesChecked(piece, x, y)) {
						return false;
					}
				}
			}
		}
		return true;
	}


	bool Chessboard::isStaleMate()
	{
		for (auto piecePtr : possibleMoves_) {
			if (piecePtr.first->getColor() == currentPlayer_) {
				if (!piecePtr.second.empty()) {
					return false;
				}
			}
		}
		return true;
	}
}