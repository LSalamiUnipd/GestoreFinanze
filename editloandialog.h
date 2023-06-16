#ifndef EDITLOANDIALOG_H
#define EDITLOANDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QString>
#include <QDate>
#include <QFormLayout>
#include <QLabel>
#include <loan.h>

// Classe EditLoanDialog per la modifica di un oggetto Loan
class EditLoanDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditLoanDialog(Loan& loan, QWidget *parent = nullptr); // Costruttore

    // Getter per il Loan modificato e i suoi campi
    Loan getModifiedLoan() const;
    QString getLoanDescription() const;
    double getLoanAmount() const;
    QDate getLoanDate() const;
    int getLoanDuration() const;
    double getLoanInterestRate() const;
    bool isLoanPaid() const;

private slots:
    void accept() override; // Slot di accettazione del dialogo

private:
    // Riferimenti al Loan originale e a una copia modificabile dello stesso
    Loan& originalLoan;
    Loan modifiedLoan;

    // Widget di input
    QLineEdit* descriptionEdit;
    QDoubleSpinBox* amountEdit;
    QDateEdit* dateEdit;
    QSpinBox* durationSpinBox;
    QDoubleSpinBox* interestRateSpinBox;
    QCheckBox* paidCheckBox;
    QDialogButtonBox* buttonBox;
};

#endif // EDITLOANDIALOG_H
