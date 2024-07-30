#include "Window.h"
#include <math.h>
#include <queue>
#include <stack>
#include <map>
#include "ButtonFactory.h"
#include "Singleton.h"

#define WINDOW_WIDTH 715
#define WINDOW_HEIGHT 600
#define STARTING_X_POS 40
#define STARTING_Y_POS 150
#define SPACING 20
#define PADDING_LEFT 40
#define BOTTOM_ROW_Y_POS 450
#define UPPER_ROW_Y_POS 150
#define SECOND_SET_X_POS 380

#define BUTTON_SIZE 80

// Button Unique IDs
#define ID_CALCULATOR_DISPLAY 2001

#define ID_DIGIT_1 10000
#define ID_DIGIT_2 10001
#define ID_DIGIT_3 10002
#define ID_DIGIT_4 10003
#define ID_DIGIT_5 10004
#define ID_DIGIT_6 10005
#define ID_DIGIT_7 10006
#define ID_DIGIT_8 10007
#define ID_DIGIT_9 10008
#define ID_PLUS_MINUS_BUTTON 10009
#define ID_DIGIT_0 10010
#define ID_DECIMAL_BUTTON 10011
#define ID_EQUAL_BUTTON 10012
#define ID_CLEAR_BUTTON 10013
#define ID_SYMBOL_PLUS 10014
#define ID_SYMBOL_MINUS 10015
#define ID_SYMBOL_BACKSPACE 10016
#define ID_SYMBOL_MULTIPLY 10017
#define ID_SYMBOL_DIVIDE 10018
#define ID_SYMBOL_MODULO 10019
#define ID_SYMBOL_SIN 10020
#define ID_SYMBOL_COS 10021
#define ID_SYMBOL_TAN 10022

// Event table
wxBEGIN_EVENT_TABLE(Window, wxFrame)
EVT_BUTTON(ID_DIGIT_1, OnSymbolClick)
EVT_BUTTON(ID_DIGIT_2, OnSymbolClick)
EVT_BUTTON(ID_DIGIT_3, OnSymbolClick)
EVT_BUTTON(ID_DIGIT_4, OnSymbolClick)
EVT_BUTTON(ID_DIGIT_5, OnSymbolClick)
EVT_BUTTON(ID_DIGIT_6, OnSymbolClick)
EVT_BUTTON(ID_DIGIT_7, OnSymbolClick)
EVT_BUTTON(ID_DIGIT_8, OnSymbolClick)
EVT_BUTTON(ID_DIGIT_9, OnSymbolClick)
EVT_BUTTON(ID_DIGIT_0, OnSymbolClick)
EVT_BUTTON(ID_PLUS_MINUS_BUTTON, OnSymbolClick)
EVT_BUTTON(ID_DECIMAL_BUTTON, OnSymbolClick)
EVT_BUTTON(ID_EQUAL_BUTTON, OnSymbolClick)
EVT_BUTTON(ID_CLEAR_BUTTON, OnSymbolClick)
EVT_BUTTON(ID_SYMBOL_PLUS, OnSymbolClick)
EVT_BUTTON(ID_SYMBOL_MINUS, OnSymbolClick)
EVT_BUTTON(ID_SYMBOL_BACKSPACE, OnSymbolClick)
EVT_BUTTON(ID_SYMBOL_MULTIPLY, OnSymbolClick)
EVT_BUTTON(ID_SYMBOL_DIVIDE, OnSymbolClick)
EVT_BUTTON(ID_SYMBOL_MODULO, OnSymbolClick)
EVT_BUTTON(ID_SYMBOL_SIN, OnSymbolClick)
EVT_BUTTON(ID_SYMBOL_COS, OnSymbolClick)
EVT_BUTTON(ID_SYMBOL_TAN, OnSymbolClick)
wxEND_EVENT_TABLE()


Window::Window() : wxFrame(nullptr, wxID_ANY, "Perle's Calculator", wxPoint(200, 200), wxSize(WINDOW_WIDTH, WINDOW_HEIGHT), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {

	// Text Control
	wxFont displayFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	calculatorDisplay = new wxTextCtrl(this, ID_CALCULATOR_DISPLAY, "", wxPoint(PADDING_LEFT, 30), wxSize(WINDOW_WIDTH-95, 80), wxTE_READONLY);
	calculatorDisplay->SetFont(displayFont);
	
	// UI Numbers Buttons from 1-9
	ButtonFactory buttonFactory(SPACING, STARTING_X_POS, STARTING_Y_POS, BUTTON_SIZE, BUTTON_SIZE, this);
	buttonFactory.CreateNumberPad();
	buttonFactory.MakeRow({ "+/-", "0", "." });

	// Set new positions
	buttonFactory.SetStartingX(380);
	buttonFactory.SetStartingY(STARTING_Y_POS);
	buttonFactory.SetButtonSizeX(180);
	buttonFactory.MakeRow({ "=" });

	buttonFactory.SetStartingX(380 + 180 + SPACING);
	buttonFactory.SetButtonSizeX(80);

	buttonFactory.MakeRow({ "Clear" });

	buttonFactory.SetStartingX(380);
	buttonFactory.NextRow();

	buttonFactory.MakeRow({ "+", "-", "backspace" });
	buttonFactory.NextRow();

	buttonFactory.MakeRow({ "X", "/", "%" });
	buttonFactory.NextRow();

	buttonFactory.MakeRow({ "Sin", "Cos", "Tan" });

	calculatorInstance = Singleton::getInstance();
}


void Window::OnBackspace()
{
	wxString str = calculatorDisplay->GetValue();
	size_t str_size = str.size();

	if (str == "Error" || str.size() == 1) { calculatorDisplay->Clear(); }

	else if (!str.empty()) {

		char lastChar = str[str_size - 1];
		char c2 = str[str_size - 2];
		std::string lastTwoChars = std::string(1, c2) + lastChar;

		if (str.size() == 4 && ( str.starts_with("Sin") || str.starts_with("Cos") || str.starts_with("Tan") )) {
			str = "";
		}
		else if (lastTwoChars == "n " || lastTwoChars == "s ") {
			str.erase(str.begin() + str_size - 5, str.end());
		}
		else if (lastChar == ' ') {
			str.erase(str.begin() + str_size - 3, str.end());
		}
		else {
			str.erase(str.begin() + str_size - 1, str.end());
		}

		calculatorDisplay->Clear();
		calculatorDisplay->WriteText(str);
	}
}

void Window::OnEquals()
{
	if (!CheckErrors()) {
		double result = calculatorInstance->Calculate(calculatorDisplay->GetValue());
		calculatorDisplay->Clear();
		calculatorDisplay->WriteText(std::to_string(result));
	}
}

bool Window::CheckErrors()
{
	
	// Check for non decimal numbers:
	try {
		double test;
		wxString str = calculatorDisplay->GetValue();
		wxStringTokenizer tokenizer(str);
		int decimalCount = 0;
		int operatorCount = 0;

		// If there are impossible expressions...
		if (str.size() == 0 || str[str.size() - 1] == ' ' || str.Contains("Error") || str.Contains("% 0") || str.Contains("/ 0")) {
			throw std::logic_error("");
		}

		// If a number isn't parsable to double...
		while (tokenizer.HasMoreTokens()) {
			wxString currentToken = tokenizer.NextToken();
			if (!IsOperator(currentToken)) {
				currentToken.ToDouble(&test);
				decimalCount++;
			}
			else {
				operatorCount++;
			}
		}

		// If One or neither are present...
		if (decimalCount + operatorCount <= 1) throw std::logic_error("");
		return false;
	}
	catch (...) {
		calculatorDisplay->Clear();
		calculatorDisplay->WriteText("Error");
		return true;
	}


}

bool Window::IsOperator(wxString str)
{
	bool result = false;
	if (operators.find(str) != operators.end()) {
		result = true;
	}
	return result;
}

void Window::OnNegative()
{
	wxString str = calculatorDisplay->GetValue();
	calculatorDisplay->Clear();
	if (!str.empty()) {
		if (str[0] == '-') {
			str.erase(str.begin());
			calculatorDisplay->WriteText(str);
		}
		else {
			calculatorDisplay->Clear();
			calculatorDisplay->WriteText("-" + str);
		}
	}
}

void Window::OnSymbolClick(wxCommandEvent &evt)
{
	double test = 0;
	wxString text = calculatorDisplay->GetValue();
	size_t textSize = text.size();
	bool isFirstChar = textSize == 0 ? true : false;
	bool isNumber = true;
	bool lastIsOperatorOrDecimalOrNegation = false;
	if (!isFirstChar) {
		char lastChar = text[textSize - 1];
		lastIsOperatorOrDecimalOrNegation = lastChar == ' ' || lastChar == '.' || lastChar == '-' ? true : false;
	}

	if (calculatorDisplay->GetValue() == "Error") { calculatorDisplay->Clear(); }
	switch (evt.GetId()) {

	case ID_PLUS_MINUS_BUTTON:
		OnNegative();
		break;
	case ID_EQUAL_BUTTON:
		OnEquals();
		break;
	case ID_CLEAR_BUTTON:
		calculatorDisplay->Clear();
		break;
	case ID_SYMBOL_BACKSPACE:
		OnBackspace();
		break;


	case ID_DIGIT_0:
		calculatorDisplay->WriteText("0");
		break;
	case ID_DECIMAL_BUTTON:
		if (!isFirstChar && !lastIsOperatorOrDecimalOrNegation) calculatorDisplay->WriteText(".");
		break;
	case ID_DIGIT_1:
		calculatorDisplay->WriteText("1");
		break;
	case ID_DIGIT_2:
		calculatorDisplay->WriteText("2");
		break;
	case ID_DIGIT_3:
		calculatorDisplay->WriteText("3");
		break;
	case ID_DIGIT_4:
		calculatorDisplay->WriteText("4");
		break;
	case ID_DIGIT_5:
		calculatorDisplay->WriteText("5");
		break;
	case ID_DIGIT_6:
		calculatorDisplay->WriteText("6");
		break;
	case ID_DIGIT_7:
		calculatorDisplay->WriteText("7");
		break;
	case ID_DIGIT_8:
		calculatorDisplay->WriteText("8");
		break;
	case ID_DIGIT_9:
		calculatorDisplay->WriteText("9");
		break;
	case ID_SYMBOL_PLUS:
		if (!(lastIsOperatorOrDecimalOrNegation || isFirstChar)) calculatorDisplay->WriteText(" + ");
		break;
	case ID_SYMBOL_MINUS:
		if (isFirstChar) {
			calculatorDisplay->WriteText(" -");
		}
		else if (text[text.size() - 1] == ' ') {
			calculatorDisplay->WriteText("-");
		}
		else if (!text[text.size() - 1] == '-' || !lastIsOperatorOrDecimalOrNegation) {
			calculatorDisplay->WriteText(" - ");
		}
		isNumber = false;
		break;
	case ID_SYMBOL_MULTIPLY:
		if (!lastIsOperatorOrDecimalOrNegation && !isFirstChar) calculatorDisplay->WriteText(" x ");
		isNumber = false;
		break;
	case ID_SYMBOL_DIVIDE:
		if (!lastIsOperatorOrDecimalOrNegation && !isFirstChar) calculatorDisplay->WriteText(" / ");
		isNumber = false;
		break;
	case ID_SYMBOL_MODULO:
		if (!lastIsOperatorOrDecimalOrNegation && !isFirstChar) calculatorDisplay->WriteText(" % ");
		isNumber = false;
		break;
	case ID_SYMBOL_SIN:
		if (lastIsOperatorOrDecimalOrNegation || isFirstChar) calculatorDisplay->WriteText(" Sin ");
		isNumber = false;
		break;
	case ID_SYMBOL_COS:
		if (lastIsOperatorOrDecimalOrNegation || isFirstChar) calculatorDisplay->WriteText(" Cos ");
		isNumber = false;
		break;
	case ID_SYMBOL_TAN:
		if (lastIsOperatorOrDecimalOrNegation || isFirstChar) calculatorDisplay->WriteText(" Tan ");
		isNumber = false;
		break;
	}

	if (isFirstChar && !isNumber) {
		text = wxString(calculatorDisplay->GetValue());
		text.erase(text.begin());
		calculatorDisplay->Clear();
		calculatorDisplay->WriteText(text);
	}

	evt.Skip();
}

