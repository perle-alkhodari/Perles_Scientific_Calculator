#pragma once
#include "wx/wx.h"
#include <vector>
#include <map>

class Singleton;
class ButtonFactory;

class Window : public wxFrame
{
private:
	wxTextCtrl* calculatorDisplay = nullptr;
	Singleton* calculatorInstance = nullptr;
	
	// Numbers, Unary, Binary and Backspace Buttons
	std::vector<wxButton*> numbersButtons;
	std::vector<wxButton*> binaryAndUnaryButtons;
	std::map<wxString, int> operators = { {"Sin", 1}, {"Cos", 1}, {"Tan", 1}, {"%", 2}, {"x", 3}, {"/", 3}, {"+", 4}, {"-", 4} };


	// Other buttons
	wxButton* plusMinusButton = nullptr;
	wxButton* numberZeroButton = nullptr;
	wxButton* decimalButton = nullptr;
	wxButton* equalButton = nullptr;
	wxButton* clearButton = nullptr;

public:
	Window();

	wxDECLARE_EVENT_TABLE();

	bool CheckErrors();
	bool IsOperator(wxString str);

	void OnNegative();
	void OnEquals();
	void OnBackspace();

	void OnSymbolClick(wxCommandEvent &evt);
};
