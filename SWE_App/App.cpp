#include "App.h"
#include "Window.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	App::SetTopWindow(window);
	window = new Window();
	window->Show();

	return true;
}