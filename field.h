#ifndef __FIELD_H__
#define __FIELD_H__

#include <QRect>
#include <QPixmap>
#include <QGraphicsScene>
#include "pad.h"
#include "defines.h"

class Field: public QGraphicsScene{
	public:
		Field(const QPixmap &back, const QPixmap &zone, int w, int h);
		~Field();

	private:
		Pad *localpad, *remotepad;
		int width, height; // tamanho do campo, nao da imagem de fundo

	protected:
		void keyPressEvent(QKeyEvent *event);
};

#endif

