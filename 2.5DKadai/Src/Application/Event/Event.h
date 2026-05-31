#pragma once

class Event
{
public:
	Event(){}
	~Event(){}

	//イベントを追加
	void SetEvent(std::function<void()> event);

	//指定したイベントを発生
	void AddEvent();


private:
	
	std::map<std::string,std::function<void()>> m_event;

};

