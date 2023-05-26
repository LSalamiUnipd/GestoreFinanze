#include "mainwindow.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTreeView>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout> // Include this for the vertical box layout
#include <QListWidget> // Include this for the list widget
#include "addaccountdialog.h"
#include "addexpensedialog.h"
#include "addincomedialog.h"

// Costruttore
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createCentralWidget();
}

// Distruttore
MainWindow::~MainWindow() {
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::on_actionSave_As_triggered);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    addAccountAction = new QAction(tr("&Add Account"), this);
    connect(addAccountAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Account_triggered);

    addExpenseAction = new QAction(tr("Add &Expense"), this);
    connect(addExpenseAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Expense_triggered);

    addIncomeAction = new QAction(tr("Add &Income"), this);
    connect(addIncomeAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Income_triggered);

    removeAccountAction = new QAction(tr("&Remove Account"), this);
    connect(removeAccountAction, &QAction::triggered, this, &MainWindow::on_actionRemove_Account_triggered);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(addAccountAction);
    editMenu->addAction(addExpenseAction);
    editMenu->addAction(addIncomeAction);
    editMenu->addSeparator();
    editMenu->addAction(removeAccountAction);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(addAccountAction);
    editToolBar->addAction(addExpenseAction);
    editToolBar->addAction(addIncomeAction);
    editToolBar->addAction(removeAccountAction);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createCentralWidget()
{
    accountTreeView = new QTreeView(this);
    listWidget = new QListWidget(this);

    // Create a layout and add both widgets to it
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(accountTreeView);
    layout->addWidget(listWidget);

    // Create a central widget and set the layout
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);

    // Set the central widget
    setCentralWidget(centralWidget);
}

// Slot per aprire un file JSON
void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("JSON Files (*.json)"));
    if (!filePath.isEmpty()) {
        openFile(filePath);
    }
}

// Slot per salvare il file JSON corrente
void MainWindow::on_actionSave_triggered() {
    if (currentFilePath.isEmpty()) {
        on_actionSave_As_triggered();
    } else {
        saveFile(currentFilePath);
    }
}

// Slot per salvare il file JSON con un nuovo nome
void MainWindow::on_actionSave_As_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File As"), QString(), tr("JSON Files (*.json)"));
    if (!filePath.isEmpty()) {
        saveFile(filePath);
    }
}

// Slot per uscire dall'applicazione
void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

// Slot per aggiungere un nuovo account
void MainWindow::on_actionAdd_Account_triggered() {
    AddAccountDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Account newAccount(dialog.getAccountName());
        accountContainer.addAccount(newAccount);
        updateAccountList();
    }
}

// Slot per aggiungere una nuova spesa
void MainWindow::on_actionAdd_Expense_triggered() {
    int selectedIndex = listWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("No account selected."));
        return;
    }

    AddExpenseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString description = dialog.getExpenseDescription();
        double amount = dialog.getExpenseAmount();
        QDate date = dialog.getExpenseDate();

        Expense newExpense(description, amount, date);
        accountContainer.addExpenseToAccount(selectedIndex, newExpense);
        updateExpenseIncomeList(selectedIndex);
    }
}

// Slot per aggiungere una nuova entrata
void MainWindow::on_actionAdd_Income_triggered() {
    int selectedIndex = listWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("No account selected."));
        return;
    }

    AddIncomeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString description = dialog.getIncomeDescription();
        double amount = dialog.getIncomeAmount();
        QDate date = dialog.getIncomeDate();

        Income newIncome(description, amount, date);
        accountContainer.addIncomeToAccount(selectedIndex, newIncome);
        updateExpenseIncomeList(selectedIndex);
    }
}

// Slot per rimuovere un account
void MainWindow::on_actionRemove_Account_triggered() {
    int selectedIndex = listWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("No account selected."));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Remove Account"), tr("Are you sure you want to remove the selected account?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        accountContainer.removeAccount(selectedIndex);
        updateAccountList();
    }
}

// Metodo per aprire un file JSON
void MainWindow::openFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot open file for reading."));
        return;
    }

    jsonHandler.readJson(file, accountContainer);
    file.close();

    currentFilePath = filePath;
    updateAccountList();
}




// Metodo per salvare un file JSON
void MainWindow::saveFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot open file for writing."));
        return;
    }

    jsonHandler.writeJson(file, accountContainer);
    file.close();

    currentFilePath = filePath;
}


// Metodo per aggiornare la lista degli account
void MainWindow::updateAccountList() {
    listWidget->clear();

    for (const Account &account : accountContainer.getAccounts()) {
        listWidget->addItem(account.getName());
    }
}

// Metodo per aggiornare la lista delle spese e delle entrate
void MainWindow::updateExpenseIncomeList(int accountIndex) {
    listWidget->clear();

    try{
    const Account &account = accountContainer.getAccount(accountIndex);

    for (const Expense &expense : account.getExpenses()) {
        listWidget->addItem(expense.getDescription()); // assuming getDescription is a method in your Expense class
    }

    for (const Income &income : account.getIncomes()) {
        listWidget->addItem(income.getDescription()); // assuming getDescription is a method in your Income class
    }
    } catch (const std::out_of_range& e) {
    qDebug() << "Index out of range: " << e.what();
    }
}
