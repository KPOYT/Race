#ifndef PANEL_H
#define PANEL_H
#include "Panel.h"
#endif

#ifndef STATEPANEL_H
#define STATEPANEL_H
#include "StatePanel.h"
#endif

class RightPanel : public Panel {
	public:
		RightPanel(
			const string desc = "",
			const int width = 20,
			const int height = 23);
		
		RightPanel(
			const COORD pos, 
			const string desc = "",
			const int width = 20,
			const int height = 23);
		
		RightPanel(
			const int x, 
			const int y, 
			const string desc = "",
			const int width = 20,
			const int height = 23);
		
		~RightPanel();

		const int show();

		void redrawPanel(
			const int distance,
			const int speed,
			const int fuel,
			const int textColor = OSConsole::White,
			const int backgroundColor = OSConsole::Black);

	private:
		void drawBorder();
		string intToStringWithKM(const int);

		StatePanel* distancePanel_;
		StatePanel* speedPanel_;
		StatePanel* fuelPanel_;

		int width_;
		int height_;
		string counter_;
};