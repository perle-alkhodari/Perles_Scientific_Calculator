#include "ButtonFactory.h"
#include "Window.h"


void ButtonFactory::CreateNumberPad()
{
	int startingx = startingX_;
	int startingy = startingY_;
	int n = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			n++;
			wxButton* newButton = new wxButton(parent_, buttonID, std::to_string(n),
				wxPoint(startingx, startingy), wxSize(buttonSizeX_, buttonSizeY_));
			startingx += buttonSizeX_ + spacing_;
			buttonID++;
		}
		startingx = startingX_;
		startingy += buttonSizeY_ + spacing_;
	}

	startingY_ = startingy;
}

void ButtonFactory::MakeRow(std::vector<std::string>labels)
{
	std::vector<std::string> l = labels;
	int startingx = startingX_;
	for (int i = 0; i < l.size(); i++) {
		wxButton* newButton = new wxButton(parent_, buttonID, l[i], wxPoint(startingx, startingY_), wxSize(buttonSizeX_, buttonSizeY_));
		buttonID++;
		startingx += buttonSizeX_ + spacing_;
	}
}

void ButtonFactory::NextRow()
{
	startingY_ += buttonSizeY_ + spacing_;
}
