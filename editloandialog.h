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

class EditLoanDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditLoanDialog(Loan& loan, QWidget *parent = nullptr);

    Loan getModifiedLoan() const;
    QString getLoanDescription() const;
    double getLoanAmount() const;
    QDate getLoanDate() const;
    int getLoanDuration() const;
    double getLoanInterestRate() const;
    bool isLoanPaid() const;

private slots:
    void accept() override;

private:
    Loan& originalLoan;
    Loan modifiedLoan;

    QLineEdit* descriptionEdit;
    QDoubleSpinBox* amountEdit;
    QDateEdit* dateEdit;
    QSpinBox* durationSpinBox;
    QDoubleSpinBox* interestRateSpinBox;
    QCheckBox* paidCheckBox;
    QDialogButtonBox* buttonBox;
};

#endif // EDITLOANDIALOG_H
