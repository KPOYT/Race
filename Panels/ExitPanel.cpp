#include "ExitPanel.h"

ExitPanel::ExitPanel(
	const string desc):Panel(desc) {};

ExitPanel::ExitPanel(
	const COORD pos, 
	const string desc):Panel(pos, desc) {};
		
ExitPanel::ExitPanel(
	const int x, 
	const int y, 
	const string desc):Panel(x, y, desc) {};
		
ExitPanel::~ExitPanel(){
	console->fillLine(" ", static_cast<int>(description.length()) + 9, position.X, position.Y, false);
};

const int ExitPanel::show()
{  
	int mode = 0;
	
	console->drawText(position.X, position.Y, description);

	redrawMenu(mode);

	mode = checkKeys(mode);
	
	return mode;
}

void ExitPanel::redrawMenu(const int mode) {
	switch(mode)
	{
		case 0:
			console->drawText(position.X + 15, position.Y, "Yes");
			console->drawText(position.X + 20, position.Y, "No", console->Green, console->Black);
		break;
		case 1:
			console->drawText(position.X + 15, position.Y, "Yes", console->Green, console->Black);
			console->drawText(position.X + 20, position.Y, "No");
		break;
	}
}

const int ExitPanel::checkKeys(int mode){
	bool isDone = false;
	do 
	{
		int code = console->getCodeFromKeyboard();
		if (code == 224)
		{
			code = console->getCodeFromKeyboard();
			switch(code) 
			{
			case 77: {
				mode++;
				if(mode > 1)
					mode = 0;

				redrawMenu(mode);
				break;
			}	 
			case 75: {
				mode--;
				if(mode < 0)
					mode = 1;

				redrawMenu(mode);
				break;
				}
			}
		}
		else 
		{
			switch(code)
			{
				case VK_RETURN: 
					isDone = true; 
				break;
				case VK_ESCAPE:
					mode = 0;
					isDone = true;
				break;
			}	
		}
	} 
	while (!isDone);

	return mode;
};