#include "addloandialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QFormLayout>

// Costruttore di AddLoanDialog
AddLoanDialog::AddLoanDialog(QWidget *parent)
    : QDialog(parent),
    descriptionLineEdit(new QLineEdit(this)),
    amountSpinBox(new QDoubleSpinBox(this)),
    dateEdit(new QDateEdit(this)),
    durationSpinBox(new QSpinBox(this)),
    interestRateSpinBox(new QDoubleSpinBox(this)),
    paidCheckBox(new QCheckBox(this)) {

    QLabel *descriptionLabel = new QLabel("Descrizione:", this);
    QLabel *amountLabel = new QLabel("Importo:", this);
    QLabel *dateLabel = new QLabel("Data:", this);
    QLabel *durationLabel = new QLabel("Durata (mesi):", this);
    QLabel *interestRateLabel = new QLabel("Tasso di interesse (%):", this);
    QLabel *paidLabel = new QLabel("Pagato:", this);
    QPushButton *confirmButton = new QPushButton("Conferma", this);

    amountSpinBox->setMinimum(0.0);
    dateEdit->setCalendarPopup(true);
    durationSpinBox->setMinimum(1);
    interestRateSpinBox->setMinimum(0.0);

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(descriptionLabel, descriptionLineEdit);
    formLayout->addRow(amountLabel, amountSpinBox);
    formLayout->addRow(dateLabel, dateEdit);
    formLayout->addRow(durationLabel, durationSpinBox);
    formLayout->addRow(interestRateLabel, interestRateSpinBox);
    formLayout->addRow(paidLabel, paidCheckBox);
    formLayout->addRow(confirmButton);

    connect(confirmButton, &QPushButton::clicked, this, &AddLoanDialog::accept);
}

// Distruttore di AddLoanDialog
AddLoanDialog::~AddLoanDialog() {
}

// Ottiene la descrizione del prestito
QString AddLoanDialog::getLoanDescription() const {
    return descriptionLineEdit->text();
}

// Ottiene l'importo del prestito
double AddLoanDialog::getLoanAmount() const {
    return amountSpinBox->value();
}

// Ottiene la data del prestito
QDate AddLoanDialog::getLoanDate() const {
    return dateEdit->date();
}

// Ottiene la durata del prestito
int AddLoanDialog::getLoanDuration() const {
    return durationSpinBox->value();
}

// Ottiene il tasso di interesse del prestito
double AddLoanDialog::getLoanInterestRate() const {
    return interestRateSpinBox->value();
}

// Verifica se il prestito è stato pagato
bool AddLoanDialog::isLoanPaid() const {
    return paidCheckBox->isChecked();
}
