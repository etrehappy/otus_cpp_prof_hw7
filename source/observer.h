// observer.h
#pragma once
#include <vector>
#include <string>
#include <chrono>

// Интерфейс наблюдателя
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void Update(const std::vector<std::string>& commands,
        std::chrono::system_clock::time_point bulk_time) = 0;
};

// Интерфейс субъекта
class Subject
{
public:
    virtual ~Subject() = default;
    virtual void Attach(Observer* observer) = 0;
    virtual void Detach(Observer* observer) = 0;
    virtual void Notify() = 0;
};
