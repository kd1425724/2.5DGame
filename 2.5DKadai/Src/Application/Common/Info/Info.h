#pragma once

class Info
{
public:

	static const int ScrWidth = 1280;
	static const int ScrHeight = 720;
	

private:
	Info(){}
	~Info(){}

public:

	static Info& Instance()
	{
		static Info instance;
		return instance;
	}
};

#define INFO Info::Instance()

