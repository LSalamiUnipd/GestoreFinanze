#ifndef ADDACCOUNTDIALOG_H
#define ADDACCOUNTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialogButtonBox>

// Classe AddAccountDialog per aggiungere un nuovo account tramite un dialog
class AddAccountDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddAccountDialog(QWidget *parent = nullptr); // Costruttore

    QString getAccountName() const; // Ottiene il nome dell'account
    QString getAccountDescription() const; // Ottiene la descrizione dell'account

private:
    QLineEdit *nameEdit; // Campo per inserire il nome dell'account
    QTextEdit *descriptionEdit; // Campo per inserire la descrizione dell'account
    QDialogButtonBox *buttonBox; // Pulsanti di conferma e annullamento
};

#endif // ADDACCOUNTDIALOG_H
