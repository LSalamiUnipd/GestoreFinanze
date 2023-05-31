#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QVector>
#include "expense.h"
#include "income.h"

class Account {
public:
    Account(const QString &name, const QString &description = QString()); // Aggiunto parametro description con un valore predefinito

    QString getName() const;
    void setName(const QString &newName);

    QString getDescription() const; // Getter per la descrizione
    void setDescription(const QString &newDescription); // Setter per la descrizione

    void addExpense(const Expense &expense);
    QVector<Expense> getExpenses() const;
    void removeExpense(int index);

    void addIncome(const Income &income);
    QVector<Income> getIncomes() const;
    void removeIncome(int index);

private:
    QString name;
    QString description; // Nuovo membro dati per la descrizione
    QVector<Expense> expenses;
    QVector<Income> incomes;
};

#endif // ACCOUNT_H
