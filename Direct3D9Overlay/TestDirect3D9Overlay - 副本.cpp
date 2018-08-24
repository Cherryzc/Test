#include "stdafx.h"
#include <d3d9.h>

#pragma comment(lib, "d3d9")
#pragma comment(lib, "dxguid")

IDirect3DSwapChain9 *g_d3dswapchain;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		if (g_d3dswapchain)
			g_d3dswapchain->Present(NULL, NULL, NULL, NULL, D3DPRESENT_UPDATECOLORKEY);
		EndPaint(hwnd, &ps);
	}
	break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = MainWndProc;
	wc.lpszClassName = _T("foo");
	ATOM a = RegisterClass(&wc);
	DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT r = { 0,0,720,480 };
	AdjustWindowRect(&r, style, FALSE);

	HWND hwnd = CreateWindow(MAKEINTATOM(a), _T(""), style, 0, 0, r.right - r.left, r.bottom - r.top, NULL, NULL, wc.hInstance, NULL);

	IDirect3D9Ex *d3d9ex;
	Direct3DCreate9Ex(D3D_SDK_VERSION, &d3d9ex);

	IDirect3D9ExOverlayExtension *d3d9exovl;
	d3d9ex->QueryInterface(IID_IDirect3D9ExOverlayExtension, (void **)&d3d9exovl);

	D3DOVERLAYCAPS ocaps;
	d3d9exovl->CheckDeviceOverlayType(0, D3DDEVTYPE_HAL, 720, 480, D3DFMT_A8R8G8B8, NULL, D3DDISPLAYROTATION_IDENTITY, &ocaps);

	d3d9exovl->Release();

	D3DPRESENT_PARAMETERS pparms = {};
	pparms.BackBufferWidth = 720;
	pparms.BackBufferHeight = 480;
	pparms.BackBufferFormat = D3DFMT_X8R8G8B8;
	//	pparms.BackBufferFormat = (D3DFORMAT)MAKEFOURCC('Y','U','Y','2');
	pparms.Windowed = true;
	pparms.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	pparms.SwapEffect = D3DSWAPEFFECT_OVERLAY;
	//	pparms.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//	pparms.Flags = D3DPRESENTFLAG_VIDEO;
	pparms.Flags = D3DPRESENTFLAG_VIDEO | D3DPRESENTFLAG_OVERLAY_LIMITEDRGB;
	//	pparms.Flags = D3DPRESENTFLAG_VIDEO | D3DPRESENTFLAG_OVERLAY_YCbCr_xvYCC;

	IDirect3DDevice9Ex *d3ddevex;
	HRESULT hr = d3d9ex->CreateDeviceEx(0, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pparms, NULL, &d3ddevex);
	if (FAILED(hr))
		__debugbreak();

	hr = d3ddevex->GetSwapChain(0, &g_d3dswapchain);
	if (FAILED(hr))
		__debugbreak();

	IDirect3DSurface9 *surf;
	hr = d3ddevex->CreateOffscreenPlainSurface(720, 480, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &surf, NULL);
	if (FAILED(hr))
		__debugbreak();

	D3DLOCKED_RECT lr;
	hr = surf->LockRect(&lr, NULL, D3DLOCK_NOSYSLOCK);
	if (FAILED(hr))
		__debugbreak();

	for (int y = 0; y < 480; ++y) {
		BYTE *dst = (BYTE *)lr.pBits + lr.Pitch * y;
		BYTE rm = 0, gm = 0, bm = 0;
		switch (y / 120) {
		case 0:
			rm = gm = bm = 255;
			break;
		case 1:
			rm = 255;
			break;
		case 2:
			gm = 255;
			break;
		case 3:
			bm = 255;
			break;
		}

		bool half = (y % 120) < 60;

		for (int x = 0; x < 720; ++x) {
			BYTE val = (BYTE)((x * 256) / 720);

			if (half) {
				if (val < 16)
					val = 16;

				if (val > 235)
					val = 235;
			}

			dst[0] = val & bm;
			dst[1] = val & gm;
			dst[2] = val & rm;
			dst[3] = 255;
			dst += 4;
		}
	}

	surf->UnlockRect();

	IDirect3DSurface9 *rt;
	hr = d3ddevex->GetRenderTarget(0, &rt);
	if (FAILED(hr))
		__debugbreak();

	for (;;) {
		MSG msg;
		if (MsgWaitForMultipleObjects(0, NULL, FALSE, 50, QS_ALLINPUT) == WAIT_OBJECT_0) {
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT)
					goto xit;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			continue;
		}

		hr = d3ddevex->BeginScene();
		if (FAILED(hr))
			__debugbreak();

		hr = d3ddevex->Clear(0, NULL, D3DCLEAR_TARGET, 0x10401010, 0, 0);
		if (FAILED(hr))
			__debugbreak();

		hr = d3ddevex->UpdateSurface(surf, NULL, rt, NULL);
		if (FAILED(hr))
			__debugbreak();

		hr = d3ddevex->EndScene();
		if (FAILED(hr))
			__debugbreak();

		RECT r;
		GetClientRect(hwnd, &r);

		int w = r.right;
		int h = r.bottom;
		if (w > 720)
			w = 720;
		if (h > 480)
			h = 480;

		r.right = w;
		r.bottom = h;

		hr = g_d3dswapchain->Present(&r, &r, NULL, NULL, 0);
		if (FAILED(hr))
			__debugbreak();

	}

xit:
	rt->Release();
	surf->Release();
	g_d3dswapchain->Release();
	d3ddevex->Release();
	d3d9ex->Release();

	return 0;
}