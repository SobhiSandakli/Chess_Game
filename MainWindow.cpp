#include "MainWindow.hpp"

namespace view
{
	MainWindow::MainWindow() : 
		sourceTile_(nullptr), 
		checkedTile_(nullptr), 
		controller_(new control::Controller()), 
		playerTurnDisplayer_(nullptr),
		gameoverMessage_(nullptr),
		positionSelectionWindow_(nullptr)
	{
		QObject::connect(controller_, &control::Controller::invalidMove,
            this, &view::MainWindow::invalidMove);
		QObject::connect(controller_, &control::Controller::notifyCheck,
			this, &view::MainWindow::assignCheckTile);
		QObject::connect(controller_, &control::Controller::notifyGameover,
			this, &view::MainWindow::gameover);
		QObject::connect(controller_, &control::Controller::notifyPieceAdded,
			this, &view::MainWindow::addPiece);
	}


	MainWindow::~MainWindow()
	{
		for (auto tile : tiles_) {
			delete tile;
		}
		delete controller_;
	}


	void MainWindow::buttonClicked()
	{
		const QPushButton* sender = qobject_cast<QPushButton*>(QObject::sender());

		if (sourceTile_ != nullptr) {
			const int destinationX = sender->x() / caseWidth;
			const int destinationY = sender->y() / caseHeight;
			setSourceTileDefaultColor();
			movePiece(destinationX, destinationY);
		}
		else {
			const int sourceX = sender->x() / caseWidth;
			const int sourceY = sender->y() / caseHeight;
			if (controller_->isValidTile(sourceX, sourceY)) {
				sourceTile_ = tiles_[sourceX * chessboardHeigth + sourceY];
				sourceTile_->setSelected();
			}
		}
	}


	void MainWindow::invalidMove(int x, int y)
	{
		Tile* wantedDestination = tiles_[x * chessboardHeigth + y];
		wantedDestination->setInvalid();
	}


	void MainWindow::assignCheckTile(int x, int y)
	{
		checkedTile_ = tiles_[x * chessboardHeigth + y];
	}


	void MainWindow::gameover()
	{
		gameoverMessage_ = new QLabel("GAME OVER", this);
		gameoverMessage_->setGeometry(
			gameoverMessageX, 
			gameoverMessageY, 
			gameoverMessageWidth, 
			gameoverMessageHeight
		);
		gameoverMessage_->setFont(QFont("Helvetica", gameoverMessageSize));
		gameoverMessage_->setStyleSheet("QLabel {color: red}");
		gameoverMessage_->show();
	}


	void MainWindow::selectStartupPosition()
	{
		QPushButton* button = qobject_cast<QPushButton*>(QObject::sender());
		std::string startupPosition = button->whatsThis().toStdString();
		int positionNumber = stoi(startupPosition.substr(startupPositionStringLength, 1));
		displayPrompt(positionNumber);
	}


	void MainWindow::displayPositionSelectionWindow()
	{
		positionSelectionWindow_ = new PositionSelectionWindow;
		positionSelectionWindow_->createWindow(*this);
		positionSelectionWindow_->setAttribute(Qt::WA_DeleteOnClose);
		positionSelectionWindow_->show();
	}


	void MainWindow::addPiece(int x, int y, std::string type, std::string pieceColor)
	{
		std::string filename = "img/" + pieceColor + "_" + type + ".svg";
		QIcon icon(QString::fromStdString(filename));
		tiles_[(x * chessboardHeigth) + y]->setImage(icon);
	}


	void MainWindow::setUi()
	{
		initializeMainWindow();
		initializeBoard();
		displayPositionSelectionWindow();
	}


	void MainWindow::initializeMainWindow()
	{
		setWindowTitle("Chess");
		const int width = margin * 2 + chessboardWidth * caseWidth;
		const int height = margin * 2 + chessboardHeigth * caseHeight;
		setFixedSize(width, height);
		
		initializePlayerTurnDisplayer();
		initializeMenuBar();
		
		show();
	}


	void MainWindow::initializeBoard()
	{
		QWidget* board = new QWidget(this);
		const int width = chessboardWidth * caseWidth;
		const int height = chessboardHeigth * caseHeight;
		board->setGeometry(margin, margin, width, height);


		for (int i : iter::range(chessboardWidth)) {
			for (int j : iter::range(chessboardHeigth)) {
				Tile* tile = new Tile("", board, i, j);
				QObject::connect(tile, &QPushButton::pressed, 
					this, &MainWindow::buttonClicked);
				tiles_.push_back(tile);
			}
		}
		board->show();
	}

	
	void MainWindow::initializePlayerTurnDisplayer()
	{
		playerTurnDisplayer_ = new QLabel(this);

		int width = playerTurnDisplayerWidth;
		int height = playerTurnDisplayerHeight;
		int x = playerTurnDisplayerX;
		int y = playerTurnDisplayerY;

		playerTurnDisplayer_->setFixedHeight(height);
		playerTurnDisplayer_->setFixedWidth(width);
		playerTurnDisplayer_->setScaledContents(true);
		playerTurnDisplayer_->move(x, y);

		QPixmap colorTurn("img/white.png");
		colorTurn.scaled(width, height);
		playerTurnDisplayer_->setPixmap(colorTurn);
	}


	void MainWindow::initializeMenuBar()
	{
		QMenu* playMenu = menuBar()->addMenu("Play");
		QAction* positionSelection = playMenu->addAction("New Game");
		QObject::connect(positionSelection, &QAction::triggered,
			this, &MainWindow::displayPositionSelectionWindow);
		playMenu->addSeparator();

		QAction* closeAction = playMenu->addAction("Close");
		QObject::connect(closeAction, &QAction::triggered, 
			this, &MainWindow::close);
	}


	void MainWindow::displayPrompt(int positionNumber)
	{
		QMessageBox prompt;
		prompt.setWindowTitle("Confirm your selection");
		prompt.setText("A preset has been selected.");
		prompt.setInformativeText("Do you wish to start the game?");

		QPushButton* yes = prompt.addButton(tr("Yes"), QMessageBox::ActionRole);
		prompt.addButton(tr("Cancel"), QMessageBox::ActionRole);

		prompt.exec();

		if (prompt.clickedButton() == yes) {
			positionSelectionWindow_->close();
			startGame(positionNumber);
		}
	}


	void MainWindow::startGame(int piecesPositionNumber)
	{
		clear();
		controller_->startGame(piecesPositionNumber);
	}


	void MainWindow::clear()
	{
		clearBoard();
		switchColor(model::Color::white);
		delete gameoverMessage_;
	}


	void MainWindow::clearBoard()
	{
		sourceTile_ = nullptr;
		checkedTile_ = nullptr;
		for (Tile* tile : tiles_) {
			tile->setImage(QIcon());
			tile->setDefaultColor();
		}
	}

	void MainWindow::switchColor(const model::Color& color)
	{
		QPixmap colorTurn;

		if (color == model::Color::white)
			colorTurn = QPixmap("img/white.png");
		else
			colorTurn = QPixmap("img/black.png");

		const int width = playerTurnDisplayerWidth;
		const int height = playerTurnDisplayerHeight;
		colorTurn.scaled(width, height);
		playerTurnDisplayer_->setPixmap(colorTurn);
	}

	void MainWindow::moveIcon(Tile* destinationTile)
	{
		QIcon icon = sourceTile_->icon();
		sourceTile_->setImage(QIcon());
		destinationTile->setImage(icon);
	}
	

	void MainWindow::setSourceTileDefaultColor()
	{
		const bool checkedTileIsSelected = (sourceTile_ == checkedTile_);
		if (checkedTileIsSelected)
			checkedTile_->setCheck();
		else
			sourceTile_->setDefaultColor();
	}


	void MainWindow::setCheckedTileColor()
	{
		if (!checkedTile_->isCheck()) {
			checkedTile_->setCheck();
		}
		else {
			checkedTile_->setDefaultColor();
			checkedTile_ = nullptr;
		}
	}


	void MainWindow::movePiece(int destinationX, int destinationY)
	{		
		auto [sourceX, sourceY] = sourceTile_->getPosition();
		int destinationTileNumber = destinationX * chessboardHeigth + destinationY;
		Tile* destinationTile = tiles_[destinationTileNumber];
		bool isValidMove = controller_->move(sourceX, sourceY, destinationX, destinationY);
		
		if (isValidMove) {
			switchColor(controller_->getColor());
			moveIcon(destinationTile);

			const bool kingIsChecked = checkedTile_ != nullptr;
			if (kingIsChecked) {
				setCheckedTileColor();
			}
		}

		sourceTile_ = nullptr;
	}
}