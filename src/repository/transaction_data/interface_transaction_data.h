//
// Created by Da on 9/6/25.
//

#ifndef INTERFACE_TRANSACTION_DATA_H
#define INTERFACE_TRANSACTION_DATA_H

#include "../../model/transaction_log.h"
#include "../../utils/list.h"

namespace data {
    class ITransactionData {
    public:
        virtual ~ITransactionData() = default;

        virtual void saveToFile() = 0;

        virtual void loadFromFile(const std::string &username) = 0;

        virtual List<TransactionLog> getAll() = 0;

        virtual bool create(const std::string &senderUsername, const std::string &receiverUsername,
                            long long amount) = 0;
    };
}

#endif //INTERFACE_TRANSACTION_DATA_H
