#include <windows.h>
#include <stdio.h>
using namespace std;
HWND textfield,button[4],textbox1,textbox2;
 char text1[100];
 char text2[100];
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
textfield = CreateWindow("STATIC","calculator",WS_VISIBLE|WS_CHILD ,80,20,65,25,hwnd,NULL,NULL,NULL);

textbox1 =  CreateWindow("EDIT","",WS_VISIBLE|WS_CHILD|WS_BORDER ,80,40,65,25,hwnd,NULL,NULL,NULL);
textbox2 =  CreateWindow("EDIT","",WS_VISIBLE|WS_CHILD|WS_BORDER ,80,80,65,25,hwnd,NULL,NULL,NULL);

 
	 button[0] =CreateWindow("Button", "+",WS_VISIBLE|WS_CHILD|WS_BORDER,10    ,120,30,25,hwnd,(HMENU) (1),NULL,NULL);
	 button[1] =CreateWindow("Button", "-",WS_VISIBLE|WS_CHILD|WS_BORDER,60   ,120,30,25,hwnd,(HMENU) (2),NULL,NULL);
	 button[2] =CreateWindow("Button","*",WS_VISIBLE|WS_CHILD|WS_BORDER,110    ,120,30,25,hwnd,(HMENU) (3),NULL,NULL);
	 button[3] =CreateWindow("Button", "/",WS_VISIBLE|WS_CHILD|WS_BORDER,160   ,120,30,25,hwnd,(HMENU) (4),NULL,NULL);
 



		break;
		case WM_COMMAND:
switch (LOWORD(wParam))
{
	case 1:
    {        
        int get1 = GetWindowText(textbox1, text1, 100);
        int get2 = GetWindowText(textbox2, text2, 100);

         
        double x1 = atof(text1);
        double x2 = atof(text2);
 
        double result = x1 + x2;
 
        char t[100]  ;
        sprintf(t, "%f", result);

         
        MessageBox(hwnd, t, "Result", MB_OK);
        break;
    }
	case 2:
    {        
        int get1 = GetWindowText(textbox1, text1, 100);
        int get2 = GetWindowText(textbox2, text2, 100);

         
        double x1 = atof(text1);
        double x2 = atof(text2);
 
        double result = x1 - x2;
 
        char t[100]  ;
        sprintf(t, "%f", result);

         
        MessageBox(hwnd, t, "Result", MB_OK);
        break;
    }case 3:
    {        
        int get1 = GetWindowText(textbox1, text1, 100);
        int get2 = GetWindowText(textbox2, text2, 100);

         
        double x1 = atof(text1);
        double x2 = atof(text2);
 
        double result = x1 * x2;
 
        char t[100]  ;
        sprintf(t, "%f", result);

         
        MessageBox(hwnd, t, "Result", MB_OK);
        break;
    }case 4:
    {        
        int get1 = GetWindowText(textbox1, text1, 100);
        int get2 = GetWindowText(textbox2, text2, 100);

         
        double x1 = atof(text1);
        double x2 = atof(text2);
 
        double result = x1 / x2;
 
        char t[100]  ;
        sprintf(t, "%f", result);

         
        MessageBox(hwnd, t, "Result", MB_OK);
        break;
    } 
}


break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255,105,180));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My calculator",WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}