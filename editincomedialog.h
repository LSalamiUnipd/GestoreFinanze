#ifndef EDITINCOMEDIALOG_H
#define EDITINCOMEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include "income.h" // Include your Income header file here

class EditIncomeDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditIncomeDialog(Income *incomeToEdit, QWidget *parent = nullptr);

private slots:
    void accept() override;

private:
    QLineEdit *descriptionEdit;
    QDoubleSpinBox *amountEdit;
    QDateEdit *dateEdit;
    QDialogButtonBox *buttonBox;
    Income *income; // The income to edit
};

#endif // EDITINCOMEDIALOG_H
