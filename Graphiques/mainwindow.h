#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QComboBox>
#include <QDockWidget>
#include <QColorDialog>
#include <QFontDialog>
#include <QRandomGenerator>
#include "modelgraphiques.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:


    void creerMenus();
    void creerActions();
    void creerTools();
    void stylesheetSetter(QWidget * w );
public slots:

    void loadCSV();
    void exportIMG();
    void tracerGraphique();
     void aboutGraphiques();
     void customizeColor1();
     void customizeColor2();
     void customizeColor3();
     void customizeFont();
     void customizeFontColor();
     void customizeAppTheme();
     void RestoreAppTheme();
     void ColorFond();
     void ColorAxis();
     void trieASC();
     void trieDESC();
     void EnableGrid();
     void updateQTabCells();
     void setAxisWidth();
     void personnalizeTableWidget();
     void ResetTabStyleSheet();
     void justifyView();
     void CloseDialog();
//     void scaleGraphics();
private:
    Ui::MainWindow *ui;
    QMenuBar *menu_bar;
    QMenu *menu_fichier,*menu_graphiques,*menu_aide;
    QAction *charger,*sauvegarder,*dessiner,*aproposQt,*aproposgraphiques;
    QVBoxLayout *mainLayout;
    QTableWidget * _tablecsv;
     QPushButton * _ok_vf;
    QGridLayout *vf_lay;
    QMovie *mov;
     QString csv;

    QDockWidget * dockerModel,*docker;
    QDialog * loading_verified;
    modelGraphiques *model_graphiques;
};
#endif // MAINWINDOW_H
