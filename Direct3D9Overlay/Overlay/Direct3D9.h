#ifndef __DIRECT3D9__
#define __DIRECT3D9__

#ifdef _WIN32
#pragma once
#endif

#include "Color.h"

namespace Direct3D9
{
	class Direct3D9Render
	{
	public:
		Direct3D9Render( void );
		~Direct3D9Render( void );

		void	String( int x, int y, Color color, ID3DXFont* pFont, const wchar_t *fmt, ... );
		void	StringOutlined( int x, int y, Color color, ID3DXFont* pFont, const wchar_t *fmt, ... );
		void	Rect( int x, int y, int l, int h, Color color );
		void	BorderBox( int x, int y, int l, int h, int thickness, Color color );
		void	BorderBoxOutlined( int x, int y, int l, int h, int thickness, Color color, Color outlined );
		void	Texture( int x, int y, LPDIRECT3DTEXTURE9 dTexture, LPD3DXSPRITE Sprite );
		void	RectOutlined( int x, int y, int l, int h, Color rectcolor, Color outlinedcolor, int thickness );
		void	Line( int x, int y, int x2, int y2, Color color, float thickness = 1 );
		void	GardientRect( int x, int y, int w, int h, int thickness, bool outlined, Color from, Color to, Color Outlined );
	};

	extern Direct3D9Render*	pRender;
	extern bool				Render( void );
	extern ID3DXFont*		GetFont( std::wstring szName );
	extern int				getWidth( void );
	extern int				getHeight( void );
	extern HRESULT			CreateOverlay(HWND hWnd, std::wstring szGameWindowTitle);
};

#endif