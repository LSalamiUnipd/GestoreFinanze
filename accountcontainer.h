#ifndef ACCOUNTCONTAINER_H
#define ACCOUNTCONTAINER_H

#include <QList>
#include "account.h"

class AccountContainer {
public:
    // Costruttore
    AccountContainer();

    // Metodi per aggiungere, ottenere, rimuovere e cercare account
    void addAccount(const Account &account);
    QList<Account> getAccounts() const;
    void removeAccount(int index);
    int findAccount(const QString &name) const;
    void addExpenseToAccount(int index, const Expense &expense);
    void addIncomeToAccount(int index, const Income &income);
    const Account& getAccount(int index) const;
    Account& getAccount(int index);

private:
    QList<Account> accounts;
};

#endif // ACCOUNTCONTAINER_H
