
#include "PositionSelectionWindow.hpp"

namespace view
{
	void PositionSelectionWindow::createWindow(MainWindow& mainWindow)
	{
		setWindowTitle("Selection screen");
		QString locations[4] = { "img/Pos1.png", "img/Pos2.png", "img/Pos3.png", "img/Pos4.png" };
		QVBoxLayout* layout = new QVBoxLayout();
		QLabel* label = new QLabel(this);
		label->setText("Select the desired preset.");
		label->setAlignment(Qt::AlignCenter);
		layout->addWidget(label);

		QHBoxLayout* selectionTable = new QHBoxLayout();
		for (int i = 0; i < numberOfPresets; i++) {
			QPushButton* button = new QPushButton("", this);
			button->setWhatsThis(QString::fromStdString("Startup Position " + std::to_string(i + 1)));
			button->setGeometry(i % 2 * xPosition, i / 2 * yPosition, widthDimension, heightDimension);
			button->setIcon(QIcon(locations[i]));
			button->setIconSize(QSize(widthDimension, heightDimension));
			selectionTable->addWidget(button);
		
			QObject::connect(button, &QPushButton::pressed,
				&mainWindow, &MainWindow::selectStartupPosition);
		}
		layout->addLayout(selectionTable);

		setLayout(layout);
		setWindowModality(Qt::ApplicationModal);
	}
}