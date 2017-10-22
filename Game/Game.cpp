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
	
	rightPanel_ = new RightPanel(config->WINDOW_WIDTH - OSConfig::RIGHT_PANEL_WIDTH - 1, 1);
	rightPanel_->show();
	
	map_ = new Map(OSConfig::MAP_X, OSConfig::MAP_Y);
	map_->setUserCarPanel(rightPanel_);
	map_->draw();
	map_->start();
}