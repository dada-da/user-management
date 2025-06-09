//
// Created by Da on 9/6/25.
//

#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <sstream>
#include <iomanip>

namespace utils {
    class DateTime {
        static std::string timeTToString(const std::time_t time) {
            return formatTimeT(time, "%Y-%m-%d %H:%M:%S");
        }

        static std::string formatTimeT(const std::time_t time, const std::string &format) {
            const std::tm *tm = std::localtime(&time);
            if (!tm) {
                return "Invalid time";
            }

            std::ostringstream oss;
            oss << std::put_time(tm, format.c_str());
            return oss.str();
        }

    public:
        static std::string getCurrentTimestamp() {
            const auto now = std::chrono::system_clock::now();
            const std::time_t time = std::chrono::system_clock::to_time_t(now);
            return timeTToString(time);
        }


        static std::string formatForDisplay(const std::time_t time, const std::string &format) {
            return formatTimeT(time, "%B %d, %Y at %I:%M %p");
        }
    };
}

#endif //DATE_TIME_H
