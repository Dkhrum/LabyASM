#include "framework.h"
#include "WinApiKr2KhrisanenkoVar14.h"
#include <vector>
#include <fstream>
#include "commdlg.h"

#define MAX_LOADSTRING			100
#define HotKeyCtrlPlusL			1
#define HotKeyAltPlusS			2
#define HotKeyAltPlusO			3

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK ChangeNMDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPIKR2KHRISANENKOVAR14, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIKR2KHRISANENKOVAR14));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

std::vector<std::vector<bool>> matrix;
int N = 7;
int M = 7;
bool isStopped = false;
COLORREF color = RGB(255, 255, 0);

const int Timer1ID = 1;

void Life()
{
	std::vector<std::vector<bool>> newMatrix(N, std::vector<bool>(M));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			int count = 0;
						
			if (!matrix[i][j])
			{
				if (i != 0 && j != 0 && matrix[i - 1][j - 1]) //лево верх
					count++;
				else if (i < N - 1 && j != 0 && matrix[i + 1][j - 1]) // право верх
					count++;
				else if (i < N - 1 && j < M - 1 && matrix[i + 1][j + 1]) // право низ
					count++;
				else if ( i != 0 && j < M - 1 && matrix[i - 1][j + 1]) // лево низ
					count++;
				if (count == 1)
				{
					newMatrix[i][j] = !matrix[i][j];
					break;
				}
			}

				/* if (matrix[i - 1][j - 1])
					 count++;
				 if (i < N - 1 && matrix[i + 1][j - 1])
					 count++;
				 if (i < N - 1 && j < M - 1 && matrix[i + 1][j + 1])
					 count++;
				 if (j < M - 1 && matrix[i - 1][j + 1])
					 count++;*/ //ведет себя непредсказуемо но очень забавно, гляньте
			
		}
	}
	matrix = newMatrix;
}

void InitializeMatrix(int N, int M)
{
	std::vector<std::vector<bool>> newMatrix(N, std::vector<bool>(M));
	//int count = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (i == 3 && j == 3)
			{
				newMatrix[i][j] = true;
			}
			else
			{
				newMatrix[i][j] = false;
			}
		}
		matrix = newMatrix;
	}
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIKR2KHRISANENKOVAR14));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIKR2KHRISANENKOVAR14);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

DWORD dColors[3] = { 255,222,222 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		InitializeMatrix(N, M);
		RegisterHotKey(hWnd, HotKeyCtrlPlusL, MOD_CONTROL, 0x4C);
		RegisterHotKey(hWnd, HotKeyAltPlusS, MOD_ALT, 0x53);
		RegisterHotKey(hWnd, HotKeyAltPlusO, MOD_ALT, 0x4F);
		SetTimer(hWnd, Timer1ID, 1500, NULL);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_TIMER:
		if (!isStopped)
		{
			Life();
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_HOTKEY:
		switch (wParam)
		{
		case(HotKeyCtrlPlusL):
			CHOOSECOLOR cc;
			cc.Flags = CC_RGBINIT | CC_FULLOPEN;
			cc.hInstance = NULL;
			cc.hwndOwner = hWnd;
			cc.lCustData = 0L;
			cc.lpCustColors = dColors;
			cc.lpfnHook = NULL;
			cc.lpTemplateName = (LPCWSTR)NULL;
			cc.lStructSize = sizeof(cc);
			cc.rgbResult = RGB(255, 0, 0);
			if (ChooseColor(&cc)) {
				color = (COLORREF)cc.rgbResult;
			}
			UpdateWindow(hWnd);
			break;
		case(HotKeyAltPlusS):
			wchar_t filePath[MAX_PATH]; // MAX_PATH = 260; обычно больше поддерживать не имеет смысла.
			filePath[0] = '\0';

			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn); // Используется для совместимости между различными версиями структур.
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = filePath;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrFilter = TEXT("Все\0*.*\0Текстовые файлы\0*.txt\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrInitialDir = nullptr;
			//		ofn.Flags = OFN_OVERWRITEPROMPT; // Предупреждает о перезаписи.

			if (GetSaveFileName(&ofn))
			{
				auto path = ofn.lpstrFile;
				std::fstream fout(path);
				fout << N << " " << M << " ";
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						fout << matrix[i][j] << " ";
					}
				}
			}
			break;

		case(HotKeyAltPlusO):
			wchar_t filePath1[MAX_PATH]; // MAX_PATH = 260; обычно больше поддерживать не имеет смысла.
			filePath1[0] = '\0';
			OPENFILENAME ofn1;
			ZeroMemory(&ofn1, sizeof(ofn1));
			ofn1.lStructSize = sizeof(ofn1);
			ofn1.hwndOwner = hWnd; // Модальный!
			ofn1.lpstrFile = filePath1;
			ofn1.nMaxFile = MAX_PATH;
			ofn1.nFilterIndex = 1; // Выбранный фильтр, 1-based.
			ofn1.lpstrInitialDir = nullptr; // Начальная директория.
			ofn1.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // Нельзя открыть несуществующие файл/папку.

			if (GetOpenFileName(&ofn1))
			{
				auto path = ofn1.lpstrFile; // Получили путь. Дальше можно с ним работать.
				std::fstream fin(path);
				fin >> N >> M;

				std::vector<std::vector<bool>> newMatrix(N, std::vector<bool>(M));
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						int bol;
						fin >> bol;
						newMatrix[i][j] = bol;
					}
				}
				matrix = newMatrix;
			}
			else
			{
				MessageBox(hWnd, L"Problems with", L"Error", MB_OK);
			}
			UpdateWindow(hWnd);
			break;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		int count = 1;

		RECT rect;
		GetClientRect(hWnd, &rect);
		double delta = min((rect.right - rect.left) / M / 2, (rect.bottom - rect.top) / N);
		double beginFromLeft = (rect.right - rect.left - delta * M) / 64;
		double beginFromTop = (rect.bottom - rect.top - delta * N) / 2;

		auto penBrush = LOGBRUSH();
		penBrush.lbColor = RGB(0, 0, 200);
		auto pen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 3, &penBrush, 0, nullptr);
		SelectObject(hdc, pen);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (!matrix[i][j])
				{
					HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
					SelectObject(hdc, brush);
					Rectangle(hdc, (beginFromLeft + rect.left + delta * j) * 2, beginFromTop + rect.top + delta * i,
						(beginFromLeft + rect.left + delta * (j + 1)) * 2, beginFromTop + rect.top + delta * (i + 1));
					DeleteObject(brush);
				}
				else
				{
					HBRUSH brush = CreateSolidBrush(color);
					SelectObject(hdc, brush);
					Rectangle(hdc, (beginFromLeft + rect.left + delta * j) * 2, beginFromTop + rect.top + delta * i,
						(beginFromLeft + rect.left + delta * (j + 1)) * 2, beginFromTop + rect.top + delta * (i + 1));
					DeleteObject(brush);
				}
				++count;
			}
		}
		DeleteObject(pen);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
		switch (wParam) {
		case(VK_F2):
		{
			DialogBox(hInst, MAKEINTRESOURCE(ChangeNM), NULL, ChangeNMDialog);
			break;
		}
		case 0x57:
			isStopped = !isStopped;
			break;
		default:
			break;
		}
		break;
	case WM_LBUTTONDOWN:
	{

		int count = 1;
		POINT cursor;
		cursor.x = LOWORD(lParam);
		cursor.y = HIWORD(lParam);
		RECT rect;
		GetClientRect(hWnd, &rect);
		double delta = min((rect.right - rect.left) / M, (rect.bottom - rect.top) / N);
		double beginFromLeft = (rect.right - rect.left - delta * M) / 2;
		double beginFromTop = (rect.bottom - rect.top - delta * N) / 2;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (cursor.x > beginFromLeft + rect.left + delta * j &&
					cursor.x < beginFromLeft + rect.left + delta * (j + 1) &&
					cursor.y > beginFromTop + rect.top + delta * i &&
					cursor.y < beginFromTop + rect.top + delta * (i + 1))
				{
					if (!matrix[i][j])
					{
						matrix[i][j] = !matrix[i][j];
					}
				}

			}
		}
		InvalidateRect(hWnd, &rect, false);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


INT_PTR CALLBACK ChangeNMDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hWnd, IDC_EDIT1, N, false);
		SetDlgItemInt(hWnd, IDC_EDIT2, M, false);
		return true;
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			if (GetDlgItemInt(hWnd, IDC_EDIT1, nullptr, false) >= 3 &&
				GetDlgItemInt(hWnd, IDC_EDIT1, nullptr, false) <= 22 &&
				GetDlgItemInt(hWnd, IDC_EDIT2, nullptr, false) >= 3 &&
				GetDlgItemInt(hWnd, IDC_EDIT2, nullptr, false) <= 22)
			{
				N = GetDlgItemInt(hWnd, IDC_EDIT1, nullptr, false);
				M = GetDlgItemInt(hWnd, IDC_EDIT2, nullptr, false);
				InitializeMatrix(N, M);
			}
			else
			{
				MessageBox(hWnd, L"Wrong value of \"N\" or \"M\"", L"Error", MB_OK);
			}
			EndDialog(hWnd, LOWORD(wParam));
			break;
		case IDCANCEL:
			EndDialog(hWnd, LOWORD(wParam));
			break;
		}
	case WM_DESTROY:
		break;
	default:
		break;
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
