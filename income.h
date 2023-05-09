#ifndef INCOME_H
#define INCOME_H

#include "finance.h"

// Dichiarazione della classe Income, che estende la classe Finance
class Income : public Finance {
public:
    // Costruttore
    Income(const QString &description, double amount, const QDate &date);

    // Metodo per ottenere il tipo di transazione finanziaria (implementazione del metodo virtuale puro)
    QString getType() const override;
};

#endif // INCOME_H
