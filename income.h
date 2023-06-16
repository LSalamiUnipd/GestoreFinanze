#ifndef INCOME_H
#define INCOME_H

#include "finance.h"

// Classe Income estende Finance
class Income : public Finance {
public:
    // Costruttore
    Income(const QString &description, double amount, const QDate &date);

    // Implementazione del metodo virtuale puro per ottenere il tipo di transazione finanziaria
    QString getType() const override;
};

#endif // INCOME_H
