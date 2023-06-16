#include "editloandialog.h"

// Costruttore
EditLoanDialog::EditLoanDialog(Loan& loan, QWidget *parent)
    : QDialog(parent), originalLoan(loan), modifiedLoan(loan) {
    setWindowTitle("Modifica Prestito");

    // Inizializzazione dei widget di input con i valori del Loan da modificare
    descriptionEdit = new QLineEdit(loan.getDescription(), this);
    amountEdit = new QDoubleSpinBox(this);
    amountEdit->setMinimum(0);
    amountEdit->setMaximum(9999999);
    amountEdit->setDecimals(2);
    amountEdit->setValue(loan.getAmount());
    dateEdit = new QDateEdit(loan.getDate(), this);
    durationSpinBox = new QSpinBox(this);
    durationSpinBox->setMinimum(1);
    durationSpinBox->setValue(loan.getDuration());
    interestRateSpinBox = new QDoubleSpinBox(this);
    interestRateSpinBox->setMinimum(0);
    interestRateSpinBox->setMaximum(100);
    interestRateSpinBox->setDecimals(2);
    interestRateSpinBox->setValue(loan.getInterestRate());
    paidCheckBox = new QCheckBox("Pagato", this);
    paidCheckBox->setChecked(loan.isLoanPaid());
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // Creazione e assegnazione del layout
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Descrizione:"), descriptionEdit);
    formLayout->addRow(new QLabel("Importo:"), amountEdit);
    formLayout->addRow(new QLabel("Data:"), dateEdit);
    formLayout->addRow(new QLabel("Durata (in mesi):"), durationSpinBox);
    formLayout->addRow(new QLabel("Tasso di interesse (%):"), interestRateSpinBox);
    formLayout->addRow(paidCheckBox);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);

    // Collegamento dei pulsanti di accettazione e rifiuto agli slot appropriati
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditLoanDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditLoanDialog::reject);
}

// Implementazione dei getter
QString EditLoanDialog::getLoanDescription() const {
    return descriptionEdit->text();
}

double EditLoanDialog::getLoanAmount() const {
    return amountEdit->value();
}

QDate EditLoanDialog::getLoanDate() const {
    return dateEdit->date();
}

int EditLoanDialog::getLoanDuration() const {
    return durationSpinBox->value();
}

double EditLoanDialog::getLoanInterestRate() const {
    return interestRateSpinBox->value();
}

bool EditLoanDialog::isLoanPaid() const {
    return paidCheckBox->isChecked();
}

Loan EditLoanDialog::getModifiedLoan() const {
    return modifiedLoan;
}

// Slot di accettazione: modifica il Loan e chiude il dialogo
void EditLoanDialog::accept() {
    modifiedLoan.setDescription(getLoanDescription());
    modifiedLoan.setAmount(getLoanAmount());
    modifiedLoan.setDate(getLoanDate());
    modifiedLoan.setDuration(getLoanDuration());
    modifiedLoan.setInterestRate(getLoanInterestRate());
    modifiedLoan.setLoanPaid(isLoanPaid());
    QDialog::accept();
}
