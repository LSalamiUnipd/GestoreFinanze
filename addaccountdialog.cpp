#include "addaccountdialog.h"
#include <QFormLayout>
#include <QLabel>

// Costruttore della classe AddAccountDialog
AddAccountDialog::AddAccountDialog(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Aggiungi Account");

    // Inizializzazione dei widget di input e dei pulsanti
    nameEdit = new QLineEdit(this);
    descriptionEdit = new QTextEdit(this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // Layout e aggiunta dei widget
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Nome:"), nameEdit);
    formLayout->addRow(new QLabel("Descrizione:"), descriptionEdit);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);

    // Connessione dei pulsanti alle funzioni di QDialog
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddAccountDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddAccountDialog::reject);
}

// Metodo per ottenere il nome dell'account
QString AddAccountDialog::getAccountName() const {
    return nameEdit->text();
}

// Metodo per ottenere la descrizione dell'account
QString AddAccountDialog::getAccountDescription() const {
    return descriptionEdit->toPlainText();
}
