#include "stdafx.h"
#include "Direct3D9Overlay.h"

CDirect3D9Overlay::CDirect3D9Overlay()
	: m_hWndTarget(NULL)
	, m_hWndOverlay(NULL)
	, m_pD3D9Ex(NULL)
	, m_pD3DDevice9Ex(NULL)
	, m_pD3DLine(NULL)
{

}

CDirect3D9Overlay::~CDirect3D9Overlay()
{

}

HRESULT CDirect3D9Overlay::CreateOverlay(HWND hWnd, std::wstring szGameWindowTitle)
{
	m_strGameTitle = szGameWindowTitle;

	if (!m_strGameTitle.c_str())
		return E_FAIL;

	m_hWndTarget = FindWindowW(NULL, szGameWindowTitle.c_str());
	if (!m_hWndTarget)
		return E_FAIL;

	RECT rect_client, rect_app;

	GetClientRect(m_hWndTarget, &rect_client);

	m_hWndOverlay = hWnd;

	if (!m_hWndOverlay)
		return E_FAIL;

	MARGINS mgDWMMargins = { -1, -1, -1, -1 };
	DwmExtendFrameIntoClientArea(m_hWndOverlay, &mgDWMMargins);
	ShowWindow(m_hWndOverlay, SW_SHOWDEFAULT);
	UpdateWindow(m_hWndOverlay);
	GetWindowRect(m_hWndTarget, &rect_app);

	int border_x = GetSystemMetrics(SM_CXBORDER);
	int border_y = GetSystemMetrics(SM_CYCAPTION);

	int x = rect_app.left + (rect_client.right - RENDER_WIDTH) / 2;
	int y = rect_app.top + (rect_client.bottom - RENDER_HEIGHT) / 2;
	MoveWindow(m_hWndOverlay, x, y, RENDER_WIDTH, RENDER_HEIGHT, TRUE);

	return(SUCCEEDED(Startup(m_hWndOverlay)));
}

HRESULT CDirect3D9Overlay::Startup(HWND hWindow)
{
	BOOL	bComposition = false;
	DWORD	msqAAQuality = 0x0;
	HRESULT	hResult = NULL;

	hResult = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_pD3D9Ex);
	if (FAILED(hResult))
		return E_FAIL;

	D3DPRESENT_PARAMETERS pParameter = { 0 };
	pParameter.Windowed = TRUE;
	pParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pParameter.BackBufferFormat = D3DFMT_A8R8G8B8;
	pParameter.EnableAutoDepthStencil = TRUE;
	pParameter.AutoDepthStencilFormat = D3DFMT_D16;
	pParameter.MultiSampleType = D3DMULTISAMPLE_NONE;
	pParameter.PresentationInterval = 0x80000000L;

	if (SUCCEEDED(m_pD3D9Ex->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, true, D3DMULTISAMPLE_NONMASKABLE, &msqAAQuality)))
	{
		pParameter.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
		pParameter.MultiSampleQuality = msqAAQuality - 1;
	}
	else
	{
		pParameter.MultiSampleType = D3DMULTISAMPLE_NONE;
	}

	hResult = m_pD3D9Ex->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pParameter, NULL, &m_pD3DDevice9Ex);
	if (FAILED(hResult))
		return E_FAIL;

	//==============================[ Add your custom Font here ]=================================//

	if (!AddFont(L"Arial", L"Arial", 14, 0, FW_NORMAL, false))
		return E_FAIL;

	if (!AddFont(L"Arial Bold", L"Arial", 14, 0, FW_BOLD, false))
		return E_FAIL;

	//============================================================================================//

	if (FAILED(D3DXCreateLine(m_pD3DDevice9Ex, &m_pD3DLine)))
		return E_FAIL;

	m_pD3DLine->SetWidth(1.0f);
	m_pD3DLine->SetPattern(0xFFFFFFFF);
	m_pD3DLine->SetAntialias(false);

	return S_OK;
}

void CDirect3D9Overlay::Shutdown(void)
{
	if (m_pD3DDevice9Ex != NULL)
		m_pD3DDevice9Ex->Release();

	if (m_pD3D9Ex != NULL)
		m_pD3D9Ex->Release();

	if (m_pD3DLine != NULL)
		m_pD3DLine->Release();

	for (std::vector<D3DFont_t>::iterator iter = m_vecFont.begin();
		iter != m_vecFont.end();
		++iter)
	{
		iter->szName = L"";
		iter->pFont->Release();
	}
	m_vecFont.clear();
}

bool CDirect3D9Overlay::Render(void)
{
	MSG uMSG = { 0 };
	if (PeekMessage(&uMSG, NULL, 0, 0, PM_REMOVE))
	{
		if (uMSG.message == WM_QUIT)
			return false;
		TranslateMessage(&uMSG);
		DispatchMessage(&uMSG);
	}

	m_pD3DDevice9Ex->Clear(NULL, NULL, D3DCLEAR_TARGET, 0x00000000, 1.f, NULL);

	if (SUCCEEDED(m_pD3DDevice9Ex->BeginScene()))
	{
		if (FindWindow(NULL, m_strGameTitle.c_str()))
		{
			GardientRect(0, 0, RENDER_WIDTH, RENDER_HEIGHT, 0, false, RED, BLUE, BLACK);
			String(0, RENDER_HEIGHT / 2, Color(255, 255, 255), GetFont(L"Arial"), L"4Z.External Base by ReactiioN'");
		}
		m_pD3DDevice9Ex->EndScene();
	}

	m_pD3DDevice9Ex->PresentEx(NULL, NULL, NULL, NULL, NULL);

	return true;
}

bool CDirect3D9Overlay::AddFont(std::wstring szName, std::wstring szFontName, int Height, int Width, int Weight, bool Italic)
{
	D3DFont_t font;
	if (FAILED(D3DXCreateFont(m_pD3DDevice9Ex, (INT)Height, (UINT)Width, (INT)Weight, 1, (BOOL)Italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, szFontName.c_str(), &font.pFont)))
		return false;

	font.szName = szName;
	m_vecFont.push_back(font);

	return true;
}

ID3DXFont* CDirect3D9Overlay::GetFont(std::wstring szName)
{
	for each (const D3DFont_t & font in m_vecFont)
	{
		if (0 == wcscmp(szName.c_str(), font.szName.c_str()))
			return font.pFont;
	}
	return NULL;
}

void CDirect3D9Overlay::String(int x, int y, Color color, ID3DXFont* pFont, const wchar_t *fmt, ...)
{
	wchar_t Buffer[4048];
	va_list vaList;
	va_start(vaList, fmt);
	vswprintf_s(Buffer, fmt, vaList);
	RECT rect_pos = { x, y, x + 500, y + 100 };
	pFont->DrawText(NULL, Buffer, -1, &rect_pos, DT_TOP, D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b()));
	va_end(vaList);
}
void CDirect3D9Overlay::StringOutlined(int x, int y, Color color, ID3DXFont* pFont, const wchar_t *fmt, ...)
{
	wchar_t Buffer[4048];
	va_list vaList;
	va_start(vaList, fmt);
	vswprintf_s(Buffer, fmt, vaList);
	this->String(x - 1, y, Color(0, 0, 0), pFont, Buffer);
	this->String(x, y - 1, Color(0, 0, 0), pFont, Buffer);
	this->String(x + 1, y, Color(0, 0, 0), pFont, Buffer);
	this->String(x, y + 1, Color(0, 0, 0), pFont, Buffer);
	this->String(x, y, color, pFont, Buffer);
	va_end(vaList);
}
void CDirect3D9Overlay::Rect(int x, int y, int l, int h, Color color)
{
	D3DRECT rect = { x, y, x + l, y + h };
	m_pD3DDevice9Ex->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b()), 0, 0);
}
void CDirect3D9Overlay::BorderBox(int x, int y, int l, int h, int thickness, Color color)
{
	this->Rect(x, y, l, thickness, color);
	this->Rect(x, y, thickness, h, color);
	this->Rect(x + l, y, thickness, h, color);
	this->Rect(x, y + h, l + thickness, thickness, color);
}
void CDirect3D9Overlay::BorderBoxOutlined(int x, int y, int l, int h, int thickness, Color color, Color outlined)
{
	this->BorderBox(x, y, l, h, thickness, color);
	this->BorderBox(x - 1, y - 1, l + 2, h + 2, 1, outlined);
	this->BorderBox(x + 1, y + 1, l - 2, h - 2, 1, outlined);
}
void CDirect3D9Overlay::Texture(int x, int y, LPDIRECT3DTEXTURE9 dTexture, LPD3DXSPRITE Sprite)
{
	Sprite->Draw(dTexture, NULL, NULL, &D3DXVECTOR3((float)x, (float)y, 0.0f), 0xFFFFFFFF);
}
void CDirect3D9Overlay::RectOutlined(int x, int y, int l, int h, Color rectcolor, Color outlinedcolor, int thickness)
{
	Rect(x, y, l, h, rectcolor);
	BorderBox(x - thickness, y - thickness, l + thickness, h + thickness, thickness, outlinedcolor);
}
void CDirect3D9Overlay::Line(int x, int y, int x2, int y2, Color color, float thickness)
{
	m_pD3DLine->SetWidth(thickness);
	D3DXVECTOR2 points[2];
	points[0].x = x;
	points[1].x = x2;
	points[0].y = y;
	points[1].y = y2;
	m_pD3DLine->Draw(points, 2, D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b()));
}
void CDirect3D9Overlay::GardientRect(int x, int y, int w, int h, int thickness, bool outlined, Color from, Color to, Color Outlined)
{
	float a = ((float)to.a() - (float)from.a()) / h;
	float r = ((float)to.r() - (float)from.r()) / h;
	float g = ((float)to.g() - (float)from.g()) / h;
	float b = ((float)to.b() - (float)from.b()) / h;

	for (int i = 0; i < h; i++)
	{
		int A = from.a() + a * i;
		int R = from.r() + r * i;
		int G = from.g() + g * i;
		int B = from.b() + b * i;
		this->Rect(x, y + i, w, 1, Color(A, R, G, B));
	}
	if (outlined)
	{
		this->BorderBox(x - thickness, y - thickness, w + thickness, h + thickness, thickness, Outlined);
	}
}
