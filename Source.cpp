#include <windows.h>
#include<tchar.h>
#include <math.h>
#include "DescriptorHPGL.h"
#include "Line.h"
#include "PolyLine.h"
#include "Painter.h"
#include <fstream>


#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>

struct Leaks {
	~Leaks()
	{
		_CrtDumpMemoryLeaks();
	}
} _l;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd, int
	mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(WinName, _T("Каркас Windows-приложения"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, NULL, This,
		NULL);
	ShowWindow(hWnd, mode);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


DescriptorHPGL descriptor;
Painter painter;
std::ofstream file;
char* ch = new char('c');

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	static int x0, y0, sx = 0, sy = 0;
	switch (message)
	{
	case WM_CREATE:

		file.open("test.txt");
		file << "PU0,0;PD1,1;PD2,2;PD;3,3;PU";
		file.close();

		painter.recieveShapes(descriptor, "penis2.hpgl");
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);

	/*	Painter* another_painter(new Painter(painter));
		another_painter->draw(hdc);
		delete another_painter;*/

		Painter* another_painter = new Painter();
		*another_painter = painter;
		*another_painter = painter;
		delete another_painter;

		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, sx * painter.getRatioX(), sy * painter.getRatioY(), NULL);
		SetViewportExtEx(hdc, sx, sy, NULL);
		SetViewportOrgEx(hdc, 0, 0, NULL);

		painter.draw(hdc);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_MOUSEWHEEL:
		painter.changeRatio(GET_WHEEL_DELTA_WPARAM(wParam));
		InvalidateRect(hWnd, 0, 1);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}