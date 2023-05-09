#ifndef ADDACCOUNTDIALOG_H
#define ADDACCOUNTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialogButtonBox>

// Dichiarazione della classe AddAccountDialog
class AddAccountDialog : public QDialog {
    Q_OBJECT

public:
    // Costruttore
    explicit AddAccountDialog(QWidget *parent = nullptr);

    // Metodo per ottenere il nome dell'account
    QString getAccountName() const;

    // Metodo per ottenere la descrizione dell'account
    QString getAccountDescription() const;

private:
    QLineEdit *nameEdit;            // Campo di input per il nome dell'account
    QTextEdit *descriptionEdit;     // Campo di input per la descrizione dell'account
    QDialogButtonBox *buttonBox;    // Pulsanti di conferma e annullamento
};

#endif // ADDACCOUNTDIALOG_H
