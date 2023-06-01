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

class AddLoanDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddLoanDialog(QWidget *parent = nullptr);
    ~AddLoanDialog();

    QString getLoanDescription() const;
    double getLoanAmount() const;
    QDate getLoanDate() const;
    int getLoanDuration() const;
    double getLoanInterestRate() const;
    bool isLoanPaid() const;

private:
    QLineEdit* descriptionLineEdit;
    QDoubleSpinBox* amountSpinBox;
    QDateEdit* dateEdit;
    QSpinBox* durationSpinBox;
    QDoubleSpinBox* interestRateSpinBox;
    QCheckBox* paidCheckBox;
};

#endif // ADDLOANDIALOG_H
