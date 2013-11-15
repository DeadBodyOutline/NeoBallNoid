#ifndef __BALL_H__
#define __BALL_H__

//#include <QRectF>
#include <QString>
//#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "defines.h"

class Ball: public QGraphicsPixmapItem{
	public:
		Ball(QString ballimage);
		~Ball();
		void definePos(int x, int y); // seta a posicao inicial
		//void moveLeft();
		//void moveRight();

		QGraphicsPixmapItem *ball;

	private:
		//QRectF limit_left, limit_right;
		int width, height; // tamanho da bola
		int x, y; // posicao no jogo

};

#endif

