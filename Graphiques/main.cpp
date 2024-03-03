#include "mainwindow.h"
#include <QTranslator>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if(translator.load(":/home/etudiant/Bureau/SE 6/F.Coef/D.INTERFACES.GRAPHIQUES X3/projet_note/Graphiques/TraductionfrEN.qm")) {
    a.installTranslator(&translator);
    }
    a.installTranslator(&translator);
    MainWindow w;
    w.show();
    return a.exec();
}


