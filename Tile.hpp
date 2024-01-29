#pragma once
#include <QPushButton>
#include <QString>
#include <QTimer>

    
namespace view
{
	constexpr const int defaultPosition = 999;

	constexpr const int caseWidth = 100;
	constexpr const int caseHeight = 100;

	constexpr const int iconHeight = 150;
	constexpr const int iconWidth = 150;

	constexpr const int invalidMoveColorTime = 100; // milliseconds

	const QString red = "QPushButton {background-color: red; color: white}";
	const QString white = "QPushButton {background-color: white; color: black}";
	const QString grey = "QPushButton {background-color: grey; color: white}";
	const QString blue = "QPushButton {background-color: blue; color: white}";

	class Tile : public QPushButton
	{
	public slots:
		void setDefaultColor();

	public:
		Tile(QString title = "", 
			 QWidget* parent = nullptr, 
			 int x = defaultPosition, 
			 int y = defaultPosition
		);

		void setImage(QIcon icon);

		void setInvalid();

		inline bool isCheck() { return styleSheet() == red; }

		inline void setCheck() { setStyleSheet(red); }

		inline void setSelected() { setStyleSheet(blue); }

		inline std::pair<int, int> getPosition() { return std::pair<int, int>(x_, y_); }

	private:
		QTimer timer_;

		int x_;

		int y_;
	};
}