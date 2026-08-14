// MEngine entry point

#include "Windows/WindowsHeaderSet.h"

extern bool StartupWindows(IN HINSTANCE hInstance, IN MAYBE_UNUSED int32 nCmdShow);
extern int32 RunWindows(IN MAYBE_UNUSED HINSTANCE hInstance, IN MAYBE_UNUSED int32 nCmdShow);
extern void ShutdownWindows();

int32 WINAPI WinMain(IN HINSTANCE hInstance, IN MAYBE_UNUSED HINSTANCE hPrevInstance, IN MAYBE_UNUSED /**LPSTR */ char* lpCmdLine, IN MAYBE_UNUSED int32 nCmdShow)
{
  int32 result = 0;

  if (StartupWindows(hInstance, nCmdShow))
  {
    result = RunWindows(hInstance, nCmdShow);
  }
  ShutdownWindows();

  return result;
}