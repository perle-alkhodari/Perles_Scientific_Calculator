#pragma once
#include "wx/wx.h"
#include <string>
#include <functional>

class Window;

class ButtonFactory
{
private:
	wxFrame* parent_ = nullptr;
	int buttonID;
	int spacing_;
	int startingX_;
	int startingY_;
	int buttonSizeX_;
	int buttonSizeY_;
public:
	ButtonFactory(int spacing, int startingX, int startingY,
		int buttonSizeX, int buttonSizeY, wxFrame* parent, int startingID=0) :spacing_(spacing), startingX_(startingX),
		startingY_(startingY), buttonSizeX_(buttonSizeX), buttonSizeY_(buttonSizeY),
		parent_(parent), buttonID(startingID) {
		
		if (startingID == 0) buttonID = 10000;
	}

	// Setters
	void SetStartingX(int startingX) { startingX_ = startingX; }
	void SetStartingY(int startingY) { startingY_ = startingY; }
	void SetButtonSizeX(int buttonSizeX) { buttonSizeX_ = buttonSizeX; }
	void SetButtonSizeY(int buttonSizeY) { buttonSizeY_ = buttonSizeY; }
	void SetSpacing(int spacing) { spacing_ = spacing; }
	void SetStartingID(int startingID) { buttonID = startingID; }

	// Methods
	void CreateNumberPad();
	void MakeRow(std::vector<std::string>labels);
	void NextRow();
};

