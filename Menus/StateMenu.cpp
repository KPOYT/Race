#include "StateMenu.h"

StateMenu::StateMenu() :Menu() {
	config = OS::GetOSFactory()->GetConfig();
};

const int StateMenu::show(
	 const int scoreValue,
	 const int timerValue)
{
	console->setColor(console->Black, console->Black);
	console->clearConsole();

	string title = "GAME OVER";
	string score_desc = "Your score:";
	string score = to_string(scoreValue);
	string timer_desc = "Your time:";
	string timer = to_string(timerValue);
	
	console->drawText(
		(config->WINDOW_WIDTH - title.length()) / 2,
		config->WINDOW_HEIGHT / 2 - 5,
		title);

	console->drawText(
		(config->WINDOW_WIDTH - score_desc.length()) / 2,
		config->WINDOW_HEIGHT / 2 - 2,
		score_desc);

	console->drawText(
		(config->WINDOW_WIDTH - score.length()) / 2,
		config->WINDOW_HEIGHT / 2 - 1,
		score);

	console->drawText(
		(config->WINDOW_WIDTH - timer_desc.length()) / 2,
		config->WINDOW_HEIGHT / 2 + 1,
		timer_desc);

	console->drawText(
		(config->WINDOW_WIDTH - timer.length()) / 2,
		config->WINDOW_HEIGHT / 2 + 2,
		timer);

	return NULL;
};