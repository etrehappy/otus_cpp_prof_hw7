#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <chrono> 

#include "observer.h"


class Parser : public Observer
{
public:
	Parser(std::ostream& output);
	~Parser() = default;

	void Analysis(std::vector<std::string>&, std::ostream&,
		std::chrono::system_clock::time_point);	

	void Update(const std::vector<std::string>& commands,
		std::chrono::system_clock::time_point bulk_time) override;

private:
	void RunCommands(std::ostream&, std::chrono::system_clock::time_point);
	void SaveLogs(std::chrono::system_clock::time_point);
	void PrintCommands(std::ostream&);
	
	size_t  start_dynamic_counter_;
	size_t  end_dynamic_counter_;
	const std::string start_dynamic_symbol_;
	const std::string end_dynamic_symbol_;
	std::vector<std::string> commands_;

	std::ostream& output_;
};
