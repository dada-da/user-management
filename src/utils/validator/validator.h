//
// Created by Da on 5/6/25.
//

#ifndef VALIDATOR_H
#define VALIDATOR_H

namespace input {
    class Validator final {
        struct UsernameRules {
            size_t minLength = 3;
            size_t maxLength = 20;
            bool allowNumbers = true;
            bool allowUnderscore = true;
            bool allowDash = false;
            bool requireAlphaStart = true;
        };

        struct NameRules {
            static constexpr size_t minLength = 2;
            static constexpr size_t maxLength = 50;
            static constexpr bool allowMultipleSpaces = false;
            static constexpr bool allowLeadingTrailingSpaces = false;
        };

        static std::string trimSpace(const std::string &str);

        static bool isValidUserName(const std::string &username);

        static bool isValidName(const std::string &name);


    public:
        static std::string getValidUserName(const std::string &label= "Enter username: ");

        static std::string getPassword(const std::string& label = "Enter password: ");

        static std::string getValidName(const std::string &label = "Enter your name: ");

        static long long getAmountInput(long long maxAmount);
    };
}


#endif //VALIDATOR_H
