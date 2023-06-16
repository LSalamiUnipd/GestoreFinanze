#ifndef ADDLOANDIALOG_H
#define ADDLOANDIALOG_H

#include <QDialog>
#include <QString>
#include <QDate>

class QLineEdit;
class QDoubleSpinBox;
class QDateEdit;
class QSpinBox;
class QCheckBox;

// Classe AddLoanDialog per aggiungere un nuovo prestito tramite un dialog
class AddLoanDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddLoanDialog(QWidget *parent = nullptr); // Costruttore
    ~AddLoanDialog(); // Distruttore

    QString getLoanDescription() const; // Ottiene la descrizione del prestito
    double getLoanAmount() const; // Ottiene l'importo del prestito
    QDate getLoanDate() const; // Ottiene la data del prestito
    int getLoanDuration() const; // Ottiene la durata del prestito
    double getLoanInterestRate() const; // Ottiene il tasso di interesse del prestito
    bool isLoanPaid() const; // Verifica se il prestito è stato pagato

private:
    QLineEdit* descriptionLineEdit; // Campo per inserire la descrizione del prestito
    QDoubleSpinBox* amountSpinBox; // Campo per inserire l'importo del prestito
    QDateEdit* dateEdit; // Campo per inserire la data del prestito
    QSpinBox* durationSpinBox; // Campo per inserire la durata del prestito
    QDoubleSpinBox* interestRateSpinBox; // Campo per inserire il tasso di interesse del prestito
    QCheckBox* paidCheckBox; // Casella di controllo per indicare se il prestito è stato pagato
};

#endif // ADDLOANDIALOG_H
