#include "Game.h"

Game::Game(){
	console = OS::GetOSFactory()->GetConsole();
	config = OS::GetOSFactory()->GetConfig();
};

Game::~Game(){
	delete map_;
	delete rightPanel_;
};

void Game::draw() {
	console->clearConsole();
	
	rightPanel_ = new RightPanel(config->WINDOW_WIDTH - 21, 1);
	rightPanel_->show();
	rightPanel_->redrawPanel(0, 0, 100);
	
	map_ = new Map(15, 1);
	map_->setUserCarPanel(rightPanel_);
	map_->draw();
	map_->start();
}