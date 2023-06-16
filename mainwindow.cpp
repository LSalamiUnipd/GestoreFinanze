#include "mainwindow.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTreeView>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QListWidget>
#include "addaccountdialog.h"
#include "addexpensedialog.h"
#include "addincomedialog.h"
#include "addloandialog.h"
#include "editaccountdialog.h"
#include "editexpensedialog.h"
#include "editincomedialog.h"
#include "editloandialog.h"
#include "expense.h"
#include "income.h"
#include "loan.h"
#include <QLabel>

// Costruttore
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    // Imposta le dimensioni della finestra principale
    resize(800, 600);

    // Crea le azioni
    createActions();
    // Crea i menu
    createMenus();
    // Crea le barre degli strumenti
    createToolBars();
    // Crea la barra di stato
    createStatusBar();
    // Crea il widget centrale
    createCentralWidget();
    // Connetti il segnale 'currentItemChanged' del widget accountListWidget allo slot 'on_accountListWidget_currentItemChanged'
    connect(accountListWidget, &QListWidget::currentItemChanged, this, &MainWindow::on_accountListWidget_currentItemChanged);
}

// Distruttore
MainWindow::~MainWindow() {
}

void MainWindow::createActions()
{
    // Crea l'azione "Apri"
    openAction = new QAction(tr("&Apri"), this);
    // Imposta il tasto di scelta rapida per l'azione "Apri"
    openAction->setShortcut(QKeySequence::Open);
    // Connetti il segnale 'triggered' dell'azione 'openAction' allo slot 'on_actionOpen_triggered'
    connect(openAction, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);

    // Azione per salvare un file
    saveAction = new QAction(tr("&Salva"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);

    // Azione per salvare un file con un nuovo nome
    saveAsAction = new QAction(tr("&Salva con nome..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::on_actionSave_As_triggered);

    // Azione per uscire dall'applicazione
    exitAction = new QAction(tr("&Esci"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    // Azioni per gestire gli account e le transazioni
    addAccountAction = new QAction(tr("&Aggiungi Account"), this);
    connect(addAccountAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Account_triggered);

    addExpenseAction = new QAction(tr("&Aggiungi Spesa"), this);
    connect(addExpenseAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Expense_triggered);

    addIncomeAction = new QAction(tr("&Aggiungi Entrata"), this);
    connect(addIncomeAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Income_triggered);

    addLoanAction = new QAction(tr("&Aggiungi Prestito"), this);
    connect(addLoanAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Loan_triggered);

    removeAccountAction = new QAction(tr("&Rimuovi Account"), this);
    connect(removeAccountAction, &QAction::triggered, this, &MainWindow::on_actionRemove_Account_triggered);

    editAccountAction = new QAction(tr("&Modifica Account"), this);
    connect(editAccountAction, &QAction::triggered, this, &MainWindow::on_actionEdit_Account_triggered);

    removeTransactionAction = new QAction(tr("&Rimuovi Transazione"), this);
    connect(removeTransactionAction, &QAction::triggered, this, &MainWindow::on_actionRemove_Transaction_triggered);

    editTransactionAction = new QAction(tr("&Modifica Transazione"), this);
    connect(editTransactionAction, &QAction::triggered, this, &MainWindow::on_actionEdit_Transaction_triggered);
}
// Crea i menu
void MainWindow::createMenus()
{
    // Crea il menu "File"
    fileMenu = menuBar()->addMenu(tr("&File"));
    // Aggiungi l'azione "Apri" al menu "File"
    fileMenu->addAction(openAction);
    // (Analogamente per le altre azioni...)
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Modifica"));
    editMenu->addAction(addAccountAction);
    editMenu->addAction(addIncomeAction);
    editMenu->addAction(addExpenseAction);
    editMenu->addAction(addLoanAction);
    editMenu->addSeparator();
    editMenu->addAction(removeAccountAction);
    editMenu->addAction(editAccountAction);
    editMenu->addAction(removeTransactionAction);
    editMenu->addAction(editTransactionAction);
}

// Crea le barre degli strumenti
void MainWindow::createToolBars()
{
    // Crea la barra degli strumenti "File"
    fileToolBar = addToolBar(tr("File"));
    // Aggiungi l'azione "Apri" alla barra degli strumenti "File"
    fileToolBar->addAction(openAction);
    // (Analogamente per le altre azioni...)
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);

    editToolBar = addToolBar(tr("Modifica"));
    editToolBar->addAction(addAccountAction);
    editToolBar->addAction(addIncomeAction);
    editToolBar->addAction(addExpenseAction);
    editToolBar->addAction(addLoanAction);
    editToolBar->addAction(removeAccountAction);
    editToolBar->addAction(editAccountAction);
    editToolBar->addAction(removeTransactionAction);
    editToolBar->addAction(editTransactionAction);
}

// Crea la barra di stato
void MainWindow::createStatusBar()
{
    // Mostra il messaggio "Pronto" nella barra di stato
    statusBar()->showMessage(tr("Pronto"));
}

// Questa funzione crea il widget centrale dell'interfaccia, composto da due liste (account e transazioni) e da un'etichetta per il saldo.
void MainWindow::createCentralWidget()
{
    accountListWidget = new QListWidget(this);
    transactionListWidget = new QListWidget(this);

    // Creiamo le etichette per i nostri widget
    accountListWidgetLabel = new QLabel(tr("Account"), this);
    transactionListWidgetLabel = new QLabel(tr("Transazioni"), this);
    balanceLabel = new QLabel(this);

    // Creiamo un layout verticale e aggiungiamo i nostri widget
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(accountListWidgetLabel);
    layout->addWidget(accountListWidget);
    layout->addWidget(transactionListWidgetLabel);
    layout->addWidget(transactionListWidget);
    layout->addWidget(balanceLabel);


    // Creiamo un widget centrale e gli assegniamo il layout che abbiamo appena creato
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);

    // Impostiamo il widget centrale dell'interfaccia
    setCentralWidget(centralWidget);
}

// Questa funzione viene chiamata quando un elemento della lista degli account viene selezionato. Aggiorna la lista delle transazioni e il saldo.
void MainWindow::on_accountListWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    Q_UNUSED(previous);

    // Otteniamo l'indice dell'account selezionato
    int selectedIndex = accountListWidget->row(current);
    qDebug() << "Indice selezionato: " << selectedIndex;

    // Verifichiamo se l'indice selezionato è valido
    if (selectedIndex >= 0 && selectedIndex < accountContainer.getAccounts().size()) {
        // Aggiorniamo la lista delle transazioni per questo account
        try {
            updateTransactionList(selectedIndex);
        } catch (const std::out_of_range& e) {
            qDebug() << "Errore nell'aggiornamento della lista di transazioni: " << e.what();
        }
    } else {
        qDebug() << "Indice non valido: " << selectedIndex;
    }

    // Aggiorniamo il saldo
    updateBalance();
}

// Questo slot viene eseguito quando si tenta di aprire un file JSON
void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Apri File"), QString(), tr("JSON Files (*.json)"));
    if (!filePath.isEmpty()) {
        openFile(filePath);
    }
}

// Questo slot viene attivato quando si cerca di salvare il file JSON corrente
void MainWindow::on_actionSave_triggered() {
    if (currentFilePath.isEmpty()) {
        on_actionSave_As_triggered();
    } else {
        saveFile(currentFilePath);
    }
}

// Questo slot viene utilizzato per salvare un file JSON con un nome diverso
void MainWindow::on_actionSave_As_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Salva File Con Nome"), QString(), tr("JSON Files (*.json)"));
    if (!filePath.isEmpty()) {
        saveFile(filePath);
    }
}

// Questo slot permette l'uscita dall'applicazione
void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

// Questo slot viene utilizzato per creare un nuovo account
void MainWindow::on_actionAdd_Account_triggered() {
    AddAccountDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Account newAccount(dialog.getAccountName(), dialog.getAccountDescription());
        accountContainer.addAccount(newAccount);
        updateAccountList();
    }
    updateBalance();
}

// Questo slot viene utilizzato per l'aggiunta di una nuova spesa
void MainWindow::on_actionAdd_Expense_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Errore"), tr("Nesssun account selezionato."));
        return;
    }

    AddExpenseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString description = dialog.getExpenseDescription();
        double amount = dialog.getExpenseAmount();
        QDate date = dialog.getExpenseDate();

        Expense newExpense(description, amount, date);

        try {
            accountContainer.addTransactionToAccount(selectedIndex, newExpense);
            updateTransactionList(selectedIndex);
        } catch (const std::out_of_range& e) {
            qDebug() << "Errore nell'aggiunta della spesa: " << e.what();
            QMessageBox::warning(this, tr("Errore"), tr("Aggiunta della spesa non riuscita."));
        }
    }
    updateBalance();
}

// Questo slot viene utilizzato per l'aggiunta di un nuovo reddito
void MainWindow::on_actionAdd_Income_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Errore"), tr("Nessun account selezionato."));
        return;
    }

    AddIncomeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString description = dialog.getIncomeDescription();
        double amount = dialog.getIncomeAmount();
        QDate date = dialog.getIncomeDate();

        Income newIncome(description, amount, date);

        try {
            accountContainer.addTransactionToAccount(selectedIndex, newIncome);
            updateTransactionList(selectedIndex);
        } catch (const std::out_of_range& e) {
            qDebug() << "Errore nell'aggiunta del reddito: " << e.what();
            QMessageBox::warning(this, tr("Errore"), tr("Aggiunta del reddito non riuscito."));
        }
    }
    updateBalance();
}

// Questo slot viene utilizzato per l'aggiunta di un nuovo prestito
void MainWindow::on_actionAdd_Loan_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Errore"), tr("Nessun account selezionato."));
        return;
    }

    AddLoanDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString description = dialog.getLoanDescription();
        double amount = dialog.getLoanAmount();
        QDate date = dialog.getLoanDate();
        int duration = dialog.getLoanDuration();
        double interestRate = dialog.getLoanInterestRate();
        bool isPaid = dialog.isLoanPaid();

        Loan newLoan(description, amount, date, duration, interestRate, isPaid);

        try {
            accountContainer.addTransactionToAccount(selectedIndex, newLoan);
            updateTransactionList(selectedIndex);
        } catch (const std::out_of_range& e) {
            qDebug() << "Errore nell'aggiunta del prestito: " << e.what();
            QMessageBox::warning(this, tr("Errore"), tr("Aggiunta del prestito non riuscito."));
        }
    }
    updateBalance();
}


// Questo slot viene utilizzato per rimuovere un account
void MainWindow::on_actionRemove_Account_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Errore"), tr("Nessun account selezionato."));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Rimuovi Account"), tr("Sei sicuro di voler rimuovere l'account selezionato?"),
    QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        accountContainer.removeAccount(selectedIndex);
        updateAccountList();
    }
    updateBalance();
}

// Questo slot viene utilizzato per modificare un account
void MainWindow::on_actionEdit_Account_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0 || selectedIndex >= accountContainer.getAccounts().size()) {
        QMessageBox::warning(this, tr("Errore"), tr("Nessun account selezionato."));
        return;
    }

    // Ottenere l'account corrente
    Account currentAccount = accountContainer.getAccount(selectedIndex);

    // Creare un dialogo di modifica account con le informazioni correnti precompilate.
    EditAccountDialog dialog(&currentAccount, this);

    // Se l'utente ha accettato il dialogo, aggiorna l'account nell'AccountContainer
    if (dialog.exec() == QDialog::Accepted) {
        accountContainer.setAccount(selectedIndex, currentAccount);
        updateAccountList();
    }
}

// Questo slot viene utilizzato per rimuovere una transazione
void MainWindow::on_actionRemove_Transaction_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    int selectedTransactionIndex = transactionListWidget->currentRow();

    if (selectedIndex < 0 || selectedTransactionIndex < 0) {
        QMessageBox::warning(this, tr("Errore"), tr("Nessun account o transazione selezionato."));
        return;
    }

    try {
        accountContainer.removeTransactionFromAccount(selectedIndex, selectedTransactionIndex);
        updateTransactionList(selectedIndex);
        updateBalance();
    } catch (const std::out_of_range& e) {
        qDebug() << "Errore nella rimozione della transazionie: " << e.what();
        QMessageBox::warning(this, tr("Errore"), tr("Rimozione della transazione non riuscita."));
    }
}

// Questo slot viene utilizzato per modificare una transazione
void MainWindow::on_actionEdit_Transaction_triggered() {
    int selectedAccountIndex = accountListWidget->currentRow();
    int selectedTransactionIndex = transactionListWidget->currentRow();
    if (selectedAccountIndex < 0 || selectedTransactionIndex < 0) {
        QMessageBox::warning(this, tr("Errore"), tr("Nessun account o transazione selezionato."));
        return;
    }

    // Ottieni la transazione corrente
    Finance* currentTransaction = accountContainer.getTransactionFromAccount(selectedAccountIndex, selectedTransactionIndex);

    // Decidi il tipo di dialogo da mostrare sulla base del tipo di transazione
    if (Expense* expense = dynamic_cast<Expense*>(currentTransaction)) {
        EditExpenseDialog* editDialog = new EditExpenseDialog(*expense, this);
        if (editDialog->exec() == QDialog::Accepted) {
            *expense = editDialog->getModifiedExpense();
        }
        delete editDialog;
    } else if (Income* income = dynamic_cast<Income*>(currentTransaction)) {
        EditIncomeDialog* editDialog = new EditIncomeDialog(*income, this);
        if (editDialog->exec() == QDialog::Accepted) {
            *income = editDialog->getModifiedIncome();
        }
        delete editDialog;
    } else if (Loan* loan = dynamic_cast<Loan*>(currentTransaction)) {
        EditLoanDialog* editDialog = new EditLoanDialog(*loan, this);
        if (editDialog->exec() == QDialog::Accepted) {
            *loan = editDialog->getModifiedLoan();
        }
        delete editDialog;
    }

    // Aggiorna la lista delle transazioni
    updateTransactionList(selectedAccountIndex);
    updateBalance();
}

// Metodo per aprire un file JSON
void MainWindow::openFile(const QString &filePath) {
    // Tenta di leggere il file JSON specificato. Se la lettura fallisce, mostra un messaggio di errore
    if (!jsonHandler.readJson(filePath, accountContainer)) {
        QMessageBox::critical(this, tr("Errore"), tr("Impossibile aprire il file per la lettura."));
        return;
    }

    // Se la lettura è riuscita, salva il percorso del file e aggiorna la lista degli account
    currentFilePath = filePath;
    updateAccountList();
}

// Metodo per salvare un file JSON
void MainWindow::saveFile(const QString &filePath) {
    // Tenta di scrivere i dati nel file JSON specificato. Se la scrittura fallisce, mostra un messaggio di errore
    if (!jsonHandler.writeJson(filePath, accountContainer)) {
        QMessageBox::critical(this, tr("Errore"), tr("Non è possibile salvare il file."));
        return;
    }

    // Se la scrittura è riuscita, salva il percorso del file
    currentFilePath = filePath;
}

// Metodo per aggiornare la lista degli account
void MainWindow::updateAccountList() {
    accountListWidget->clear();

    for (const Account &account : accountContainer.getAccounts()) {
        QString accountDetails = account.getName() + " - " + account.getDescription();
        accountListWidget->addItem(accountDetails);
    }

    qDebug() << "Dimensione Lista Account: " << accountContainer.getAccounts().size();
}

// Metodo per aggiornare la lista delle transazioni
void MainWindow::updateTransactionList(int accountIndex) {
    qDebug() << "Indice Account: " << accountIndex;
    transactionListWidget->clear();
    QList<Finance*> transactions = accountContainer.getTransactions(accountIndex);
    for (const Finance* transaction : transactions) {
        QString transactionStr;
        if (dynamic_cast<const Expense*>(transaction)) {
            transactionStr = " -" + QString::number(transaction->getAmount()) + ": " + transaction->getDescription();
        } else if (dynamic_cast<const Income*>(transaction)) {
            transactionStr = " +" + QString::number(transaction->getAmount()) + ": " + transaction->getDescription();
        } else if (dynamic_cast<const Loan*>(transaction)) {
            transactionStr = " Prestito " + QString::number(transaction->getAmount()) + ": " + transaction->getDescription();
        }
        transactionListWidget->addItem(transactionStr);
    }
}

// Metodo per aggiornare il saldo
void MainWindow::updateBalance() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        return;
    }
    double balance = 0.0;
    QList<Finance*> transactions = accountContainer.getTransactions(selectedIndex);
    for (const Finance* transaction : transactions) {
        if (dynamic_cast<const Expense*>(transaction)) {
            balance -= transaction->getAmount();
        } else if (dynamic_cast<const Income*>(transaction)) {
            balance += transaction->getAmount();
        } else if (const Loan* loan = dynamic_cast<const Loan*>(transaction)) {
            // In questo caso il prestito riduce il saldo se non è pagato
            if (!loan->isLoanPaid()) {
                balance -= loan->getAmount();
            }
        }
    }
    balanceLabel->setText(tr("Saldo: ") + QString::number(balance));
}
