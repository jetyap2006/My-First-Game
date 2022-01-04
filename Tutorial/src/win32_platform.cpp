#include <windows.h>
#include "utils.cpp"

struct Render_State
{
	int width;
	int height;
	void* memory;
	BITMAPINFO bitmapinfo;
};

global Render_State render_state;

#include "renderer.cpp"
#include "platform_common.cpp"
#include "game.cpp"

global bool running = true;

LRESULT CALLBACK window_callback(HWND hWnd, UINT Msg, WPARAM  wParam, LPARAM  lParam)
{	
	LRESULT result = 0;
	switch (Msg)
	{
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
		break;
	}
	case WM_SIZE: {
		
		RECT rect;
		GetClientRect(hWnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;

		int buffer_size = render_state.width * render_state.height * sizeof(u32);

		//if memory already exists, free it
		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);

		//Allocate buffer memory
		render_state.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_state.bitmapinfo.bmiHeader.biSize = sizeof(render_state.bitmapinfo.bmiHeader);
		render_state.bitmapinfo.bmiHeader.biWidth = render_state.width;
		render_state.bitmapinfo.bmiHeader.biHeight = render_state.height;
		render_state.bitmapinfo.bmiHeader.biPlanes = 1;
		render_state.bitmapinfo.bmiHeader.biBitCount = 32;
		render_state.bitmapinfo.bmiHeader.biCompression = BI_RGB;

		break;
	}
	default:
		result = DefWindowProc(hWnd, Msg, wParam, lParam);
		break;
	}
	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	//Create Window Class
	const wchar_t CLASS_NAME[] = L"Game Window";
	WNDCLASS window_class = {};

	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = CLASS_NAME;
	window_class.lpfnWndProc = window_callback;

	//Register Class
	RegisterClass(&window_class);

	//Create Window
	HWND window = CreateWindow(window_class.lpszClassName, CLASS_NAME, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, hInstance, NULL);
	HDC hdc = GetDC(window);

	float delta_time = 0.166666f;
	LARGE_INTEGER frame_begin_time;               //First frame time
	QueryPerformanceCounter(&frame_begin_time);   //  return cpu counts

	LARGE_INTEGER perf_freq;
	QueryPerformanceFrequency(&perf_freq); // return cpu counts per second

	Input input = {};


	while (running)
	{
		//Input
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++)  //reset button status each frame 
		{
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

				switch (vk_code)
				{
					process_key(BUTTON_UP, VK_UP);
					process_key(BUTTON_DOWN, VK_DOWN);
					process_key(BUTTON_W, 0x57);
					process_key(BUTTON_S, 0x53);
				}

				break;
			}

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
				break;
			}

			}

		}

		// Simulate
		simulate_game(&input, delta_time);

		// Render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / perf_freq.QuadPart;
		frame_begin_time = frame_end_time;
	}
}