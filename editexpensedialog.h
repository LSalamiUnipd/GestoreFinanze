#ifndef EDITEXPENSEDIALOG_H
#define EDITEXPENSEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include "expense.h" // Include your Expense header file here

class EditExpenseDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditExpenseDialog(Expense *expenseToEdit, QWidget *parent = nullptr);

private slots:
    void accept() override;

private:
    QLineEdit *descriptionEdit;
    QDoubleSpinBox *amountEdit;
    QDateEdit *dateEdit;
    QDialogButtonBox *buttonBox;
    Expense *expense; // The expense to edit
};

#endif // EDITEXPENSEDIALOG_H
