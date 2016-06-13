#pragma once
#include <vector>
class CommandLog
{
public:
	static CommandLog* GetInstance();

	void AddEntry(std::string string);
	std::string GetEntry();
	void CycleUp();
	void CycleDown();
private:
	static CommandLog* m_instance;

	CommandLog();

	int m_currentIndex;
	std::vector<std::string> m_log;
};

