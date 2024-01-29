#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "Tile.hpp"
#include "MainWindow.hpp"

namespace view
{
	const int xPosition = 450;
	const int yPosition = 450;
	const int widthDimension = 400;
	const int heightDimension = 400;
	const int numberOfPresets = 4;

	class PositionSelectionWindow : public QWidget
	{
		Q_OBJECT

	public:
		PositionSelectionWindow() = default;
		~PositionSelectionWindow() = default;

		void createWindow(class MainWindow& mainWindow);
	};
}