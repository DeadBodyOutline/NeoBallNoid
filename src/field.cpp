#include <QList>
#include <QRectF>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "field.h"

Field::Field(const QPixmap &back, const QPixmap &zone, int w, int h): QGraphicsScene(back.rect()){
	QGraphicsPixmapItem *game_zone = new QGraphicsPixmapItem(zone);

	// adiciona o background
	addPixmap(back);

	/* ZONA */
	// tamanho da zona de jogo
	width = w;
	height = h;

	game_zone->setZValue(1);
	addItem(game_zone);

	/* LOCAL PAD */
	localpad = new Pad("images/padred.png");
	addItem(localpad->pad);
	localpad->definePos((width / 2) - PADXPOS, height - PADYPOS);

	/* REMOTE PAD */
	remotepad = new Pad("images/padblue.png");
	addItem(remotepad->pad);
	remotepad->definePos((width / 2) - PADXPOS, PADYPOS / 2);

	addItem(localpad->ball->ball);
}

Field::~Field(){
}

void Field::keyPressEvent(QKeyEvent *event){
	switch (event->key()){
		case Qt::Key_Left:
			localpad->moveLeft();
			break;
		case Qt::Key_Right:
			localpad->moveRight();
			break;
		default:
			break;
	}	
}

