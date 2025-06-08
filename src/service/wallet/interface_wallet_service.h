//
// Created by Da on 8/6/25.
//

#ifndef INTERFACE_WALLET_SERVICE_H
#define INTERFACE_WALLET_SERVICE_H

#include <string>

class IWalletService {
public:
    virtual ~IWalletService() = default;

    virtual bool transfer(const std::string &receivedUsername, long long value) = 0;

    virtual void displayWalletDashboard() = 0;

    virtual long long getBalance() = 0;

    virtual std::string getFormattedBalance() = 0;
};

#endif //INTERFACE_WALLET_SERVICE_H
