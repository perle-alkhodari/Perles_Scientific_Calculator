#include "Singleton.h"

// Private Methods

std::vector<wxString> Singleton::GetOutputQueue(wxString expression)
{

	wxString str = expression;
	wxStringTokenizer tokenizer(str, ' ');
	std::vector<wxString> outputQueue;
	std::vector<wxString> operatorStack;

	while (tokenizer.HasMoreTokens()) {
		wxString currentToken = tokenizer.GetNextToken();

		if (!IsOperator(currentToken)) {
			outputQueue.push_back(currentToken);
		}

		else {
			wxString currentOperator = currentToken;
			while (!operatorStack.empty() && operators[operatorStack[operatorStack.size() - 1]] < operators[currentOperator]) {
				wxString poppedOperator = operatorStack[operatorStack.size() - 1];
				operatorStack.pop_back();
				outputQueue.push_back(poppedOperator);
			}
			operatorStack.push_back(currentOperator);
		}
	}
	while (!operatorStack.empty()) {
		wxString operator_ = operatorStack[operatorStack.size() - 1];
		outputQueue.push_back(operator_);
		operatorStack.pop_back();
	}

	return outputQueue;
}

bool Singleton::IsOperator(wxString str)
{
	bool result = false;
	if (operators.find(str) != operators.end()) {
		result = true;
	}
	return result;
}

double Singleton::Eval(wxString expression)
{
	double result = 0.0;
	std::vector<wxString> outputQueue = GetOutputQueue(expression);
	std::vector<wxString> stack;
	std::map<wxString, int> trigOperations = { {"Sin", 1}, {"Cos", 2}, {"Tan", 3} };
	double n1, n2;

	// While output queue isnt empty
	while (!outputQueue.empty()) {

		// Take first item and pop it
		wxString token = outputQueue.at(0);
		outputQueue.erase(outputQueue.begin());

		// Check if the item is an operator or not
		if (!IsOperator(token)) {
			// If it is not an operator and instead a number, I push it in stack
			stack.push_back(token);
		}

		// If it's an operator...
		else {

			// I take the last value in the stack
			stack[stack.size() - 1].ToDouble(&n2);
			stack.pop_back();

			// And first check if my operator is a trig func
			if (trigOperations.find(token) != trigOperations.end()) {

				// If it is, I use it on the value from the stack and end the iteration.
				switch ((char)token[0]) {
				case 'S':
					result = sin(n2);
					break;
				case 'C':
					result = cos(n2);
					break;
				case 'T':
					result = tan(n2);
					break;
				}
			}
			// If my operator isn't a trig func
			else {

				// I'll pop back the next value in the stack and evaluate the expression.
				stack[stack.size() - 1].ToDouble(&n1);
				stack.pop_back();
				switch ((char)token[0]) {
				case 'x':
					result = n1 * n2;
					break;
				case '/':
					result = n1 / n2;
					break;
				case '%':
					result = (int)n1 % (int)n2;
					break;
				case '+':
					result = n1 + n2;
					break;
				case '-':
					result = n1 - n2;
					break;
				}
			}

			// I push the result back into the stack.
			stack.push_back(std::to_string(result));
		}
	}

	stack[0].ToDouble(&result);
	return result;
}

Singleton* Singleton::uniqueInstance = nullptr;