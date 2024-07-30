#pragma once

#include "wx/wx.h"

class Window;

class App : public wxApp
{
private:

	Window* window = nullptr;

public:

	virtual bool OnInit();
};

