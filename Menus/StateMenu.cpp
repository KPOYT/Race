#include "StateMenu.h"

StateMenu::StateMenu() :Menu() {
	config = OS::GetOSFactory()->GetConfig();
};

const int StateMenu::show(
	 const int value)
{
	console->setColor(console->Black, console->Black);
	console->clearConsole();

	string title = "GAME OVER";
	string description = "Your score:";
	string score = to_string(value);
	
	console->drawText(
		(config->WINDOW_WIDTH - title.length()) / 2,
		config->WINDOW_HEIGHT / 2 - 3,
		title);

	console->drawText(
		(config->WINDOW_WIDTH - description.length()) / 2,
		config->WINDOW_HEIGHT / 2 - 1,
		description);

	console->drawText(
		(config->WINDOW_WIDTH - score.length()) / 2,
		config->WINDOW_HEIGHT / 2,
		score);

	return NULL;
};