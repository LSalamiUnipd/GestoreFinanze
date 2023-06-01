#ifndef ACCOUNTCONTAINER_H
#define ACCOUNTCONTAINER_H

#include <QString>
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
    void setAccount(int index, const Account& account);
    void removeAccount(int index);
    int findAccount(const QString &name) const;
    // Methods for adding, removing and retrieving transactions
    void addTransactionToAccount(int index, const Finance &transaction);
    void removeTransactionFromAccount(int accountIndex, int transactionIndex);
    QList<Finance*> getTransactions(int accountIndex) const;

    QList<Account> getAccounts() const;

    ~AccountContainer();

private:
    struct AccountNode {
        Account account;
        struct FinanceNode {
            Finance* transaction;
            FinanceNode* next;

            FinanceNode() : transaction(nullptr), next(nullptr) {}
        } *transactionsHead;
        AccountNode* next;

        AccountNode() : transactionsHead(nullptr), next(nullptr) {}
    };
    AccountNode* head;

};

#endif // ACCOUNTCONTAINER_H
