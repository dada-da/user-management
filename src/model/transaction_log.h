//
// Created by Da on 9/6/25.
//

#ifndef TRANSACTION_LOG_H
#define TRANSACTION_LOG_H

#include <string>

namespace data {
    class TransactionLog {
        long long id;
        std::string senderUsername;
        std::string receiverUsername;
        std::string status;
        long long amount;
        std::string createdAt;

    public:
        TransactionLog() = default;

        TransactionLog(const long long id, const std::string &senderUsername, const std::string &receiverUsername,
                       const long long amount) : id(id), senderUsername(senderUsername),
                                                 receiverUsername(receiverUsername),
                                                 amount(amount) {
        }

        void setId(const long long id) {
            this->id = id;
        }

        void setSenderUsername(const std::string &senderUsername) {
            this->senderUsername = senderUsername;
        }

        void setReceiverUsername(const std::string &receiverUsername) {
            this->receiverUsername = receiverUsername;
        }

        void setStatus(const std::string &status) {
            this->status = status;
        }

        void setAmount(const long long amount) {
            this->amount = amount;
        }

        void setCreatedAt(const std::string &createdAt) {
            this->createdAt = createdAt;
        }

        long long getId() const {
            return id;
        }

        std::string getSenderUsername() {
            return senderUsername;
        }

        std::string getReceiverUsername() {
            return receiverUsername;
        }

        std::string getStatus() {
            return status;
        }

        long long getAmount() const {
            return amount;
        }

        std::string getCreatedAt() const {
            return createdAt;
        }
    };
}

#endif //TRANSACTION_LOG_H
