#ifndef USER_TABLE_H
#define USER_TABLE_H

#include <array>

namespace user_table {
    inline constexpr auto TABLE_NAME = "users";

    namespace columns {
        inline constexpr auto *USERNAME = "username";
        inline constexpr auto *NAME = "name";
        inline constexpr auto *DATE_OF_BIRTH = "date_of_birth";
        inline constexpr auto *PHONE_NUMBER = "phone_number";
        inline constexpr auto *EMAIL = "email";
        inline constexpr auto *PASSWORD_HASH = "password_hash";
        inline constexpr auto *OTP_ID = "otp_id";
        inline constexpr auto *ROLE = "role";
        inline constexpr auto *ACTIVE = "active";
        inline constexpr auto *CREATED_AT = "created_at";
        inline constexpr auto *UPDATED_AT = "updated_at";
    }

    namespace roles {
        inline constexpr auto *ADMIN = "admin";
        inline constexpr auto *USER = "user";

        inline constexpr std::array ALL = {ADMIN, USER};
    }

    namespace constraints {
        inline constexpr int MAX_USERNAME_LENGTH = 16;
        inline constexpr int MAX_NAME_LENGTH = 50;
        inline constexpr int MAX_PHONE_LENGTH = 11;
        inline constexpr int MAX_EMAIL_LENGTH = 80;
        inline constexpr int MAX_PASSWORD_LENGTH = 255;
        inline constexpr int MAX_OTP_LENGTH = 16;
    }
}

#endif //USER_TABLE_H
