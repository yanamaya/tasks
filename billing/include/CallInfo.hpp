#ifndef CALLINFO_HPP
#define CALLINFO_HPP

#include <string>
#include <ctime>


struct CallInfo {
    std::string number;
    uint durationSeconds;
    time_t date; // month number
};

#endif // CALLINFO_HPP
