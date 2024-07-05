#include "cmd_reader.h"


CommandReader::CommandReader(size_t N)
    :max_command_number_{N}, command_counter_{0}, container_{}, 
    bulk_time_{}, eof_flag_{false}
{
    container_.resize(max_command_number_);
}


void CommandReader::Read(std::istream& input)
{   
    ClearState();  

    while (command_counter_ < max_command_number_)
    {
        std::string command{};
        std::getline(input, command);

        if (input.eof())
        {  
            eof_flag_ = true;
            break;
        }

        if (command.empty()) { continue; }

        container_.push_back(std::move(command));

        ++command_counter_;
    }   

    PrintForCheck();
}

std::vector<std::string>& CommandReader::GetCommands()
{
    return container_;
}

bool CommandReader::IsEof() const
{
    return eof_flag_;
}

std::chrono::system_clock::time_point CommandReader::GetBulkTime() const
{
    return bulk_time_;
}

void CommandReader::ClearState()
{
    command_counter_ = 0;
    eof_flag_ = false;
    container_.clear();
    bulk_time_ = std::chrono::system_clock::now();
}

void CommandReader::PrintForCheck() const
{
    for (auto& i : container_)
    {   
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << i << std::endl;        
    }
}
