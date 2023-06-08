#include "editexpensedialog.h"

EditExpenseDialog::EditExpenseDialog(Expense& expense, QWidget *parent)
    : QDialog(parent), originalExpense(expense), modifiedExpense(expense) {
    setWindowTitle("Modifica Spesa");

    descriptionEdit = new QLineEdit(expense.getDescription(), this);
    amountEdit = new QDoubleSpinBox(this);
    amountEdit->setMinimum(0);
    amountEdit->setMaximum(9999999);
    amountEdit->setDecimals(2);
    amountEdit->setValue(expense.getAmount());
    dateEdit = new QDateEdit(expense.getDate(), this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Descrizione:"), descriptionEdit);
    formLayout->addRow(new QLabel("Importo:"), amountEdit);
    formLayout->addRow(new QLabel("Data:"), dateEdit);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditExpenseDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditExpenseDialog::reject);
}

QString EditExpenseDialog::getExpenseDescription() const {
    return descriptionEdit->text();
}

double EditExpenseDialog::getExpenseAmount() const {
    return amountEdit->value();
}

QDate EditExpenseDialog::getExpenseDate() const {
    return dateEdit->date();
}

Expense EditExpenseDialog::getModifiedExpense() const {
    return modifiedExpense;
}

void EditExpenseDialog::accept() {
    modifiedExpense.setDescription(getExpenseDescription());
    modifiedExpense.setAmount(getExpenseAmount());
    modifiedExpense.setDate(getExpenseDate());
    QDialog::accept();
}
