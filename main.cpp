//
// main.cpp
//
//      Copyright (C) Kisel Studios. All rights reserved.
// 
// Utility for set all windows to dark mode. Main implementation module.
//

#include <windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

VOID EnableDarkMode(HWND hwnd)
{
  if (!IsWindow(hwnd))
    return;

  BOOL dark = TRUE;

  DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
}

VOID CALLBACK WinEventProc(HWINEVENTHOOK hook,
                           DWORD event,
                           HWND hwnd,
                           LONG idObject,
                           LONG idChild,
                           DWORD dwEventThread,
                           DWORD dwmsEventTime)
{
  if (event != EVENT_OBJECT_CREATE && event != EVENT_OBJECT_SHOW)
    return;

  if (idObject != OBJID_WINDOW)
    return;

  if (GetAncestor(hwnd, GA_ROOT) != hwnd)
    return;

  EnableDarkMode(hwnd);
}

INT WINAPI WinMain(HINSTANCE hInst,
                   HINSTANCE hPreInst,
                   LPSTR CmdLine,
                   INT ShowCmd)
{
  HWINEVENTHOOK 
    hook = SetWinEventHook(
    EVENT_OBJECT_CREATE,
    EVENT_OBJECT_SHOW,
    nullptr,
    WinEventProc,
    0,
    0,
    WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
  );

  MSG msg;

  while (GetMessage(&msg, nullptr, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWinEvent(hook);
  return 0;
}
