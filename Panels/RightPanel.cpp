#include "RightPanel.h"

RightPanel::RightPanel(
	const string desc,
	const int width,
	const int height):Panel(desc) {
	width_ = width;
	height_ = height;
};
		
RightPanel::RightPanel(
	const COORD pos, 
	const string desc,
	const int width,
	const int height):Panel(pos, desc){
	width_ = width;
	height_ = height;
};
		
RightPanel::RightPanel(
	const int x, 
	const int y, 
	const string desc,
	const int width,
	const int height):Panel(x, y, desc) {
	width_ = width;
	height_ = height;
};
		
RightPanel::~RightPanel(){
	delete distancePanel_;
	delete speedPanel_;
	delete fuelPanel_;
};

int const RightPanel::show()
{  
	int mode = NULL;
	bool choise = false;
	
	console->drawText(position.X, position.Y, description);

	drawBorder();

	COORD pos = { static_cast<SHORT>(position.X + width_ * .5), static_cast<SHORT>(position.Y + height_ * .3) };

	distancePanel_ = new StatePanel(pos.X, pos.Y, "Distance:");
	distancePanel_->setTextAlign(StatePanel::Center);
	distancePanel_->show();

	speedPanel_ = new StatePanel(pos.X, pos.Y + 3, "Speed:");
	speedPanel_->setTextAlign(StatePanel::Center);
	speedPanel_->show();

	fuelPanel_ = new StatePanel(pos.X, pos.Y + 6, "Fuel:");
	fuelPanel_->setTextAlign(StatePanel::Center);
	fuelPanel_->show();

	redrawPanel(mode, mode, mode);
	
	return mode;
}

string RightPanel::intToStringWithKM(const int value) {
	string str = to_string(value);
	str += " km/h";
	return str;
}

void RightPanel::drawBorder() {
	console->setColor(console->White, console->Black);

	console->fillLine("\xc9", "\xcd", "\xBB", width_, position.X, position.Y);
	console->fillSquare("\xba", " ", "\xba", width_, height_ - 2, position.X, position.Y + 1);
	console->fillLine("\xc8", "\xcd", "\xBC", width_, position.X, position.Y + height_ - 1);
}

void RightPanel::redrawPanel(
	 const int distance,
	 const int speed,
	 const int fuel,
	 const int textColor, 
	 const int backgroundColor)
{
	distancePanel_->redrawPanel(distance, textColor, backgroundColor);
	speedPanel_->redrawPanel(intToStringWithKM(speed), textColor, backgroundColor);
	fuelPanel_->redrawPanel(fuel, textColor, backgroundColor);
}