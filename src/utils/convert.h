//
// Created by Da on 9/6/25.
//

#ifndef CONVERT_H
#define CONVERT_H

#include <sstream>
#include <iostream>

namespace utils {
    class Convert {
    public:
        template<typename T>
        static T convertStringToNumber(const std::string &str, T defaultValue = T{}) {
            if (str.empty() || str == "null") {
                return defaultValue;
            }

            try {
                if constexpr (std::is_same_v<T, int>) {
                    return std::stoi(str);
                } else if constexpr (std::is_same_v<T, double>) {
                    return std::stod(str);
                } else if constexpr (std::is_same_v<T, float>) {
                    return std::stof(str);
                }
            } catch (const std::exception &e) {
                std::cerr << "Error converting '" << str << "': " << e.what() << std::endl;
                return defaultValue;
            }

            return defaultValue;
        }
    };
}

#endif //CONVERT_H
