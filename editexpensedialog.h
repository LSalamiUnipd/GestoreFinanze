#ifndef EDITEXPENSEDIALOG_H
#define EDITEXPENSEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include "expense.h"

// Classe EditExpenseDialog per modificare una spesa esistente
class EditExpenseDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditExpenseDialog(Expense& expense, QWidget *parent = nullptr); // Costruttore

    Expense getModifiedExpense() const; // Ottiene la spesa modificata
    QString getExpenseDescription() const; // Ottiene la descrizione della spesa
    double getExpenseAmount() const; // Ottiene l'importo della spesa
    QDate getExpenseDate() const; // Ottiene la data della spesa

private slots:
    void accept() override; // Slot che viene chiamato quando il pulsante OK viene premuto

private:
    Expense& originalExpense; // Riferimento alla spesa originale
    Expense modifiedExpense; // Copia modificabile della spesa originale

    QLineEdit *descriptionEdit; // Campo per inserire la descrizione della spesa
    QDoubleSpinBox *amountEdit; // Campo per inserire l'importo della spesa
    QDateEdit *dateEdit; // Campo per inserire la data della spesa
    QDialogButtonBox *buttonBox; // Pulsanti di conferma e annullamento
};

#endif // EDITEXPENSEDIALOG_H
