#include "CommandLog.h"
#include <iostream>
CommandLog* CommandLog::m_instance = nullptr;

CommandLog::CommandLog()
{
}


CommandLog* CommandLog::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CommandLog();
		m_instance->m_currentIndex = 1;
	}
	return m_instance;
}


void CommandLog::AddEntry(std::string string)
{
	if (m_log.empty())
	{
		m_log.push_back(string);
	}
	else
	{
		if (m_log.back() != string)
		{
			m_log.push_back(string);
		}
	}
	std::cout << "Current memento vector size: " << m_log.size() << std::endl;
}

std::string CommandLog::GetEntry()
{
	if (m_log.empty())
	{
		return "";
	}
	else
	{
		return m_log[(m_log.size() - m_currentIndex)];
	}
	m_currentIndex = 0;
}

void CommandLog::CycleUp()
{
	if (!(m_log.empty()))
	{
		if (m_currentIndex == m_log.size())
		{
			m_currentIndex = 1;
		}
		else if (m_log.size() > m_currentIndex)
		{
			m_currentIndex++;
		}
	}
	else
	{
		m_currentIndex = 1;
	}
	std::cout << "current memento index " << m_currentIndex << std::endl;
}

void CommandLog::CycleDown()
{
	if (!(m_log.empty()))
	{
		if (m_currentIndex == 1)
		{
			m_currentIndex = m_log.size();
		}
		else if (m_currentIndex > 1)
		{
			m_currentIndex--;
		}
	}
	else
	{
		m_currentIndex = 1;
	}
	std::cout << "current memento index " << m_currentIndex << std::endl;
}
