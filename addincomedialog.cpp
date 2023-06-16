#include "addincomedialog.h"
#include <QFormLayout>
#include <QLabel>

// Costruttore di AddIncomeDialog
AddIncomeDialog::AddIncomeDialog(QWidget *parent)
    : QDialog(parent),
    descriptionEdit(new QLineEdit(this)),
    amountEdit(new QDoubleSpinBox(this)),
    dateEdit(new QDateEdit(QDate::currentDate(), this)),
    buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)) {

    setWindowTitle("Aggiungi Entrata");

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
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddIncomeDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddIncomeDialog::reject);
}

// Ottiene la descrizione del reddito
QString AddIncomeDialog::getIncomeDescription() const {
    return descriptionEdit->text();
}

// Ottiene l'importo del reddito
double AddIncomeDialog::getIncomeAmount() const {
    return amountEdit->value();
}

// Ottiene la data del reddito
QDate AddIncomeDialog::getIncomeDate() const {
    return dateEdit->date();
}
