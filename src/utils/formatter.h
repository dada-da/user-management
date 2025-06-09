//
// Created by Da on 9/6/25.
//

#ifndef FORMATTER_H
#define FORMATTER_H

#include <string>

namespace utils {
    class Formatter {
    public:
        static std::string formatCurrency(const long long amount) {
            std::string str = std::to_string(amount);
            int insertPos = str.length() - 3;

            while (insertPos > 0) {
                str.insert(insertPos, ",");
                insertPos -= 3;
            }

            return str;
        }

        static std::string normalize(const std::string &value) {
            std::string result = value;
            std::transform(result.begin(), result.end(), result.begin(), ::tolower);
            return result;
        }

        static std::string capitalize(const std::string &value) {
            if (value.empty()) return value;

            std::string result = value;
            bool capitalizeNext = true;

            for (char &c: result) {
                if (std::isalpha(c)) {
                    if (capitalizeNext) {
                        c = std::toupper(c);
                        capitalizeNext = false;
                    } else {
                        c = std::tolower(c);
                    }
                } else if (c == ' ') {
                    capitalizeNext = true;
                }
            }

            return result;
        }

        static std::string normalizeSpaces(const std::string &value) {
            if (value.empty()) return value;

            std::istringstream iss(value);
            std::string word;
            std::string result;

            while (iss >> word) {
                if (!result.empty()) {
                    result += " ";
                }
                result += word;
            }

            return result;
        }

        static std::string formatForStorage(const std::string &value) {
            return normalize(value);
        }

        static std::string formatForDisplay(const std::string &value) {
            return capitalize(value);
        }
    };
}

#endif //FORMATTER_H
