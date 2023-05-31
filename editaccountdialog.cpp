#include "editaccountdialog.h"
#include <QFormLayout>
#include <QLabel>
#include "account.h"

// Costruttore della classe EditAccountDialog
EditAccountDialog::EditAccountDialog(Account *accountToEdit, QWidget *parent)
    : QDialog(parent), account(accountToEdit) {
    setWindowTitle("Modifica Account");

    // Inizializzazione dei widget di input e dei pulsanti
    nameEdit = new QLineEdit(this);
    descriptionEdit = new QTextEdit(this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // Precompila i campi con i dati dell'account da modificare
    nameEdit->setText(account->getName());
    descriptionEdit->setPlainText(account->getDescription());

    // Layout e aggiunta dei widget
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Nome:"), nameEdit);
    formLayout->addRow(new QLabel("Descrizione:"), descriptionEdit);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);

    // Connessione dei pulsanti alle funzioni di QDialog
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditAccountDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditAccountDialog::reject);
}

// Metodo per ottenere il nome dell'account
QString EditAccountDialog::getAccountName() const {
    return nameEdit->text();
}

// Metodo per ottenere la descrizione dell'account
QString EditAccountDialog::getAccountDescription() const {
    return descriptionEdit->toPlainText();
}

// Metodo che viene chiamato quando il pulsante OK viene premuto
void EditAccountDialog::accept() {
    // Aggiorna i dati dell'account con i nuovi valori inseriti
    account->setName(nameEdit->text());
    account->setDescription(descriptionEdit->toPlainText());

    // Chiama il metodo accept della classe base QDialog per chiudere il dialogo
    QDialog::accept();
}
