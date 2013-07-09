#include <QGraphicsView>
#include <QVBoxLayout>
#include "game.h"
#include "field.h"

Game::Game(QWidget *parent): QWidget(parent){
	QPixmap background;
	QPixmap game_zone;

	resize(GAMEW + 4, GAMEH + 4); // 480 + 4, 640 + 4
	//resize(484, 644); // 480 + 4, 640 + 4

	background.load("images/background.png");
	game_zone.load("images/game_zone2.png");

	game_scene = new Field(background, game_zone, ZONEW, ZONEH);
	
	game_view = new QGraphicsView(this);

	//resize(background.size());

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(game_view);

	game_view->setScene(game_scene);
}

Game::~Game(){
}

