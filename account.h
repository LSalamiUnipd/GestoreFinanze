#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QVector>
#include "expense.h"
#include "income.h"

class Account {
public:
    // Costruttore
    explicit Account(const QString &name);

    // Getter e setter per il nome dell'account
    QString getName() const;
    void setName(const QString &name);

    // Metodi per aggiungere, ottenere e rimuovere spese
    void addExpense(const Expense &expense);
    QVector<Expense> getExpenses() const;
    void removeExpense(int index);

    // Metodi per aggiungere, ottenere e rimuovere entrate
    void addIncome(const Income &income);
    QVector<Income> getIncomes() const;
    void removeIncome(int index);

private:
    QString name;
    QVector<Expense> expenses;
    QVector<Income> incomes;
};

#endif // ACCOUNT_H
