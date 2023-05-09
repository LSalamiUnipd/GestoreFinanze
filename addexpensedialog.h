#ifndef ADDEXPENSEDIALOG_H
#define ADDEXPENSEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>

// Dichiarazione della classe AddExpenseDialog
class AddExpenseDialog : public QDialog {
    Q_OBJECT

public:
    // Costruttore
    explicit AddExpenseDialog(QWidget *parent = nullptr);

    // Metodo per ottenere la descrizione della spesa
    QString getExpenseDescription() const;

    // Metodo per ottenere l'importo della spesa
    double getExpenseAmount() const;

    // Metodo per ottenere la data della spesa
    QDate getExpenseDate() const;

private:
    QLineEdit *descriptionEdit;     // Campo di input per la descrizione della spesa
    QDoubleSpinBox *amountEdit;     // Campo di input per l'importo della spesa
    QDateEdit *dateEdit;            // Campo di input per la data della spesa
    QDialogButtonBox *buttonBox;    // Pulsanti di conferma e annullamento
};

#endif // ADDEXPENSEDIALOG_H
