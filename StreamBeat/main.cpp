#include "Application.h"

int main()
{
	try
	{
		sb::Application app;
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}