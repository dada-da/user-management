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

        static std::string trimSpace(const std::string &str);

        static bool isValidUserName(const std::string &username);

    public:
        static std::string getValidUserName();

        static std::string getPassword();
    };
}


#endif //VALIDATOR_H
