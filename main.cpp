#include <windows.h>
#include <vector>
#include <random>
using namespace std;
const int weight = 600;
const int height = 500;
#define WM_LBUTTONDOWN 0x0201
int x = 100;
int y = height / 2;
int yv = 0;
vector<int> blocks;
vector<int> pos;
int time = 0;
int n = -1;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

   switch (uMsg)
   {
   case WM_LBUTTONDOWN:
   {
      yv = 40;
      return 0; // Message processed#
   }
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   case WM_TIMER:
      InvalidateRect(hwnd, NULL, TRUE);
      break;
   case WM_PAINT:
   {
      SetTimer(hwnd, 1, 16, NULL);
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);
      // All painting occurs here, between BeginPaint and EndPaint.
      RECT picture = {0, 0, weight, height};
      FillRect(hdc, &picture, CreateSolidBrush(RGB(59, 183, 240)));
      time++;
      if (time % 250 == 0)
      {
         blocks.push_back((rand() % 400) + 50);
         pos.push_back(weight);
         n++;
      }
      for (int i = 0; i < n; i++)
      {
         RECT pipeup = {pos[i] - 10, 0, pos[i] + 10, blocks[i] - 75};
         RECT pipedown = {pos[i] - 10, blocks[i] + 75, pos[i] + 10, height};
         FillRect(hdc, &pipeup, CreateSolidBrush(RGB(10, 250, 20)));
         FillRect(hdc, &pipedown, CreateSolidBrush(RGB(10, 250, 20)));
         for (int j = 0; j < blocks[i] - 75; j++)
         {
            for (int h = 0; h < 20; h++)
            {
               if (j + 10 > y && j - 10 < y && h + 10 + pos[i] > x && h - 10 + pos[i] < x)
               {
                  x = 100;
                  y = height / 2;
                  time = 0;
                  n = 0;
                  blocks.clear();
                  pos.clear();
               }
            }
         }
         for (int j = blocks[i] + 75; j < height; j++)
         {
            for (int h = 0; h < 20; h++)
            {
               if (j + 10 > y && j - 10 < y && h + 10 + pos[i] > x && h - 10 + pos[i] < x)
               {
                  x = 100;
                  y = height / 2;
                  time = 0;
                  n = 0;
                  blocks.clear();
                  pos.clear();
               }
            }
         }
         pos[i]--;
      }
      RECT player = {x - 10, y - 10, x + 10, y + 10};
      FillRect(hdc, &player, CreateSolidBrush(RGB(255, 255, 0)));
      y -= yv / 10;
      yv--;
      if (y > weight || y < 0)
      {
         x = 100;
         y = height / 2;
         time = 0;
         n = 0;
         blocks.clear();
         pos.clear();
      }
      EndPaint(hwnd, &ps);
   }
      return 0;
   }
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
   }
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
   // Register the window class.
   const wchar_t *CLASS_NAME = L"ClassName";
   WNDCLASSW wc = {};
   wc.lpfnWndProc = WindowProc;
   wc.hInstance = hInstance;
   wc.lpszClassName = CLASS_NAME;
   RegisterClass(&wc);
   // Create the window.
   HWND hwnd = CreateWindowExW(
       0,                   // Optional window styles.
       CLASS_NAME,          // Window class
       L"Titel",            // Window text
       WS_OVERLAPPEDWINDOW, // Window stylek
       // Size and position
       CW_USEDEFAULT, CW_USEDEFAULT, weight, height,
       NULL,      // Parent window
       NULL,      // Menu
       hInstance, // Instance handle
       NULL       // Additional application data
   );
   if (hwnd == NULL)
   {
      return 0;
   }
   ShowWindow(hwnd, nCmdShow);
   // Run the message loop.
   MSG msg = {};
   while (GetMessage(&msg, NULL, 0, 0) > 0)
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   return 0;
}
// g++ main.cpp -lgdi32 -DUNICODE -D_UNICODE -municode -o game.exe
