#ifndef _MY_DLL_H_
#define _MY_DLL_H_
extern "C" __declspec(dllexport) int Add(int &a, int &b);
extern "C" __declspec(dllexport) int Max(const int &a, const int &b);
extern "C" __declspec(dllexport) int Get(const int &a);
#endif