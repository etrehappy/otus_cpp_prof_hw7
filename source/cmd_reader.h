#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <thread> // for PrintForCheck()
#include <chrono> 

#include "m_exceptions.h"

class CommandReader
{
public:
	CommandReader(size_t);
	~CommandReader() = default;

	void Read(std::istream&);
	std::vector<std::string>& GetCommands();
	bool IsEof() const;
	std::chrono::system_clock::time_point GetBulkTime() const;		

private:

	void ClearState();

	/*!
	* @brief Задание: Данные подаются на стандартный вход построчно с паузой
	*	в 1 секунду для визуального контроля.
	*/
	void PrintForCheck() const;

	const size_t max_command_number_;
	size_t command_counter_;
	std::vector<std::string> container_;
	std::chrono::system_clock::time_point bulk_time_;
	bool eof_flag_;
};


