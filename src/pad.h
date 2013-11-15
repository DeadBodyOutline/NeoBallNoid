#ifndef __PAD_H__
#define __PAD_H__

#include <QRectF>
#include <QString>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "defines.h"
#include "ball.h"

class Pad: public QGraphicsPixmapItem{
	public:
		Pad(QString padimage);
		~Pad();
		void definePos(int x, int y); // seta a posicao inicial
		void moveLeft();
		void moveRight();

		QGraphicsPixmapItem *pad;
		Ball *ball;

	private:
		QRectF limit_left, limit_right;
		int width, height; // tamanho do pad
		int x, y; // posicao no jogo

};

#endif

