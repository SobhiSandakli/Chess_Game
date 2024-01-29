#include "Tile.h"

namespace view
{
    Tile::Tile(Qstring title, Qwidget* parent, int x , int y):
    QPushButton(title, parent),
    timer_(this),
    x_(x),
    y_(y)
    {
		setGeometry(caseWidth * x_, caseHeight * y_, caseWidth, caseHeight);
		setDefaultColor();

		timer_.setSingleShot(true);
		QObject::connect(&timer_, &QTimer::timeout,
			this, &view::Tile::setDefaultColor);
	}
    
    void Tile::setImage(Qicon icon)
    {
        setIcon(icon);
        setIconSize(Qsize(iconHeight, iconWidth));
    }
    
    void Tile::setDefaultColor()
    {
        const bool isPairColumn = (x_ % 2 == 0);
        const bool isPairRow = (y_ % 2 == 0);

        const bool isBlackTileCase1 = (isPairColumn && !isPairRow);
        const bool isBlackTileCase2 = (isPairRow && !isPairColumn);
        const bool isBlackTile = (isBlackTileCase1) || (isBlackTileCase2);

        if (isBlackTile)
            setStyleSheet(grey);
        else
            setStyleSheet(white);
        
    }
    void TIle::SetInvalid()
    {
        setStyleSheet(red);
        timer_.start(isvalidmoveColorTime);
    }

}