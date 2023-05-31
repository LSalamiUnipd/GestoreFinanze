#include "editincomedialog.h"
#include <QFormLayout>
#include <QLabel>

// Costruttore della classe EditIncomeDialog
EditIncomeDialog::EditIncomeDialog(Income *incomeToEdit, QWidget *parent)
    : QDialog(parent), income(incomeToEdit) {
    setWindowTitle("Modifica Entrata");

    // Inizializzazione dei widget di input e dei pulsanti
    descriptionEdit = new QLineEdit(this);
    amountEdit = new QDoubleSpinBox(this);
    amountEdit->setMinimum(0);
    amountEdit->setMaximum(9999999);
    amountEdit->setDecimals(2);
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // Precompila i campi con i dati dell'entrata da modificare
    descriptionEdit->setText(income->getDescription());
    amountEdit->setValue(income->getAmount());
    dateEdit->setDate(income->getDate());

    // Layout e aggiunta dei widget
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Descrizione:"), descriptionEdit);
    formLayout->addRow(new QLabel("Importo:"), amountEdit);
    formLayout->addRow(new QLabel("Data:"), dateEdit);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);

    // Connessione dei pulsanti alle funzioni di QDialog
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditIncomeDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditIncomeDialog::reject);
}

// Metodo che viene chiamato quando il pulsante OK viene premuto
void EditIncomeDialog::accept() {
    // Aggiorna i dati dell'entrata con i nuovi valori inseriti
    income->setDescription(descriptionEdit->text());
    income->setAmount(amountEdit->value());
    income->setDate(dateEdit->date());

    // Chiama il metodo accept della classe base QDialog per chiudere il dialogo
    QDialog::accept();
}
