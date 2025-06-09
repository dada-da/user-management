//
// Created by Da on 9/6/25.
//

#ifndef TRANSACTION_DATA_H
#define TRANSACTION_DATA_H

#include "interface_transaction_data.h"
#include "../../model/transaction_log.h"
#include "../../utils/list.h"
#include "../../utils/date_time.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <optional>

namespace data {
    class TransactionData final : public ITransactionData {
        List<TransactionLog> data;
        static long long lastTransactionId;
        static const std::string TRANSACTION_LOG_DATA_FILE_PATH;

        static std::string generateId(const std::string &username) {
            const std::string currentDateTime = utils::DateTime::getCurrentTimestamp();
            return currentDateTime + username;
        }

        static std::optional<TransactionLog> parseLine(const std::string &line, const std::string &username) {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            const std::string &sender = fields[1];
            const std::string &receiver = fields[2];

            if (lastTransactionId < std::stoll(fields[0])) {
                long long maxId = std::max(maxId, std::stoll(fields[0]));

                setLastTransactionId(maxId);
            }

            if (sender == username || receiver == username) {
                TransactionLog transactionLog = {};
                transactionLog.setId(std::stoll(fields[0]));
                transactionLog.setSenderUsername(sender);
                transactionLog.setReceiverUsername(receiver);
                transactionLog.setAmount(std::stoll(fields[3]));
                transactionLog.setStatus(fields[4]);
                transactionLog.setCreatedAt(fields[5]);

                return transactionLog;
            }

            return std::nullopt;
        }

    public:
        static long long getNewTransactionId() {
            return ++lastTransactionId;
        }

        static void setLastTransactionId(long long id) {
            lastTransactionId = id;
        }

        void saveToFile() override;

        void loadFromFile(const std::string &username) override;


        List<TransactionLog> getAll() override;

        bool create(const std::string &senderUsername, const std::string &receiverUsername,
                    long long amount) override;
    };
};


#endif //TRANSACTION_DATA_H
