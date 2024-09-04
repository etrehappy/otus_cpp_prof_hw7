#include "cmd_reader.h"
#include <algorithm> 

CommandReader::CommandReader(size_t N)
    :max_command_number_{N}, command_counter_{0}, container_{}, 
    bulk_time_{}, eof_flag_{false}, observers_{}
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

    Notify();
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

void CommandReader::Attach(Observer* observer)
{
    observers_.push_back(observer);
}

void CommandReader::Detach(Observer* observer)
{
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

void CommandReader::Notify()
{
    for (auto observer : observers_)
    {
        observer->Update(container_, bulk_time_);
    }
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
