#ifndef EDITEXPENSEDIALOG_H
#define EDITEXPENSEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include "expense.h"

class EditExpenseDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditExpenseDialog(Expense& expense, QWidget *parent = nullptr);

    Expense getModifiedExpense() const;
    QString getExpenseDescription() const;
    double getExpenseAmount() const;
    QDate getExpenseDate() const;

private slots:
    void accept() override;

private:
    Expense& originalExpense;
    Expense modifiedExpense;

    QLineEdit *descriptionEdit;
    QDoubleSpinBox *amountEdit;
    QDateEdit *dateEdit;
    QDialogButtonBox *buttonBox;
};

#endif // EDITEXPENSEDIALOG_H
