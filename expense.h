#ifndef EXPENSE_H
#define EXPENSE_H

#include "finance.h"

// Classe Expense estende Finance
class Expense : public Finance {
public:
    // Costruttore
    Expense(const QString &description, double amount, const QDate &date);

    // Implementazione del metodo virtuale puro per ottenere il tipo di transazione finanziaria
    QString getType() const override;
    // Metodo per eseguire operazioni specifiche per una transazione finanziaria
    void performOperation() const override;
};

#endif // EXPENSE_H
