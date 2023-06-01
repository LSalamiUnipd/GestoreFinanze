#ifndef ACCOUNTCONTAINER_H
#define ACCOUNTCONTAINER_H

#include <string>
#include <stdexcept>
#include "account.h"
#include "finance.h"

class AccountContainer {
public:
    // Costruttore
    AccountContainer();

    // Metodi per aggiungere, ottenere, rimuovere e cercare account
    void addAccount(const Account &account);
    Account getAccount(int index) const;
    void removeAccount(int index);
    int findAccount(const std::string &name) const;
    void addTransactionToAccount(int index, const Finance &transaction);
    ~AccountContainer();

private:
    struct AccountNode {
        Account account;
        struct FinanceNode {
            Finance* transaction;
            FinanceNode* next;

            // Aggiungi questo costruttore
            FinanceNode() : transaction(nullptr), next(nullptr) {}
        } *transactionsHead;
        AccountNode* next;

        // Aggiungi questo costruttore
        AccountNode() : transactionsHead(nullptr), next(nullptr) {}
    };
    AccountNode* head;

};

#endif // ACCOUNTCONTAINER_H
