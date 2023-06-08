#ifndef EDITINCOMEDIALOG_H
#define EDITINCOMEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <income.h>

class EditIncomeDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditIncomeDialog(Income& income, QWidget *parent = nullptr);

    Income getModifiedIncome() const;
    QString getIncomeDescription() const;
    double getIncomeAmount() const;
    QDate getIncomeDate() const;

private slots:
    void accept() override;

private:
    Income &originalIncome;
    Income modifiedIncome;

    QLineEdit* descriptionEdit;
    QDoubleSpinBox* amountEdit;
    QDateEdit* dateEdit;
    QDialogButtonBox* buttonBox;
};

#endif // EDITINCOMEDIALOG_H
