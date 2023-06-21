#include "expense.h"

// Implementazione del costruttore della classe Expense
Expense::Expense(const QString &description, double amount, const QDate &date)
    : Finance(description, amount, date) {
}

// Implementazione del metodo getType() per la classe Expense
QString Expense::getType() const {
    return "Expense";
}

// Implementazione del metodo performOperation() per Expense
void Expense::performOperation() const{
    // Operazioni specifiche per una spesa
    // Esempio: Calcola l'IVA per la spesa
    double iva = getAmount() * 0.22;
    qDebug() << "L'IVA per la spesa di" << getDescription() << "è di" << iva;
}
