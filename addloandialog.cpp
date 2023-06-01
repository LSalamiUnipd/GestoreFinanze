#include "addloandialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QFormLayout>

AddLoanDialog::AddLoanDialog(QWidget *parent)
    : QDialog(parent) {
    QLabel *descriptionLabel = new QLabel("Descrizione:", this);
    descriptionLineEdit = new QLineEdit(this);

    QLabel *amountLabel = new QLabel("Importo:", this);
    amountSpinBox = new QDoubleSpinBox(this);
    amountSpinBox->setMinimum(0.0);

    QLabel *dateLabel = new QLabel("Data:", this);
    dateEdit = new QDateEdit(this);
    dateEdit->setCalendarPopup(true);

    QLabel *durationLabel = new QLabel("Durata (mesi):", this);
    durationSpinBox = new QSpinBox(this);
    durationSpinBox->setMinimum(1);

    QLabel *interestRateLabel = new QLabel("Tasso di interesse (%):", this);
    interestRateSpinBox = new QDoubleSpinBox(this);
    interestRateSpinBox->setMinimum(0.0);

    QLabel *paidLabel = new QLabel("Pagato:", this);
    paidCheckBox = new QCheckBox(this);

    QPushButton *confirmButton = new QPushButton("Conferma", this);

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

AddLoanDialog::~AddLoanDialog() {
}

QString AddLoanDialog::getLoanDescription() const {
    return descriptionLineEdit->text();
}

double AddLoanDialog::getLoanAmount() const {
    return amountSpinBox->value();
}

QDate AddLoanDialog::getLoanDate() const {
    return dateEdit->date();
}

int AddLoanDialog::getLoanDuration() const {
    return durationSpinBox->value();
}

double AddLoanDialog::getLoanInterestRate() const {
    return interestRateSpinBox->value();
}

bool AddLoanDialog::isLoanPaid() const {
    return paidCheckBox->isChecked();
}
