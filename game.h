#ifndef __GAME_H__
#define __GAME_H__

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "defines.h"

class Game: public QWidget{
	Q_OBJECT

	public:
		Game(QWidget *parent = 0);
		~Game();

	private:
		QGraphicsView *game_view;
		QGraphicsScene *game_scene;
};

#endif

