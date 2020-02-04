#pragma once

class CTabControler
{
public:
	CTabControler(void);
	~CTabControler(void);

public:
	void Hide_All_Image();
	void Show_Image_Tab(int index);

	void Hide_All_Parameters();
	void Show_Parameters_Tab(int index);
};
