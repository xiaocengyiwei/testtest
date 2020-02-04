#include "stdafx.h"
#include "HTempDispRegion.h"

CHTempDispRegion::CHTempDispRegion(void)
{
}

CHTempDispRegion::~CHTempDispRegion(void)
{
}

void CHTempDispRegion::TempDispRegion( Hobject RegionToShow )
{
	set_window_attr("background_color","black");
	open_window(0,0,512,512,0,"","",&m_WindowHandle);
	HDevWindowStack::Push(m_WindowHandle);
	disp_obj(RegionToShow,m_WindowHandle);
}

void CHTempDispRegion::TempWindowClose()
{
	close_window(m_WindowHandle);
}