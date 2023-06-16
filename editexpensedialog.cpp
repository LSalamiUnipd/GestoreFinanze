#include "editexpensedialog.h"

// Costruttore della classe EditExpenseDialog
EditExpenseDialog::EditExpenseDialog(Expense& expense, QWidget *parent)
    : QDialog(parent), originalExpense(expense), modifiedExpense(expense) {
    setWindowTitle("Modifica Spesa");

    // Inizializzazione dei widget di input e dei pulsanti
    descriptionEdit = new QLineEdit(expense.getDescription(), this);
    amountEdit = new QDoubleSpinBox(this);
    amountEdit->setMinimum(0);
    amountEdit->setMaximum(9999999);
    amountEdit->setDecimals(2);
    amountEdit->setValue(expense.getAmount());
    dateEdit = new QDateEdit(expense.getDate(), this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

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

// Ottiene la descrizione della spesa
QString EditExpenseDialog::getExpenseDescription() const {
    return descriptionEdit->text();
}

// Ottiene l'importo della spesa
double EditExpenseDialog::getExpenseAmount() const {
    return amountEdit->value();
}

// Ottiene la data della spesa
QDate EditExpenseDialog::getExpenseDate() const {
    return dateEdit->date();
}

// Ottiene la spesa modificata
Expense EditExpenseDialog::getModifiedExpense() const {
    return modifiedExpense;
}

// Slot che viene chiamato quando il pulsante OK viene premuto
void EditExpenseDialog::accept() {
    // Aggiorna i dati della spesa con i nuovi valori inseriti
    modifiedExpense.setDescription(getExpenseDescription());
    modifiedExpense.setAmount(getExpenseAmount());
    modifiedExpense.setDate(getExpenseDate());

    // Chiama il metodo accept della classe base QDialog per chiudere il dialogo
    QDialog::accept();
}
