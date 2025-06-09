//
// Created by Da on 9/6/25.
//

#include <string>
#include <fstream>
#include <sstream>
#include "../../utils/date_time.h"
#include  "../../model/transaction_log.h"
#include "transaction_data.h"

namespace data {
    const std::string TransactionData::TRANSACTION_LOG_DATA_FILE_PATH = "../database/transaction_log.csv";
    long long TransactionData::lastTransactionId = 0;

    void TransactionData::saveToFile() {
        std::ofstream file(TRANSACTION_LOG_DATA_FILE_PATH);

        if (!file.is_open()) {
            throw std::runtime_error("Error opening file for writing");
        }

        file << "id,username,balance\n";

        for (int i = 0; i < data.getSize(); i++) {
            std::optional<TransactionLog> transaction = data.getDataAt(i);

            if (!transaction.has_value()) continue;

            file << transaction->getId() << ","
                    << transaction->getSenderUsername() << ","
                    << transaction->getReceiverUsername() << ","
                    << transaction->getAmount() << ","
                    << transaction->getStatus() << ","
                    << transaction->getCreatedAt() << "\n";
        }
    }

    void TransactionData::loadFromFile(const std::string &username) {
        std::ifstream file(TRANSACTION_LOG_DATA_FILE_PATH);

        if (!file.is_open()) {
            throw std::runtime_error("Could not open file " + TRANSACTION_LOG_DATA_FILE_PATH);
        }

        std::string line;
        bool isFirstLine = true;

        while (std::getline(file, line)) {
            if (isFirstLine) {
                isFirstLine = false;
                continue;
            }

            std::optional<TransactionLog> transaction = parseLine(line, username);

            if (transaction.has_value()) {
                data.insert(*transaction);
            }
        }

        file.close();
    }

    List<TransactionLog> TransactionData::getAll() {
        return data;
    }

    bool TransactionData::create(const std::string &senderUsername, const std::string &receiverUsername,
                                 long long amount) {
        const std::string currentDateTime = utils::DateTime::getCurrentTimestamp();
        auto transaction = TransactionLog(getNewTransactionId(), senderUsername, receiverUsername, amount);
        transaction.setCreatedAt(currentDateTime);

        std::ifstream checkFile(TRANSACTION_LOG_DATA_FILE_PATH);
        bool fileExists = checkFile.good();
        checkFile.close();

        std::ofstream file(TRANSACTION_LOG_DATA_FILE_PATH, std::ios::app);

        if (!file.is_open()) {
            throw std::runtime_error("Error opening file for writing");
        }

        if (!fileExists) {
            file << "id,sender_username,receiver_username,amount,status,created_at\n";
        }

        file << transaction.getId() << ","
                << transaction.getSenderUsername() << ","
                << transaction.getReceiverUsername() << ","
                << transaction.getAmount() << ","
                << transaction.getStatus() << ","
                << transaction.getCreatedAt() << "\n";

        file.close();

        data.insert(transaction);

        return true;
    }
}
