#ifndef ADDINCOMEDIALOG_H
#define ADDINCOMEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>

// Classe AddIncomeDialog per aggiungere un nuovo reddito tramite un dialog
class AddIncomeDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddIncomeDialog(QWidget *parent = nullptr); // Costruttore

    QString getIncomeDescription() const; // Ottiene la descrizione del reddito
    double getIncomeAmount() const; // Ottiene l'importo del reddito
    QDate getIncomeDate() const; // Ottiene la data del reddito

private:
    QLineEdit *descriptionEdit; // Campo per inserire la descrizione del reddito
    QDoubleSpinBox *amountEdit; // Campo per inserire l'importo del reddito
    QDateEdit *dateEdit; // Campo per inserire la data del reddito
    QDialogButtonBox *buttonBox; // Pulsanti di conferma e annullamento
};

#endif // ADDINCOMEDIALOG_H
