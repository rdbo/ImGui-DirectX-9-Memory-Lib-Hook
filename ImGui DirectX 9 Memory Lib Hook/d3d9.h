#pragma once
#include "pch.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#if defined(ARCH_X86)
#define ENDSCENE_HOOK_LENGTH 7
#define WNDPROC_INDEX GWL_WNDPROC
#elif defined(ARCH_X64)
#define ENDSCENE_HOOK_LENGTH 15
#define WNDPROC_INDEX GWLP_WNDPROC
#endif

#define RELEASE_D3D 1

namespace D3D9
{
	typedef long(__stdcall* EndScene_t)(LPDIRECT3DDEVICE9);
	typedef LRESULT(__stdcall* WndProc_t)(const HWND, UINT, WPARAM, LPARAM);
	extern mem_t EndSceneAddress;
	extern EndScene_t oEndScene;
	extern WndProc_t oWndProc;
	extern HWND hWnd;
	extern void* vTable[119];

	void InitImGui(LPDIRECT3DDEVICE9 pDevice);
	LRESULT __stdcall hkWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool CreateDummyDevice(void** vtable, size_t size);
	long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice);
}