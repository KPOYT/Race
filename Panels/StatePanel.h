#ifndef PANEL_H
#define PANEL_H
#include "Panel.h"
#endif

class StatePanel : public Panel {
	public:
		StatePanel(
			const string desc = "Ships:");
		
		StatePanel(
			const COORD pos, 
			const string desc = "Ships:");
		
		StatePanel(
			const int x, 
			const int y, 
			const string desc = "Ships:");
		
		~StatePanel();

		const int show();
		const void setTextAlign(const int);

		void redrawPanel(
			const int count, 
			const int textColor = OSConsole::White,
			const int backgroundColor = OSConsole::Black);

		void redrawPanel(
			const string count,
			const int textColor = OSConsole::White,
			const int backgroundColor = OSConsole::Black);

		enum TextAlignStates {
			Left = 0,
			Center = 1
		};
	private:
		int textAlign_;
		string counter_;
};