#include "income.h"

// Costruttore della classe Income
Income::Income(const QString &description, double amount, const QDate &date)
    : Finance(description, amount, date) {
}

// Implementazione del metodo getType() per la classe Income
QString Income::getType() const {
    return "Income";
}
