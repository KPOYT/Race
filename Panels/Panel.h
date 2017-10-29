#ifndef OS_H
#define OS_H
#include "..\ApplicationOS\OS.h"
#endif

class Panel {
	public:
		Panel(const string desc);

		Panel(const COORD pos, const string desc);
		
		Panel(const int x, const int y, const string desc);

		virtual ~Panel();

		virtual const int show() = 0;

	protected:
		virtual void redrawPanel(
							int mode, 
							int textColor = OSConsole::White, 
							int backgroundColor = OSConsole::Black);

		OSConsole* console;
		COORD position;
		string description;
};