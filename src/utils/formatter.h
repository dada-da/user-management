//
// Created by Da on 9/6/25.
//

#ifndef FORMATTER_H
#define FORMATTER_H

#include <string>

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
};

#endif //FORMATTER_H
