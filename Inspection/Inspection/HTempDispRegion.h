#pragma once
#include "halconcpp.h"
using namespace Halcon;
class CHTempDispRegion
{
public:
	CHTempDispRegion(void);
	~CHTempDispRegion(void);

public:
	HTuple m_WindowHandle;

public:
	void TempDispRegion(Hobject RegionToShow);
	void TempWindowClose();
};
