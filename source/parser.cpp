#include "parser.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>

Parser::Parser()
    :start_dynamic_counter_{0}, end_dynamic_counter_{0}, 
    start_dynamic_symbol_{"{"}, end_dynamic_symbol_{"}"},
    commands_{}
{
}

void Parser::Analysis(std::vector<std::string>& strings, std::ostream& output,
    std::chrono::system_clock::time_point bulk_time)
{    

    for (auto& string : strings)
    {        
        if (string == start_dynamic_symbol_)
        {  
            RunCommands(output, bulk_time);
            ++start_dynamic_counter_;            
            continue;
        }

        if (string == end_dynamic_symbol_)
        {            
            if (start_dynamic_counter_ == 0) { continue; }

            if (++end_dynamic_counter_ == start_dynamic_counter_)
            {
                start_dynamic_counter_ = 0;
                end_dynamic_counter_ = 0;
                RunCommands(output, bulk_time);               
            }

            continue;
        }     

        commands_.push_back(std::move(string));
    }

    RunCommands(output, bulk_time);
}

void Parser::RunCommands(std::ostream& output,
    std::chrono::system_clock::time_point bulk_time)
{
    if (commands_.empty() || start_dynamic_counter_ > 0) { return; }

    PrintCommands(output);

    SaveLogs(bulk_time);

    commands_.clear();
}

void Parser::SaveLogs(std::chrono::system_clock::time_point bulk_time)
{
    std::time_t time = std::chrono::system_clock::to_time_t(bulk_time);
    std::string timestamp_str = std::to_string(time);    
    std::string dir_path = "./logs/";

    std::filesystem::create_directories(dir_path);

    std::ofstream out_file(std::string{dir_path + "bulk" + timestamp_str + ".log"});

    if (!out_file.is_open())
    {   
        throw std::ios_base::failure("Log-file is not opened/created");
    }
    
    PrintCommands(out_file);

    out_file.close();
}

void Parser::PrintCommands(std::ostream& output)
{
    output << "\n\tbulk: ";

    for (auto it = commands_.cbegin(); it != (--commands_.cend()); it++)
    {
        output << *it << ", ";
    }

    output << commands_.back() << std::endl;
}
