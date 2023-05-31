#include <QApplication>
#include "mainwindow.h"

// Funzione principale che avvia l'applicazione
int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Crea un'istanza dell'applicazione Qt

    MainWindow mainWindow; // Crea la finestra principale dell'applicazione
    mainWindow.show(); // Mostra la finestra principale

    return app.exec(); // Avvia l'esecuzione dell'applicazione
}
