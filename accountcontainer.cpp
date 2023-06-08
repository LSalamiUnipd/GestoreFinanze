#include "accountcontainer.h"
#include "expense.h"
#include "income.h"
#include "loan.h"
#include <QList>

AccountContainer::AccountContainer() : head(nullptr) {}

void AccountContainer::addAccount(const Account &account) {
    AccountNode* newNode = new AccountNode;
    newNode->account = account;
    newNode->next = head;
    head = newNode;
}

Account AccountContainer::getAccount(int index) const {
    AccountNode* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == index) {
            return current->account;
        }
        current = current->next;
        count++;
    }
    throw std::out_of_range("Index out of range");
}

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

AccountContainer::~AccountContainer() {
    while (head != nullptr) {
        AccountNode* nextAccount = head->next;

        AccountNode::FinanceNode* currentTransaction = head->transactionsHead;
        while (currentTransaction != nullptr) {
            AccountNode::FinanceNode* nextTransaction = currentTransaction->next;
            delete currentTransaction->transaction;
            delete currentTransaction;
            currentTransaction = nextTransaction;
        }

        delete head;
        head = nextAccount;
    }
}



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
