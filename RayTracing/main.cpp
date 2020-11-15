#include <Windows.h>
#include "draw.h"

int WIDTH = 1280;
int HEIGHT = 720;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			draw(hdc, WIDTH, HEIGHT);

			EndPaint(hWnd, &ps);
			break;
		}
		case WM_SIZE: {
			WIDTH = LOWORD(lParam);
			HEIGHT = HIWORD(lParam);
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	MSG msg{};
	HWND hWnd{};
	WNDCLASS wc{sizeof(WNDCLASSEX)};

	wc.hInstance = hInstance;
	wc.lpszClassName = L"RTClass";
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);

	if (!RegisterClass(&wc)) return 0;

	hWnd = CreateWindow(
		L"RTClass",
		L"RayTracingApp",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WIDTH,
		HEIGHT,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}