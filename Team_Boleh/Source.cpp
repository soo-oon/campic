#include "Application.hpp"

int main()
{
	Application app;

	if (!app.Initialize())
		return -1;

	while (!app.Exit)
	{
		app.Update();
	}
	
	app.ShutDown();
	return 0;
}
