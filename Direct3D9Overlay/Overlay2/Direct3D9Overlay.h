// https://docs.microsoft.com/zh-cn/windows/desktop/medfound/hardware-overlay-support
// https://stackoverrun.com/cn/q/2021432
// http://www.cnblogs.com/gamesky/archive/2013/03/28/2986919.html
// https://yq.aliyun.com/articles/10791

#pragma once
#include "../Overlay/Color.h"

class CDirect3D9Overlay
{
public:
	CDirect3D9Overlay();
	~CDirect3D9Overlay();

	HRESULT CreateOverlay(HWND hWnd, std::wstring szGameWindowTitle);
	void Shutdown(void);
	bool Render(void);
	bool AddFont(std::wstring szName, std::wstring szFontName, int Height, int Width, int Weight, bool Italic);
	ID3DXFont* GetFont(std::wstring szName);
	
protected:
	HRESULT Startup(HWND hWindow);

	//Render
	void String(int x, int y, Color color, ID3DXFont* pFont, const wchar_t *fmt, ...);
	void StringOutlined(int x, int y, Color color, ID3DXFont* pFont, const wchar_t *fmt, ...);
	void Rect(int x, int y, int l, int h, Color color);
	void BorderBox(int x, int y, int l, int h, int thickness, Color color);
	void BorderBoxOutlined(int x, int y, int l, int h, int thickness, Color color, Color outlined);
	void Texture(int x, int y, LPDIRECT3DTEXTURE9 dTexture, LPD3DXSPRITE Sprite);
	void RectOutlined(int x, int y, int l, int h, Color rectcolor, Color outlinedcolor, int thickness);
	void Line(int x, int y, int x2, int y2, Color color, float thickness = 1);
	void GardientRect(int x, int y, int w, int h, int thickness, bool outlined, Color from, Color to, Color Outlined);

private:
	HWND m_hWndTarget;
	HWND m_hWndOverlay;
	std::wstring m_strGameTitle;

	IDirect3D9Ex* m_pD3D9Ex;
	IDirect3DDevice9Ex* m_pD3DDevice9Ex;
	ID3DXLine* m_pD3DLine;
	struct D3DFont_t
	{
		std::wstring szName;
		ID3DXFont* pFont;
	};
	std::vector<D3DFont_t> m_vecFont;
};