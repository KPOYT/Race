#include "Panel.h"

Panel::Panel(string const desc) {
	position = { 0, 0 };
	description = desc;
	console = OS::GetOSFactory()->GetConsole();
};

Panel::Panel(const COORD pos, const string desc){
	position = pos;
	description = desc;
	console = OS::GetOSFactory()->GetConsole();
};

Panel::Panel(const int x, const int y, const string desc){
	position.X = x;
	position.Y = y;
	description = desc;
	console = OS::GetOSFactory()->GetConsole();
};

Panel::~Panel() {};

void Panel::redrawPanel(
			int mode, 
			int textColor, 
			int backgroundColor){};