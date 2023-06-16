#include "accountcontainer.h"
#include "expense.h"
#include "income.h"
#include "loan.h"
#include <QList>

AccountContainer::AccountContainer() : head(nullptr) {} // Costruttore, inizializza la testa della lista a nullptr

void AccountContainer::addAccount(const Account &account) {
    AccountNode* newNode = new AccountNode; // Crea un nuovo nodo
    newNode->account = account; // Imposta l'account del nuovo nodo
    newNode->next = head; // Collega il nuovo nodo alla lista esistente
    head = newNode; // Imposta il nuovo nodo come testa della lista
}

Account AccountContainer::getAccount(int index) const {
    AccountNode* current = head; // Inizia dalla testa della lista
    int count = 0;
    while (current != nullptr) { // Esegui il ciclo finché non raggiungi la fine della lista
        if (count == index) { // Se l'indice corrente corrisponde all'indice richiesto
            return current->account; // Restituisci l'account corrente
        }
        current = current->next; // Passa all'account successivo
        count++;
    }
    throw std::out_of_range("Index out of range"); // Lancio un'eccezione se l'indice è fuori dal range
}

// (Ripete la stessa logica per gli altri metodi: setAccount, removeAccount, findAccount, etc.)

void AccountContainer::setAccount(int index, const Account& account) {
    AccountNode* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == index) {
            current->account = account;
            return;
        }
        current = current->next;
        count++;
    }
    throw std::out_of_range("Index out of range");
}

void AccountContainer::removeAccount(int index) {
    if (head == nullptr) {
        throw std::out_of_range("Cannot remove from empty list");
    }

    if (index == 0) {
        AccountNode* toDelete = head;
        head = head->next;
        delete toDelete;
        return;
    }

    AccountNode* current = head;
    int count = 0;
    while (current->next != nullptr && count < index - 1) {
        current = current->next;
        count++;
    }

    if (current->next == nullptr || count != index - 1) {
        throw std::out_of_range("Index out of range");
    }

    AccountNode* toDelete = current->next;
    current->next = toDelete->next;
    delete toDelete;
}

int AccountContainer::findAccount(const QString &name) const {
    AccountNode* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->account.getName() == name) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

// Distruttore: dealloca la memoria per ogni account e ogni transazione
AccountContainer::~AccountContainer() {
    while (head != nullptr) { // Mentre la lista degli account non è vuota
        AccountNode* nextAccount = head->next; // Memorizza il prossimo account

        AccountNode::FinanceNode* currentTransaction = head->transactionsHead; // Ottieni la lista delle transazioni per l'account corrente
        while (currentTransaction != nullptr) { // Mentre la lista delle transazioni non è vuota
            AccountNode::FinanceNode* nextTransaction = currentTransaction->next; // Memorizza la prossima transazione
            delete currentTransaction->transaction; // Dealloca la memoria per la transazione corrente
            delete currentTransaction; // Dealloca la memoria per il nodo della transazione corrente
            currentTransaction = nextTransaction; // Passa alla prossima transazione
        }

        delete head; // Dealloca la memoria per l'account corrente
        head = nextAccount; // Passa al prossimo account
    }
}

// (Ripete la stessa logica per i metodi che gestiscono le transazioni)

void AccountContainer::addTransactionToAccount(int index, const Finance &transaction) {
    AccountNode* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == index) {
            AccountNode::FinanceNode* newTransaction = new AccountNode::FinanceNode;
            if (dynamic_cast<const Expense*>(&transaction)) {
                newTransaction->transaction = new Expense(static_cast<const Expense&>(transaction));
            } else if (dynamic_cast<const Income*>(&transaction)) {
                newTransaction->transaction = new Income(static_cast<const Income&>(transaction));
            } else if (dynamic_cast<const Loan*>(&transaction)) {
                newTransaction->transaction = new Loan(static_cast<const Loan&>(transaction));
            }
            newTransaction->next = current->transactionsHead;
            current->transactionsHead = newTransaction;
            return;
        }
        current = current->next;
        count++;
    }
    throw std::out_of_range("Index out of range");
}

void AccountContainer::removeTransactionFromAccount(int accountIndex, int transactionIndex) {
    AccountNode* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == accountIndex) {
            AccountNode::FinanceNode* transactionCurrent = current->transactionsHead;
            AccountNode::FinanceNode* transactionPrev = nullptr;
            int transactionCount = 0;
            while (transactionCurrent != nullptr) {
                if (transactionCount == transactionIndex) {
                    if (transactionPrev == nullptr) {
                        current->transactionsHead = transactionCurrent->next;
                    } else {
                        transactionPrev->next = transactionCurrent->next;
                    }
                    delete transactionCurrent->transaction;
                    delete transactionCurrent;
                    return;
                }
                transactionPrev = transactionCurrent;
                transactionCurrent = transactionCurrent->next;
                transactionCount++;
            }
            throw std::out_of_range("Transaction index out of range");
        }
        current = current->next;
        count++;
    }
    throw std::out_of_range("Account index out of range");
}

QList<Finance*> AccountContainer::getTransactions(int accountIndex) const {
    AccountNode* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == accountIndex) {
            QList<Finance*> transactions;
            AccountNode::FinanceNode* transactionCurrent = current->transactionsHead;
            while (transactionCurrent != nullptr) {
                transactions.append(transactionCurrent->transaction);
                transactionCurrent = transactionCurrent->next;
            }
            return transactions;
        }
        current = current->next;
        count++;
    }
    throw std::out_of_range("Account index out of range");
}

QList<Account> AccountContainer::getAccounts() const {
    QList<Account> accounts;
    AccountNode* current = head;
    while (current != nullptr) {
        accounts.append(current->account);
        current = current->next;
    }
    return accounts;
}

Finance* AccountContainer::getTransactionFromAccount(int accountIndex, int transactionIndex) {
    AccountNode* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == accountIndex) {
            AccountNode::FinanceNode* transactionCurrent = current->transactionsHead;
            int transactionCount = 0;
            while (transactionCurrent != nullptr) {
                if (transactionCount == transactionIndex) {
                    return transactionCurrent->transaction;
                }
                transactionCurrent = transactionCurrent->next;
                transactionCount++;
            }
            throw std::out_of_range("Transaction index out of range");
        }
        current = current->next;
        count++;
    }
    throw std::out_of_range("Account index out of range");
}

void AccountContainer::setTransactionInAccount(int accountIndex, int transactionIndex, const Finance& transaction) {
    AccountNode* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == accountIndex) {
            AccountNode::FinanceNode* transactionCurrent = current->transactionsHead;
            int transactionCount = 0;
            while (transactionCurrent != nullptr) {
                if (transactionCount == transactionIndex) {
                    delete transactionCurrent->transaction;
                    if (dynamic_cast<const Expense*>(&transaction)) {
                        transactionCurrent->transaction = new Expense(static_cast<const Expense&>(transaction));
                    } else if (dynamic_cast<const Income*>(&transaction)) {
                        transactionCurrent->transaction = new Income(static_cast<const Income&>(transaction));
                    } else if (dynamic_cast<const Loan*>(&transaction)) {
                        transactionCurrent->transaction = new Loan(static_cast<const Loan&>(transaction));
                    }
                    return;
                }
                transactionCurrent = transactionCurrent->next;
                transactionCount++;
            }
            throw std::out_of_range("Transaction index out of range");
        }
        current = current->next;
        count++;
    }
    throw std::out_of_range("Account index out of range");
}
