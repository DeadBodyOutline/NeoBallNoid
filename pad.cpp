#include <QPixmap>
#include "pad.h"

#define RIGHTPOS	ZONEW + ZONEVBAR - PADW // para o calculo do limite esquerdo

Pad::Pad(QString padimage){
	QPixmap image;

	image.load(padimage);
	pad = new QGraphicsPixmapItem(image);

	pad->setZValue(2);

	limit_left = mapToScene(QRectF(GAMEW - ZONEW - (ZONEVBAR * 2), GAMEH - ZONEH - (ZONEHBAR * 2), ZONEVBAR, ZONEH)).boundingRect();
	limit_right = mapToScene(QRectF(ZONEH + ZONEVBAR, GAMEH - ZONEH - (ZONEHBAR * 2), ZONEVBAR, ZONEH)).boundingRect();

	ball = new Ball("images/ball.png");
	//scene().addItem(ball);
	ball->ball->setZValue(3);
	ball->definePos((width / 2) - PADXPOS, height - PADYPOS);
}

Pad::~Pad(){
}

void Pad::definePos(int x, int y){
	this->x = x;
	this->y = y;

	pad->setPos(this->x, this->y);
}

void Pad::moveLeft(){
	if (!limit_left.contains(x - PADSTEP + 1, y)){ // o '1' aqui é um controlador
		x -= PADSTEP;
		if (x - 10 <= PADSTEP) x = 10;
		pad->setPos(x, y);
	}
}

void Pad::moveRight(){
	if (!limit_right.contains((x + PADSTEP) + PADW - 1, y)){
		x += PADSTEP;
		if (RIGHTPOS - x <= PADSTEP) x = RIGHTPOS;
		pad->setPos(x, y);
	}
}

