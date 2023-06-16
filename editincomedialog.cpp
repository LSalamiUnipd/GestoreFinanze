#include "editincomedialog.h"

// Costruttore
EditIncomeDialog::EditIncomeDialog(Income& income, QWidget *parent)
    : QDialog(parent), originalIncome(income), modifiedIncome(income) {
    setWindowTitle("Modifica Entrata");

    // Inizializzazione dei widget di input con i valori dell'Income da modificare
    descriptionEdit = new QLineEdit(income.getDescription(), this);
    amountEdit = new QDoubleSpinBox(this);
    amountEdit->setMinimum(0);
    amountEdit->setMaximum(9999999);
    amountEdit->setDecimals(2);
    amountEdit->setValue(income.getAmount());
    dateEdit = new QDateEdit(income.getDate(), this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // Creazione e assegnazione del layout
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Descrizione:"), descriptionEdit);
    formLayout->addRow(new QLabel("Importo:"), amountEdit);
    formLayout->addRow(new QLabel("Data:"), dateEdit);
    formLayout->addWidget(buttonBox);
    setLayout(formLayout);

    // Collegamento dei pulsanti di accettazione e rifiuto agli slot appropriati
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditIncomeDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditIncomeDialog::reject);
}

// Implementazione dei getter
QString EditIncomeDialog::getIncomeDescription() const {
    return descriptionEdit->text();
}

double EditIncomeDialog::getIncomeAmount() const {
    return amountEdit->value();
}

QDate EditIncomeDialog::getIncomeDate() const {
    return dateEdit->date();
}

Income EditIncomeDialog::getModifiedIncome() const {
    return modifiedIncome;
}

// Slot di accettazione: modifica l'Income e chiude il dialogo
void EditIncomeDialog::accept() {
    modifiedIncome.setDescription(getIncomeDescription());
    modifiedIncome.setAmount(getIncomeAmount());
    modifiedIncome.setDate(getIncomeDate());
    QDialog::accept();
}
