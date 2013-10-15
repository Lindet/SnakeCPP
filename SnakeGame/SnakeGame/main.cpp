#include <Windows.h>
#include <d3d9.h>
#include <conio.h> 
#include <stddef.h>
#include "SnakeBody.h"
#pragma comment (lib, "d3d9.lib")

LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;
SnakeBody *snake = new SnakeBody();
int speed = 3;
int timer = 0;
int key;

void initD3D(HWND hWnd);
void render_frame(void);
void cleanD3D(void);
void UpdateLogic(void);
void DrawRectangle(LPDIRECT3DDEVICE9 Device_Interface, int x1, int y1, int x2, int y2, D3DCOLOR COLOR);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#pragma region

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    HWND hWnd;
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "WindowClass";
    RegisterClassEx(&wc);
    hWnd = CreateWindowEx(NULL, "WindowClass", "Test Direct3D Program", WS_OVERLAPPEDWINDOW, 300, 300, 800, 600, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    initD3D(hWnd);
    MSG msg;
	
    while(TRUE) 
	{
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if(msg.message == WM_QUIT) break;
		if(_kbhit())
		{
			key = getch();
		}
        render_frame();
		UpdateLogic();
    }
    cleanD3D();
    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch(message) 
	{
		case WM_KEYDOWN:
			{
				switch(wParam)
				{					
					case VK_LEFT:
						if(snake->head!=1)
							snake->head = 3;
						return 0;
					case VK_RIGHT:
						if(snake->head!=3)
							snake->head = 1;
						return 0;
					case VK_DOWN:
						if(snake->head!=4)
							snake->head = 2;
						return 0;
					case VK_UP:
						if(snake->head!=2)
							snake->head = 4;
						return 0;
					case VK_ESCAPE:
						SendMessage(hWnd, WM_CLOSE, 0, 0);
						return 0;
					default:
						return 0;
				}
			}
			
        case WM_DESTROY: 
			{
                PostQuitMessage(0);
                return 0;
            } 

    }
    return DefWindowProc (hWnd, message, wParam, lParam);
}

void initD3D(HWND hWnd) 
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
}

void cleanD3D(void) 
{
    d3ddev->Release();
    d3d->Release();
}

void DrawRectangle(LPDIRECT3DDEVICE9 Device_Interface, int x1, int y1, int x2, int y2, D3DCOLOR Color)
{
	D3DRECT rec;
	rec.x1 = x1;
	rec.y1 = y1;
	rec.x2 = x2;
    rec.y2 = y2;
    Device_Interface->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
}

#pragma endregion

void render_frame(void) 
{
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3ddev->BeginScene();
	
	//Общие границы экрана
	DrawRectangle(d3ddev,1,1,785,5, D3DCOLOR_XRGB(255, 255, 255)); //верхняя граница
	DrawRectangle(d3ddev,1,1,5,565, D3DCOLOR_XRGB(255, 255, 255));	//левая граница
	DrawRectangle(d3ddev,780,1,785,598, D3DCOLOR_XRGB(255, 255, 255)); // правая граница
	DrawRectangle(d3ddev,1,558,786,563, D3DCOLOR_XRGB(255, 255, 255)); // нижняя граница

	//Границы игрового поля	
	DrawRectangle(d3ddev,580,1,585,598, D3DCOLOR_XRGB(255, 255, 255)); // ограничение поля с правой стороны	
	DrawRectangle(d3ddev,1,460,580,465, D3DCOLOR_XRGB(255, 255, 255)); // ограничение поля с нижней стороны
	DrawRectangle(d3ddev,580,158,785,163, D3DCOLOR_XRGB(255, 255, 255)); //перемычка в интерфейсе справа

	for(int i = 0; i< snake->SnakeDirection.size()-1;i++)
	{
		DrawRectangle(d3ddev, snake->SnakeDirection[i].first+1, snake->SnakeDirection[i].second+1, snake->SnakeDirection[i].first+8, snake->SnakeDirection[i].second+8, D3DCOLOR_XRGB(255, 255, 255));
	}
	d3ddev->EndScene();
    d3ddev->Present(NULL, NULL, NULL, NULL);
}


void UpdateLogic()
{
	if(timer == speed)
	{
		snake->Move();
		timer = 0;
	}
	else timer++;
}




