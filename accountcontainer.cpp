#include "accountcontainer.h"

// Costruttore della classe AccountContainer
AccountContainer::AccountContainer() {
}

// Metodo per aggiungere un account al contenitore
void AccountContainer::addAccount(const Account &account) {
    accounts.append(account);
}

// Metodo per ottenere tutti gli account nel contenitore
QList<Account> AccountContainer::getAccounts() const {
    return accounts;
}

// Metodo per ottenere un singolo account dato un indice
const Account& AccountContainer::getAccount(int index) const {
    if (index >= 0 && index < accounts.size()) {
        return accounts.at(index);
    } else {
        throw std::out_of_range("Index is out of range");
    }
}

Account& AccountContainer::getAccount(int index) {
    if (index >= 0 && index < accounts.size()) {
        return accounts[index];
    } else {
        throw std::out_of_range("Index is out of range");
    }
}


// Metodo per rimuovere un account dal contenitore dato l'indice
void AccountContainer::removeAccount(int index) {
    if (index >= 0 && index < accounts.size()) {
        accounts.removeAt(index);
    }
}

// Metodo per cercare un account nel contenitore in base al nome
int AccountContainer::findAccount(const QString &name) const {
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getName() == name) {
            return i;
        }
    }
    return -1; // Se non trovato, ritorna -1
}

void AccountContainer::addExpenseToAccount(int index, const Expense &expense) {
    accounts[index].addExpense(expense);
}

void AccountContainer::addIncomeToAccount(int index, const Income &income) {
    accounts[index].addIncome(income);
}

// Aggiunge un prestito a un account specificato dall'indice
void AccountContainer::addLoanToAccount(int index, const Loan &loan) {
    accounts[index].addLoan(loan);
}
