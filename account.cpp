#include "account.h"

// Costruttore della classe Account
Account::Account(const QString &name, const QString &description)
    : name(name), description(description) {
}

// Getter e setter per il nome dell'account
QString Account::getName() const {
    return name;
}

void Account::setName(const QString &newName) {
    name = newName;
}

// Getter e setter per la descrizione dell'account
QString Account::getDescription() const {
    return description;
}

void Account::setDescription(const QString &newDescription) {
    description = newDescription;
}

// Metodo per aggiungere una spesa all'account
void Account::addExpense(const Expense &expense) {
    expenses.append(expense);
}

// Metodo per ottenere tutte le spese dell'account
QVector<Expense> Account::getExpenses() const {
    return expenses;
}

// Metodo per rimuovere una spesa dall'account
void Account::removeExpense(int index) {
    if (index >= 0 && index < expenses.size()) {
        expenses.remove(index);
    }
}

// Metodo per aggiungere un'entrata all'account
void Account::addIncome(const Income &income) {
    incomes.append(income);
}

// Metodo per ottenere tutte le entrate dell'account
QVector<Income> Account::getIncomes() const {
    return incomes;
}

// Metodo per rimuovere un'entrata dall'account
void Account::removeIncome(int index) {
    if (index >= 0 && index < incomes.size()) {
        incomes.remove(index);
    }
}

// Aggiunge un prestito all'account
void Account::addLoan(const Loan &loan) {
    loans.append(loan);
}

// Restituisce tutti i prestiti per l'account
QVector<Loan> Account::getLoans() const {
    return loans;
}

// Rimuove un prestito dall'account
void Account::removeLoan(int index) {
    if (index >= 0 && index < loans.size()) {
        loans.remove(index);
    } else {
        throw std::out_of_range("Index is out of range");
    }
}
