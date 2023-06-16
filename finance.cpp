#include "finance.h"

// Implementazione del costruttore della classe Finance
Finance::Finance(const QString &description, double amount, const QDate &date)
    : description(description), amount(amount), date(date) {
}

// Implementazione del distruttore virtuale della classe Finance
Finance::~Finance() {
}

// Implementazione dei getter per la descrizione, l'importo e la data
QString Finance::getDescription() const {
    return description;
}

double Finance::getAmount() const {
    return amount;
}

QDate Finance::getDate() const {
    return date;
}

// Implementazione dei setter per la descrizione, l'importo e la data
void Finance::setDescription(const QString &description) {
    this->description = description;
}

void Finance::setAmount(double amount) {
    this->amount = amount;
}

void Finance::setDate(const QDate &date) {
    this->date = date;
}

// Il metodo getType() deve essere implementato nelle classi derivate in quanto è un metodo virtuale puro



