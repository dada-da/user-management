//
// Created by Da on 7/6/25.
//

#ifndef PRINT_DATA_H
#define PRINT_DATA_H

#include <iostream>
#include <iomanip>

class PrintData {
public:
    static constexpr int SECTION_WIDTH = 60;
    static constexpr int LABEL_WIDTH = 20;

    static std::string centerText(const std::string &text, const int width) {
        if (text.length() >= width) {
            return text;
        }

        const int padding = (width - text.length()) / 2;
        return std::string(padding, ' ') + text + std::string(width - padding - text.length(), ' ');
    }

    static void printBorder(const char borderChar) {
        std::cout << std::string(SECTION_WIDTH, borderChar) << std::endl;
    }

    static void printHeader(const std::string &title) {
        printBorder('=');
        std::cout << centerText(title, SECTION_WIDTH) << std::endl;
        printBorder('=');
    }

    static void printField(const std::string &label, const std::string &value) {
        std::cout << std::left << std::setw(LABEL_WIDTH) << label + ":" << " " << value << std::endl;
    }

    static void printField(const std::string &label, const int value) {
        std::cout << std::left << std::setw(LABEL_WIDTH) << label + ":" << " " << value << std::endl;
    }

    static void printField(const std::string &label, const long long value) {
        std::cout << std::left << std::setw(LABEL_WIDTH) << label + ":" << " " << value << std::endl;
    }

    static void printSectionHeader(const std::string &title) {
        std::cout << "\n " << title << " ";
        std::cout << std::string(65 - title.length(), '-') << "┐\n";
    }
};

#endif //PRINT_DATA_H
