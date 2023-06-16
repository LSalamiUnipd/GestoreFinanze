#include "addaccountdialog.h"
#include <QFormLayout>
#include <QLabel>

// Costruttore di AddAccountDialog
AddAccountDialog::AddAccountDialog(QWidget *parent)
    : QDialog(parent), nameEdit(new QLineEdit(this)),
    descriptionEdit(new QTextEdit(this)),
    buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)) {

    setWindowTitle("Aggiungi Account");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Nome:"), nameEdit);
    formLayout->addRow(new QLabel("Descrizione:"), descriptionEdit);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);

    // Connessione dei pulsanti alle funzioni di QDialog
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddAccountDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddAccountDialog::reject);
}

// Ottiene il nome dell'account
QString AddAccountDialog::getAccountName() const {
    return nameEdit->text();
}

// Ottiene la descrizione dell'account
QString AddAccountDialog::getAccountDescription() const {
    return descriptionEdit->toPlainText();
}
