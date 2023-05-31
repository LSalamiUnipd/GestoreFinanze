#include "finance.h"

// Costruttore della classe Finance
Finance::Finance(const QString &description, double amount, const QDate &date)
    : description(description), amount(amount), date(date) {
}

// Distruttore virtuale della classe Finance
Finance::~Finance() {
}

// Metodo getter per la descrizione
QString Finance::getDescription() const {
    return description;
}

// Metodo getter per l'importo
double Finance::getAmount() const {
    return amount;
}

// Metodo getter per la data
QDate Finance::getDate() const {
    return date;
}

// Metodo setter per la descrizione
void Finance::setDescription(const QString &description) {
    this->description = description;
}

// Metodo setter per l'importo
void Finance::setAmount(double amount) {
    this->amount = amount;
}

// Metodo setter per la data
void Finance::setDate(const QDate &date) {
    this->date = date;
}

// Il metodo getType() è un metodo virtuale puro e deve essere implementato nelle classi derivate
