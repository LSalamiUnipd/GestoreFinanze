#include "editexpensedialog.h"
#include <QFormLayout>
#include <QLabel>

// Costruttore della classe EditExpenseDialog
EditExpenseDialog::EditExpenseDialog(Expense *expenseToEdit, QWidget *parent)
    : QDialog(parent), expense(expenseToEdit) {
    setWindowTitle("Modifica Spesa");

    // Inizializzazione dei widget di input e dei pulsanti
    descriptionEdit = new QLineEdit(this);
    amountEdit = new QDoubleSpinBox(this);
    amountEdit->setMinimum(0);
    amountEdit->setMaximum(9999999);
    amountEdit->setDecimals(2);
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // Precompila i campi con i dati della spesa da modificare
    descriptionEdit->setText(expense->getDescription());
    amountEdit->setValue(expense->getAmount());
    dateEdit->setDate(expense->getDate());

    // Layout e aggiunta dei widget
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Descrizione:"), descriptionEdit);
    formLayout->addRow(new QLabel("Importo:"), amountEdit);
    formLayout->addRow(new QLabel("Data:"), dateEdit);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);

    // Connessione dei pulsanti alle funzioni di QDialog
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditExpenseDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditExpenseDialog::reject);
}

// Metodo che viene chiamato quando il pulsante OK viene premuto
void EditExpenseDialog::accept() {
    // Aggiorna i dati della spesa con i nuovi valori inseriti
    expense->setDescription(descriptionEdit->text());
    expense->setAmount(amountEdit->value());
    expense->setDate(dateEdit->date());

    // Chiama il metodo accept della classe base QDialog per chiudere il dialogo
    QDialog::accept();
}
