#include "pch.h"
#include "d3d9.h"

namespace D3D9
{
	//Variables
	mem_t EndSceneAddress;
	EndScene_t oEndScene;
	WndProc_t oWndProc;
	HWND hWnd;
	void* vTable[119];
}

HWND g_hWnd;

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	pid_t wndPID;
	GetWindowThreadProcessId(handle, &wndPID);

	if (GetCurrentProcessId() != wndPID)
		return TRUE;

	g_hWnd = handle;
	return FALSE;
}

bool D3D9::CreateDummyDevice(void** vtable, size_t size)
{
	if (!vtable)
		return false;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D)
		return false;

	IDirect3DDevice9* pDummyDevice = NULL;
	hWnd = Memory::In::GetCurrentWindowHandle();

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;

	HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

	if (dummyDeviceCreated != S_OK)
	{
		d3dpp.Windowed = !d3dpp.Windowed;

		dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		if (dummyDeviceCreated != S_OK)
		{
			pD3D->Release();
			return false;
		}
	}

	memcpy(vtable, *reinterpret_cast<void***>(pDummyDevice), size);

#	if RELEASE_D3D
	pDummyDevice->Release();
	pD3D->Release();
#	endif
	return true;
}