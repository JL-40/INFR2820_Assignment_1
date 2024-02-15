//
// Created by Jeffry - 100698915 on 2024-02-14.
//

#include <chrono>
#include "CommonIncludes.h"

class Timer {
public:
    void DisplayTime(std::chrono::microseconds &time) {
        auto hours = std::chrono::duration_cast<std::chrono::hours>(time);
        time -= hours;

        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(time);
        time -= minutes;

        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time);
        time -= seconds;

        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time);
        time -= milliseconds;

        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time);

        std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count() << "." << milliseconds.count() << "." << microseconds.count();
    }
};


