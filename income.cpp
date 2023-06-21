#include "income.h"

// Implementazione del costruttore della classe Income
Income::Income(const QString &description, double amount, const QDate &date)
    : Finance(description, amount, date) {
}

// Implementazione del metodo getType() per la classe Income
QString Income::getType() const {
    return "Income";
}

// Implementazione del metodo performOperation() per Income
void Income::performOperation() const{
    // Operazioni specifiche per un'entrata
    // Esempio: Calcola l'imposta sul reddito per l'entrata
    double irpef = getAmount() * 0.2;
    qDebug() << "L'imposta sul reddito per l'entrata di" << getDescription() << "è di" << irpef;
}
