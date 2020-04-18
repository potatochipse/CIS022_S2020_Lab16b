// Module:		CIS023_S2020_Lab16b.cpp
// Author:		Miguel Antonio Logarta
// Date:		April 17, 2020
// Purpose:		Learn how to create a bi-directional linked list using class code.
//				Review creating object nodesand filling them with data.
//				Scroll through an object - based linked list to find a specific node after determining the direction based on user input.
//

#include "framework.h"
#include "CIS023_S2020_Lab16b.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWnd_Input;								// input field
HWND hWnd_Name;									// output fields
HWND hWnd_Dec;									// .
HWND hWnd_Hex;									// .
HWND hWnd_Oct;									// .
HWND hWnd_Bin;									// .

// Pointer to node objects
Matrix* firstNode, * lastNode, * currentNode, * newNode;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void LoadFile();								// load file into linked list
void DisplayData(Matrix* );								// Output the results

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CIS023S2020LAB16B, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIS023S2020LAB16B));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIS023S2020LAB16B));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+0);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CIS023S2020LAB16B);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 350, 275, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
			// did the value in the input field change?
			if (SendMessage(hWnd_Input, EM_GETMODIFY, NULL, NULL))		
			{
				// Variables here
				TCHAR szInput[TCHAR_SIZE];			// Input TCHAR
				int iInput;							// Input after conversion
				int iComparison;					// Int that is being compared to the user's input

				// Capture the input and store it in szInput
				SendMessage(hWnd_Input,
					WM_GETTEXT,
					TCHAR_SIZE,
					LPARAM(szInput));

				// Conversions to compare values
				iInput =  TCHARtoInt(szInput);
				iComparison = TCHARtoInt(currentNode->GetDec());

				// Check for any errors
				try 
				{
					// Throw exception if the user has enetered a number out of range
					if (iInput < 0 ||			
						iInput > 100 || 
						szInput[0] == '\0')		// If the TCHAR is invalid
						throw 1;

					while (iInput != iComparison)
					{
						if (iInput > iComparison)
						{
							// Go Next. Go up the list
							currentNode = currentNode->GetNext();
							iComparison = TCHARtoInt(currentNode->GetDec());
						}
						else
						{
							// Go Prev. Go down the list
							currentNode = currentNode->GetPrev();
							iComparison = TCHARtoInt(currentNode->GetDec());
						}
					}

					// Display the data
					DisplayData(currentNode);
				}
				catch (int)
				{
					// Display nothing
					DisplayData(nullptr);
				}
			}
		
			int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case BN_CLICKED:	// capture button click
			{
				
			}
				break;

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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CREATE:

		// prompt
		CreateWindow(TEXT("STATIC"),
			TEXT("Find decimal value (0 - 100):"),
			WS_VISIBLE | WS_CHILD,
			10, 10, 200, 20, hWnd, NULL, NULL, NULL);

		// labels
		CreateWindow(TEXT("STATIC"),
			TEXT("Name:"),
			WS_VISIBLE | WS_CHILD,
			10, 50, 110, 20, hWnd, NULL, NULL, NULL);
		CreateWindow(TEXT("STATIC"),
			TEXT("Decimal:"),
			WS_VISIBLE | WS_CHILD,
			10, 80, 110, 20, hWnd, NULL, NULL, NULL);
		CreateWindow(TEXT("STATIC"),
			TEXT("Hexadecimal:"),
			WS_VISIBLE | WS_CHILD,
			10, 110, 110, 20, hWnd, NULL, NULL, NULL);
		CreateWindow(TEXT("STATIC"),
			TEXT("Octal:"),
			WS_VISIBLE | WS_CHILD,
			10, 140, 110, 20, hWnd, NULL, NULL, NULL);
		CreateWindow(TEXT("STATIC"),
			TEXT("Binary:"),
			WS_VISIBLE | WS_CHILD,
			10, 170, 110, 20, hWnd, NULL, NULL, NULL);

		// create edit control for user input
		hWnd_Input = CreateWindow(TEXT("EDIT"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL | WS_CHILD | ES_NUMBER,
			220, 10, 30, 20, hWnd, NULL, NULL, NULL);

		// output static controls
		hWnd_Name = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 50, 170, 20, hWnd, NULL, NULL, NULL);
		hWnd_Dec = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 80, 170, 20, hWnd, NULL, NULL, NULL);
		hWnd_Hex = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 110, 170, 20, hWnd, NULL, NULL, NULL);
		hWnd_Oct = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 140, 170, 20, hWnd, NULL, NULL, NULL);
		hWnd_Bin = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 170, 170, 20, hWnd, NULL, NULL, NULL);

		// put your name in the window title
		SetWindowText(hWnd, TEXT("CIS 023, Lab 16b, Miguel Antonio Logarta"));

		// load file into linked list
		LoadFile();

		break;
	case WM_DESTROY:
		// Delete the linked list
		if (currentNode)							// If the list exists
		{
			lastNode->SetNext(nullptr);				// Set last node's next to null

			Matrix* tempNode = nullptr;				// Temporary node
			currentNode = firstNode;				// Start at the beginning of the list

			while (currentNode != nullptr)
			{
				tempNode = currentNode->GetNext();	// Save next node address
				delete currentNode;					// Delete current node
				currentNode = tempNode;				// Advance current node
			}
		}
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

// load the file into the linked list
void LoadFile()
{
	string strName = "";								// temps to hold file data
	string strDec = "";
	string strHex = "";
	string strOct = "";
	string strBin = "";

	ifstream fInput;									// file pointer

	try
	{
		fInput.open("CIS023_S2020_Lab16b_Data.csv");	// open file

		if (!fInput)
			throw 1;

		while (fInput.good())
		{
			// read data from file
			getline(fInput, strName, ',');
			getline(fInput, strDec, ',');
			getline(fInput, strHex, ',');
			getline(fInput, strOct, ',');
			getline(fInput, strBin, '\n');

			// Create a new node
			newNode = new Matrix(strName, strDec, strHex, strOct, strBin);

			// Append new node to circular linked list
			if (firstNode == nullptr)						// If list is empty
				firstNode = newNode;						// New node is now the first node
			else
			{												// Else if the list is not empty
				lastNode->SetNext(newNode);					// Last node not points to the new node
				newNode->SetPrev(lastNode);					// New node now points to the last node
			}

			lastNode = newNode;								// New node is now the last node
			firstNode->SetPrev(lastNode);					// First node points back to new last node
			lastNode->SetNext(firstNode);					// New last node points to first node

		}

		fInput.close();										// ALWAYS remember to close the file

		currentNode = firstNode;							// Start at the first node
		
	}
	catch (int)
	{
		MessageBox(NULL,
			TEXT("Failed to load file"),
			TEXT("File Error"),
			MB_ICONERROR);


	}
}

void DisplayData(Matrix* currentNode)
{
	if (currentNode != nullptr)										// If there is data to display from the node
	{
		SetWindowText(hWnd_Name, currentNode->GetName());			// Output name
		SetWindowText(hWnd_Dec, currentNode->GetDec());				// Output decimal value
		SetWindowText(hWnd_Hex, currentNode->GetHex());				// Output value in Hex
		SetWindowText(hWnd_Oct, currentNode->GetOct());				// Output value in Octaldecimal
		SetWindowText(hWnd_Bin, currentNode->GetBin());				// Output value in Binary
	}
	else
	{
		// Since there is nothing to display, set the window text to NULL
		SetWindowText(hWnd_Name, NULL);
		SetWindowText(hWnd_Dec, NULL);
		SetWindowText(hWnd_Hex, NULL);
		SetWindowText(hWnd_Oct, NULL);
		SetWindowText(hWnd_Bin, NULL);
	}
}

