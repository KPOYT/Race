#include "Race.h"

Race::Race(){};
Race::~Race(){};

Race* Race::_instance = 0;

Race* Race::Instance(){
	if (_instance == 0) {
		_instance = new Race();
	}
	return _instance;
}

const int Race::startGame(){
	MainMenu* mainMenu = new MainMenu();
	ExitMenu* exitMenu = new ExitMenu(33, 10);
	Game* game;

	int mainMenuChoise;
	int exitMenuChoise = 0;

	do {
		mainMenuChoise = mainMenu->show();

		switch (mainMenuChoise) {
			case 0:
				game = new Game;
				game->draw();
				delete game;
			break;
			case 1:
				exitMenuChoise = exitMenu->show();
			break;
		}
	}
	while (exitMenuChoise != 1);

	return exitMenuChoise;
}