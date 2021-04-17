#include "headers\App.h"
#include <sstream>
#include <iomanip>

App::App()
	:
	wnd(800, 600, "Learning CPP Game")
{}

int App::Go()
{
	while (true)
	{
			//process all messages pending, but to not block for new messages
			if (const auto ecode = Window::ProcessMessages())
			{
				//return if optional has value, means we're quitting, so return exit code
				return *ecode;
			}
			DoFrame();
	}

}

void App::DoFrame()
{
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str());
}