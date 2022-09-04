#include<windows.h>

const wchar_t gClassName[] = L"myClass";

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	//클래스등록
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to register window class", L"Error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//클래스 생성
	hWnd = CreateWindowEx(NULL,
		gClassName,
		L"Hello GDI",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1240,
		960,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == nullptr)
	{
		MessageBox(nullptr, L"Failed to create Window", L"Error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	//메시지처리
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}

//윈도프로시져
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			RECT rc{ 200, 200,400,400 };


			HPEN bluePen = CreatePen(PS_DOT,1,RGB(0,0,255));
			HPEN oldPen = (HPEN)SelectObject(hdc, bluePen);

			MoveToEx(hdc, 0, 110, nullptr);
			LineTo(hdc, 100, 110);
			DeleteObject(bluePen);
			SelectObject(hdc, oldPen);

			HPEN  RedPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
			SelectObject(hdc, RedPen);

			MoveToEx(hdc, 100, 110, nullptr);
			LineTo(hdc, 300, 110);
			DeleteObject(RedPen);
			SelectObject(hdc, oldPen);

			HBRUSH hatchBrush = CreateHatchBrush(HS_CROSS,RGB(255,255,0));
			HBRUSH oldHatch = (HBRUSH)SelectObject(hdc,hatchBrush);

			Rectangle(hdc, 0, 0, 100, 100);
			DeleteObject(hatchBrush);
			SelectObject(hdc,oldHatch);

			hatchBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));

			SelectObject(hdc, hatchBrush);

			Ellipse(hdc, 700, 700, 900, 900);
			FillRect(hdc, &rc, hatchBrush);

			DeleteObject(hatchBrush);
			SelectObject(hdc, oldHatch);

			HBRUSH solidBrush = CreateSolidBrush(RGB(0,0,255));
			HBRUSH oldsolid = (HBRUSH)SelectObject(hdc,solidBrush);

			Ellipse(hdc, 300, 300, 400, 400);

			solidBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, solidBrush);

			
			Ellipse(hdc, 700, 700, 900, 900);
			SetPixel(hdc, 700, 100, RGB(255, 0, 0));

			DeleteObject(solidBrush);
			SelectObject(hdc, oldsolid);



			EndPaint(hWnd, &ps);
			break;
		}

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
