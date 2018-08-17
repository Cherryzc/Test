// Direct3D9Overlay.cpp : main source file for Direct3D9Overlay.exe
//

#include "stdafx.h"

#include "resource.h"

#include "MainDlg.h"
#include "Overlay/Direct3D9.h"
#include "Overlay2/Direct3D9Overlay.h"

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainDlg dlgMain;

	if(dlgMain.Create(NULL) == NULL)
	{
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}



	dlgMain.ShowWindow(nCmdShow);

	int nRet = 0;//theLoop.Run();

	//L"±£Œ¿¬‹≤∑Beta"
	//L"Brawlhalla"
	//L"League of Legends (TM) Client"
	
	CDirect3D9Overlay overLay;
	if (SUCCEEDED(overLay.CreateOverlay(dlgMain.m_hWnd, L"±£Œ¿¬‹≤∑Beta")))
	{
		while (overLay.Render())
		{
			Sleep(100);
		}
	}

// 	if (SUCCEEDED(Direct3D9::CreateOverlay(dlgMain.m_hWnd, L"League of Legends (TM) Client")))
// 	{
// 		while (Direct3D9::Render())
// 		{
// 			Sleep(100);
// 		}
// 	}


	if (dlgMain.IsWindow())
		dlgMain.DestroyWindow();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
