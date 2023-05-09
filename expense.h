#ifndef EXPENSE_H
#define EXPENSE_H

#include "finance.h"

// Dichiarazione della classe Expense, che estende la classe Finance
class Expense : public Finance {
public:
    // Costruttore
    Expense(const QString &description, double amount, const QDate &date);

    // Metodo per ottenere il tipo di transazione finanziaria (implementazione del metodo virtuale puro)
    QString getType() const override;
};

#endif // EXPENSE_H
