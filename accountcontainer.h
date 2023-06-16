#ifndef ACCOUNTCONTAINER_H
#define ACCOUNTCONTAINER_H

#include <QString>
#include <stdexcept>
#include "account.h"
#include "finance.h"

class AccountContainer {
public:
    AccountContainer(); // Costruttore

    // Metodi per gestire gli account
    void addAccount(const Account &account); // Aggiungi un account
    Account getAccount(int index) const; // Ottieni un account
    void setAccount(int index, const Account& account); // Modifica un account
    void removeAccount(int index); // Rimuovi un account
    int findAccount(const QString &name) const; // Trova un account

    // Metodi per gestire le transazioni
    void addTransactionToAccount(int index, const Finance &transaction); // Aggiungi una transazione a un account
    void removeTransactionFromAccount(int accountIndex, int transactionIndex); // Rimuovi una transazione da un account
    QList<Finance*> getTransactions(int accountIndex) const; // Ottieni tutte le transazioni di un account
    Finance* getTransactionFromAccount(int accountIndex, int transactionIndex); // Ottieni una specifica transazione da un account
    void setTransactionInAccount(int accountIndex, int transactionIndex, const Finance& transaction); // Modifica una transazione in un account

    QList<Account> getAccounts() const; // Ottieni tutti gli account

    ~AccountContainer(); // Distruttore

private:
    struct AccountNode { // Nodo di una lista collegata di account
        Account account; // Dati dell'account
        struct FinanceNode { // Nodo di una lista collegata di transazioni
            Finance* transaction; // Dati della transazione
            FinanceNode* next; // Puntatore al prossimo nodo

            FinanceNode() : transaction(nullptr), next(nullptr) {} // Costruttore
        } *transactionsHead; // Testa della lista di transazioni
        AccountNode* next; // Puntatore al prossimo nodo

        AccountNode() : transactionsHead(nullptr), next(nullptr) {} // Costruttore
    };
    AccountNode* head; // Testa della lista di account

};

#endif // ACCOUNTCONTAINER_H
