#include "addincomedialog.h"
#include <QFormLayout>
#include <QLabel>

// Costruttore della classe AddIncomeDialog
AddIncomeDialog::AddIncomeDialog(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Aggiungi Entrata");

    // Inizializzazione dei widget di input e dei pulsanti
    descriptionEdit = new QLineEdit(this);
    amountEdit = new QDoubleSpinBox(this);
    amountEdit->setMinimum(0);
    amountEdit->setMaximum(9999999);
    amountEdit->setDecimals(2);
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // Layout e aggiunta dei widget
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

// Metodo per ottenere la descrizione dell'entrata
QString AddIncomeDialog::getIncomeDescription() const {
    return descriptionEdit->text();
}

// Metodo per ottenere l'importo dell'entrata
double AddIncomeDialog::getIncomeAmount() const {
    return amountEdit->value();
}

// Metodo per ottenere la data dell'entrata
QDate AddIncomeDialog::getIncomeDate() const {
    return dateEdit->date();
}
