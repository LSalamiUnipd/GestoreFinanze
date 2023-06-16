#include "addexpensedialog.h"
#include <QFormLayout>
#include <QLabel>

// Costruttore di AddExpenseDialog
AddExpenseDialog::AddExpenseDialog(QWidget *parent)
    : QDialog(parent),
    descriptionEdit(new QLineEdit(this)),
    amountEdit(new QDoubleSpinBox(this)),
    dateEdit(new QDateEdit(QDate::currentDate(), this)),
    buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)) {

    setWindowTitle("Aggiungi Spesa");

    amountEdit->setMinimum(0);
    amountEdit->setMaximum(9999999);
    amountEdit->setDecimals(2);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Descrizione:"), descriptionEdit);
    formLayout->addRow(new QLabel("Importo:"), amountEdit);
    formLayout->addRow(new QLabel("Data:"), dateEdit);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);

    // Connessione dei pulsanti alle funzioni di QDialog
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddExpenseDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddExpenseDialog::reject);
}

// Ottiene la descrizione della spesa
QString AddExpenseDialog::getExpenseDescription() const {
    return descriptionEdit->text();
}

// Ottiene l'importo della spesa
double AddExpenseDialog::getExpenseAmount() const {
    return amountEdit->value();
}

// Ottiene la data della spesa
QDate AddExpenseDialog::getExpenseDate() const {
    return dateEdit->date();
}
