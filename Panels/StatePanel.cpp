#include "StatePanel.h"

StatePanel::StatePanel(
	const string desc):Panel(desc) {
	textAlign_ = Left;
};
		
StatePanel::StatePanel(
	const COORD pos, 
	const string desc):Panel(pos, desc){
	textAlign_ = Left;
};
		
StatePanel::StatePanel(
	const int x, 
	const int y, 
	const string desc):Panel(x, y, desc) {
	textAlign_ = Left;
};
		
StatePanel::~StatePanel(){
	console->fillSquare(" ", 8, 2, position.X - 1, position.Y);
};

const void StatePanel::setTextAlign(const int state) {
	switch (state) {
		case Center:
			textAlign_ = state;
		break;
		case Left:
			textAlign_ = state;
		break;
	}
};

const int StatePanel::show()
{  
	int mode = NULL;
	bool choise = false;
	
	switch (textAlign_) {
		case Left:
			console->drawText(position.X, position.Y, description, console->White, console->Black);
		break;
		case Center:
			console->drawText(position.X - (static_cast<int> (description.length()) / 2), position.Y, description, console->White, console->Black);
		break;
	}

	redrawPanel(mode);
	
	return mode;
}

void StatePanel::redrawPanel(
	 const int count, 
	 const int textColor, 
	 const int backgroundColor)
{
	console->setColor(console->Black, console->Black);
	counter_.clear();

	counter_.push_back(0);
	counter_ += to_string(count);
	counter_.push_back(0);

	COORD centerPos;
	switch (textAlign_) {
		case Left:
			centerPos.X = position.X + static_cast<SHORT>(description.length() - counter_.length()) / 2;
		break;
		case Center:
			centerPos.X = position.X - static_cast<SHORT>(description.length() / 2) + 
				+ static_cast<SHORT>(description.length() - counter_.length()) / 2;
		break;
	}
	centerPos.Y = position.Y + 1;

	console->drawText(centerPos.X, centerPos.Y, counter_, textColor, backgroundColor);
	console->setColor(console->Black, console->Black);
}

void StatePanel::redrawPanel(
	 const string count,
	 const int textColor,
	 const int backgroundColor)
{
	console->setColor(console->Black, console->Black);
	counter_.clear();

	counter_.push_back(0);
	counter_ += count;
	counter_.push_back(0);

	COORD centerPos;
	switch (textAlign_) {
	case Left:
		centerPos.X = position.X + static_cast<SHORT>(description.length() - counter_.length()) / 2;
		break;
	case Center:
		centerPos.X = position.X - static_cast<SHORT>(description.length() / 2) +
			+static_cast<SHORT>(description.length() - counter_.length()) / 2;
		break;
	}
	centerPos.Y = position.Y + 1;

	console->drawText(centerPos.X, centerPos.Y, counter_, textColor, backgroundColor);
	console->setColor(console->Black, console->Black);
}