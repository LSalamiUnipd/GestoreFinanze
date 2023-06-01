#include "accountcontainer.h"
#include "expense.h"
#include "income.h"
#include "loan.h"

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

int AccountContainer::findAccount(const std::string &name) const {
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
        AccountNode* next = head->next;
        delete head;
        head = next;
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
