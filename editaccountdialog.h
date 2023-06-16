#ifndef EDITACCOUNTDIALOG_H
#define EDITACCOUNTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QTextEdit>

class Account;

// Classe EditAccountDialog per modificare un account esistente
class EditAccountDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditAccountDialog(Account *accountToEdit, QWidget *parent = nullptr); // Costruttore

    QString getAccountName() const; // Ottiene il nome dell'account
    QString getAccountDescription() const; // Ottiene la descrizione dell'account

public slots:
    void accept() override; // Slot che viene chiamato quando il pulsante OK viene premuto

private:
    QLineEdit *nameEdit; // Campo per inserire il nome dell'account
    QTextEdit *descriptionEdit; // Campo per inserire la descrizione dell'account
    QDialogButtonBox *buttonBox; // Pulsanti di conferma e annullamento

    Account *account; // Riferimento all'account da modificare
};

#endif // EDITACCOUNTDIALOG_H
