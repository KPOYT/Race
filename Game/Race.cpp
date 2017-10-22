#include "Race.h"

Race::Race(){};
Race::~Race(){
	delete mainMenu_;
	delete exitMenu_;
};

Race* Race::_instance = 0;

Race* Race::Instance(){
	if (_instance == 0) {
		_instance = new Race();
	}
	return _instance;
}

const int Race::startGame(){
	mainMenu_ = new MainMenu();
	exitMenu_ = new ExitMenu();

	int mainMenuChoise;
	int exitMenuChoise = 0;

	do {
		mainMenuChoise = mainMenu_->show();

		switch (mainMenuChoise) {
			case 0:
				game_ = new Game;
				game_->draw();
				delete game_;
			break;
			case 1:
				exitMenuChoise = exitMenu_->show();
			break;
		}
	}
	while (exitMenuChoise != 1);

	return exitMenuChoise;
}