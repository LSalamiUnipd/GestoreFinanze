#ifndef ADDEXPENSEDIALOG_H
#define ADDEXPENSEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>

// Classe AddExpenseDialog per aggiungere una nuova spesa tramite un dialog
class AddExpenseDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddExpenseDialog(QWidget *parent = nullptr); // Costruttore

    QString getExpenseDescription() const; // Ottiene la descrizione della spesa
    double getExpenseAmount() const; // Ottiene l'importo della spesa
    QDate getExpenseDate() const; // Ottiene la data della spesa

private:
    QLineEdit *descriptionEdit; // Campo per inserire la descrizione della spesa
    QDoubleSpinBox *amountEdit; // Campo per inserire l'importo della spesa
    QDateEdit *dateEdit; // Campo per inserire la data della spesa
    QDialogButtonBox *buttonBox; // Pulsanti di conferma e annullamento
};

#endif // ADDEXPENSEDIALOG_H
