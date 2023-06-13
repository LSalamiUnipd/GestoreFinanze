#include <QApplication>
#include "mainwindow.h"

// Funzione principale che avvia l'applicazione
int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Crea un'istanza dell'applicazione Qt

    MainWindow mainWindow; // Crea la finestra principale dell'applicazione
    mainWindow.setWindowIcon(QIcon (":/icon.png"));  // Imposta l'icona della finestra principale
    mainWindow.show(); // Mostra la finestra principale

    return app.exec(); // Avvia l'esecuzione dell'applicazione
}
