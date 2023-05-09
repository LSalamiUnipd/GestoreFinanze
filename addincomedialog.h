#ifndef ADDINCOMEDIALOG_H
#define ADDINCOMEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>

// Dichiarazione della classe AddIncomeDialog
class AddIncomeDialog : public QDialog {
    Q_OBJECT

public:
    // Costruttore
    explicit AddIncomeDialog(QWidget *parent = nullptr);

    // Metodo per ottenere la descrizione dell'entrata
    QString getIncomeDescription() const;

    // Metodo per ottenere l'importo dell'entrata
    double getIncomeAmount() const;

    // Metodo per ottenere la data dell'entrata
    QDate getIncomeDate() const;

private:
    QLineEdit *descriptionEdit;     // Campo di input per la descrizione dell'entrata
    QDoubleSpinBox *amountEdit;     // Campo di input per l'importo dell'entrata
    QDateEdit *dateEdit;            // Campo di input per la data dell'entrata
    QDialogButtonBox *buttonBox;    // Pulsanti di conferma e annullamento
};

#endif // ADDINCOMEDIALOG_H
