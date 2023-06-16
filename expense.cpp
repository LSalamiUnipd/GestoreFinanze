#include "expense.h"

// Implementazione del costruttore della classe Expense
Expense::Expense(const QString &description, double amount, const QDate &date)
    : Finance(description, amount, date) {
}

// Implementazione del metodo getType() per la classe Expense
QString Expense::getType() const {
    return "Expense";
}
