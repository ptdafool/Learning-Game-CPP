#pragma once
#include "headers\winexcludes.h"
#include "headers\ExceptionHandler.h"
#include <optional>
#include <string>
#include <sstream>
#include "Keyboard.h"
#include "Mouse.h"
//#include "graphics.h"

class Window
{
public:
	class Exception : public ExceptionHandler
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HWND hWnd;
		HRESULT hr;
	};
public:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "PtDaFool Direct3D Engine";
		static WindowClass wndClass;
		HINSTANCE hInst;
		HRESULT hr;
	};
public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;
public:
	Keyboard kbd;
	Mouse mouse;
};
/*public:
	Keyboard kbd;
	Mouse mouse;
	//	Graphics gfx;
	/*
private:
	// singleton manages registration/cleanup of window class


//	Graphics& Gfx();


//	std::unique_ptr<Graphics> pGfx;*/


// error exception helper macro


#define PTDA_EXCEPT(hr) Window::Exception( __LINE__,__FILE__,hr)
#define PTDA_LAST_EXCEPT() Window::Exception( __LINE__,__FILE__,GetLastError())