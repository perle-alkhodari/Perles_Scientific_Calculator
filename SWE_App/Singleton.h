#include "wx/wx.h"
#include <map>
#include <wx/tokenzr.h>
#include <vector>

class Singleton {
private:
    static Singleton* uniqueInstance; // Singleton instance  
    Singleton() {
    }

    std::map<wxString, int> operators = { {"Sin", 1}, {"Cos", 1}, {"Tan", 1}, {"%", 2}, {"x", 3}, {"/", 3}, {"+", 4}, {"-", 4} };

    // Methods
    std::vector<wxString> GetOutputQueue(wxString expression);
    bool IsOperator(wxString str);
    double Eval(wxString expression);

public:
    static Singleton* getInstance() {
        if (uniqueInstance == nullptr) {
            uniqueInstance = new Singleton(); // Lazy initialization  
        }
        return uniqueInstance;
    }

    double Calculate(wxString expression) {
        return Eval(expression);
    }
};


