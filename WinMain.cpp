#include "Headers\Window.h"
#include <sstream>

int WINAPI WinMain(
	HINSTANCE	hInstance, 
	HINSTANCE	hPrevInstance, 
	LPSTR		lpCmdLine,
	int nShowCmd )
{
	try
	{
		Window wnd(800, 300, "Learning Game");
		//message pump
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				if (!wnd.mouse.IsEmpty())
				{
					const auto e = wnd.mouse.Read();
					if (e.GetType() == Mouse::Event::Type::WheelUp)
					{
						std::ostringstream oss;
						oss << "We got a wheel up! (Coordinates: " << e.GetPosX() << "," << e.GetPosY() << ")." << std::endl;
						wnd.SetTitle(oss.str());
					}
					else if (e.GetType() == Mouse::Event::Type::WheelDown)
					{
						std::ostringstream oss;
						oss << "We got a wheel down! (Coordinates: " << e.GetPosX() << "," << e.GetPosY() << ")." << std::endl;
						wnd.SetTitle(oss.str());
					}
				}
				/*if (!wnd.mouse.IsEmpty())
				{
					const auto e = wnd.mouse.Read();
					if (e.GetType() == Mouse::Event::Type::Leave)
					{
						wnd.SetTitle("Gone!");
					}
					
					/*else if (e.GetType() == Mouse::Event::Type::Move)
					{
						std::ostringstream oss;
						oss << "Mouse Position: (" << e.GetPosX() << "," << e.GetPosY() << ")" << std::endl;
						wnd.SetTitle(oss.str());
					}
				}
				/*if (wnd.kbd.KeyIsPressed(VK_SPACE))
				{
					MessageBox(nullptr, "Something Happened!", "Alt Key Pressed...", MB_OK| MB_ICONEXCLAMATION);
					wnd.SetTitle("Space Pressed");
				}
				*/
				/*while (!wnd.mouse.IsEmpty())
				{
					const auto e = wnd.mouse.Read();
					switch (e.GetType())
					{
					case Mouse::Event::Type::Leave:
						wnd.SetTitle("Gone!");
						break;

					case Mouse::Event::Type::Move:
					{
						std::ostringstream oss;
						oss << "Mouse moved to (" << e.GetPosX() << "," << e.GetPosY() << ")" << std::endl;
						wnd.SetTitle(oss.str());
					}
					break;
					case Mouse::Event::Type::LRelease:
						std::ostringstream oss;
						oss << "Left Mouse Click Detected at: (" << e.GetPosX() << "," << e.GetPosY() << ")" << std::endl;
						wnd.SetTitle(oss.str());
					}
				}*/
			}
		}
		if (gResult == -1)
		{
			throw CHWND_LAST_EXCEPT(); // if the message was an error, return -1 to indicate an error
		}
		return msg.wParam;
		}
	catch (const ExceptionHandler& e)
		{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
		}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr,"No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
}