#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    _ok_vf = new QPushButton(" OK ");
    ui->setupUi(this);
    QIcon icon(":/icone/mainwindow/bar.svg");
    this->setWindowIcon(icon);
    setWindowTitle(tr("Graphiques"));
    model_graphiques = new modelGraphiques(this);
    setCentralWidget(model_graphiques);
    creerActions();
    creerMenus();
    setAnimated(true);
    loading_verified= new QDialog(this);
    vf_lay = new QGridLayout(loading_verified);
}



void MainWindow::creerActions(){
    QIcon loadIcon(":/icone/mainwindow/load.png");
    QIcon drawIcon(":/icone/mainwindow/draw.png");
    QIcon saveIcon(":/icone/mainwindow/save.png");
    QIcon infoIcon(":/icone/mainwindow/info.png");
    charger = new QAction("Charger",this);
    charger->setShortcut(QKeySequence::Open);
    charger->setIcon(loadIcon);

    sauvegarder = new  QAction(tr("&Sauvegarder le graphique"),this);
    sauvegarder->setShortcut(QKeySequence::Save);
    sauvegarder->setIcon(saveIcon);
    sauvegarder->setDisabled(true);
    dessiner = new  QAction(tr("&Dessiner le graphique"),this);
    dessiner->setIcon(drawIcon);
    dessiner->setShortcut(QKeySequence::Print);
    dessiner->setDisabled(true);
    aproposQt =new QAction(tr("&A propos de Qt"),this);
    aproposQt->setIcon(infoIcon);
    aproposgraphiques = new  QAction(tr("&A propos de graphiques"),this);
    aproposgraphiques->setIcon(infoIcon);

}

void MainWindow::stylesheetSetter(QWidget *w)
{

    std::array<QString, 10> clrs = {"blue","green","red","cyan","gray","yellow","orange","purple","brown","white"};
    std::array<QString, 12> brdr_style = {"none","doted","dashed","groove","inset","outset","dot-dash","solid","double","wave","dot-dot-dash","ridge"};
    std::array<QString, 12> font_families = {"Cantarell","Bold Oblique","Berenis ADF Pro","Cantarell Thin","Courier","GFS Didot","dot-dash","TeX Gyre Chorus",
                                             "Glass TTY VT220","Lato Black","Linux Biolinum Keyboard O","Sawasdee"};
    w->setStyleSheet( "     background-color: "+clrs.at(qrand()%10)+";"
                    "                        border-style: "+brdr_style.at(qrand()%10)+";"
                    "                        border-width: "+QString::fromStdString(std::to_string(qrand()%2))+"px;  border-radius: "+QString::fromStdString(std::to_string(qrand()%20))+"px;"
                    "                        border-color: "+clrs.at(qrand()%10)+";"
                    "                       font-family:"+font_families.at(qrand()%12)+";color: "+clrs.at(qrand()%5)+";font : bold 15px;"
                    "                        min-width: "+QString::fromStdString(std::to_string(qrand()%10))+"em;"
                    "                        padding: 1px;");
}

void MainWindow::creerMenus()
 {
    docker = new QDockWidget(this);
    QIcon exitIcon(":/icone/mainwindow/exit.png");
    QIcon aide(":/icone/mainwindow/support.png");
    menu_fichier = new QMenu(tr("&Fichier"));
          menu_fichier->addAction(charger);
          menu_fichier->addAction(exitIcon,"Quitter",QApplication::quit,QKeySequence::Close);
    menu_graphiques = new QMenu(tr("&Graphiques"));
          menu_graphiques->addAction(dessiner);
          menu_graphiques->addAction(sauvegarder);
    menu_aide = new QMenu(tr("&Aide"));
    menu_aide->setIcon(aide);
          menu_aide->addAction(aproposQt);
          menu_aide->addAction(aproposgraphiques);
    menu_bar = new QMenuBar(this);
    menu_bar->addMenu(menu_fichier);
    menu_bar->addMenu(menu_graphiques);
    menu_bar->addMenu(menu_aide);
    this->setMenuBar(menu_bar);

    _tablecsv = new QTableWidget(this);
    _tablecsv->setGeometry(10,50,300,900);
    docker->setWidget(_tablecsv);
    addDockWidget(Qt::LeftDockWidgetArea,docker);




    QObject::connect(charger,&QAction::triggered,this,&MainWindow::loadCSV);
    QObject::connect(dessiner,&QAction::triggered,this,&MainWindow::tracerGraphique);
    QObject::connect(aproposQt,&QAction::triggered,this,&QApplication::aboutQt);
    QObject::connect(aproposgraphiques,&QAction::triggered,this,&MainWindow::aboutGraphiques);
    QObject::connect(sauvegarder,&QAction::triggered,this,&MainWindow::exportIMG);
    QObject::connect(model_graphiques->costum1,&QPushButton::clicked,this,&MainWindow::customizeColor1);
    QObject::connect(model_graphiques->costum2,&QPushButton::clicked,this,&MainWindow::customizeColor2);
    QObject::connect(model_graphiques->costum3,&QPushButton::clicked,this,&MainWindow::customizeColor3);
    QObject::connect(model_graphiques->fontButton,&QPushButton::clicked,this,&MainWindow::customizeFont);
    QObject::connect(model_graphiques->_triMode,&QPushButton::clicked,this,&MainWindow::trieASC);
    QObject::connect(model_graphiques->_triMode2,&QPushButton::clicked,this,&MainWindow::trieDESC);
    QObject::connect(model_graphiques->fondClrButton,&QPushButton::clicked,this,&MainWindow::ColorFond);
    QObject::connect(model_graphiques->axescolorbtn,&QPushButton::clicked,this,&MainWindow::ColorAxis);
    QObject::connect(model_graphiques->grilleCheck,&QCheckBox::stateChanged,this,&MainWindow::EnableGrid);
    QObject::connect(model_graphiques->penwidth_Ratio,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&MainWindow::setAxisWidth);
    QObject::connect(_tablecsv,&QTableWidget::cellDoubleClicked,this,&MainWindow::updateQTabCells);
    QObject::connect(model_graphiques->theme_tabBtn,&QPushButton::clicked,this,&MainWindow::personnalizeTableWidget);
    QObject::connect(model_graphiques->theme_tabBtnReset,&QPushButton::clicked,this,&MainWindow::ResetTabStyleSheet);
    QObject::connect(model_graphiques->justify_grp,&QPushButton::clicked,this,&MainWindow::justifyView);
    QObject::connect(model_graphiques->FontColor,&QPushButton::clicked,this,&MainWindow::customizeFontColor);
    QObject::connect(model_graphiques->theme2,&QPushButton::clicked,this,&MainWindow::customizeAppTheme);
    QObject::connect(model_graphiques->theme,&QPushButton::clicked,this,&MainWindow::RestoreAppTheme);
    QObject::connect(_ok_vf,&QPushButton::clicked,this,&MainWindow::CloseDialog);
//    QObject::connect(model_graphiques->largeuredit,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&MainWindow::scaleGraphics);
//    QObject::connect(model_graphiques->hauteruedit,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&MainWindow::scaleGraphics);
}

void MainWindow::loadCSV()
{
    loading_verified->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
    loading_verified->setFixedSize(230,300);

        _tablecsv->setUpdatesEnabled(true);
    csv = QFileDialog::getOpenFileName(this,tr("charger un fichier"),this->windowFilePath(),
                                             tr("data File(*.csv *.xlsx)"));
    QFile f(csv);
    model_graphiques->lire_CSV(csv,_tablecsv,dessiner,sauvegarder);

    if (f.exists()){
        setWindowTitle("Graphiques["+csv.split('/').last()+"]");

    mov = new QMovie(":/icone/aide/verified");
    QLabel * movi_lab = new QLabel;
    mov->start();
    movi_lab->setMovie(mov);
    vf_lay->addWidget(movi_lab,0,0,Qt::AlignTop);
    vf_lay->addWidget(_ok_vf,1,0,Qt::AlignBottom);
    loading_verified->exec();
    _tablecsv->update();
}


}

void MainWindow::exportIMG()
{
    QString exportimage = QFileDialog::getSaveFileName(this,tr("&Choisir l'endroit de sauvegarde"),this->windowFilePath(),tr("data File(*.jpg , *.png)"));
    QPixmap pix;
    model_graphiques->saveToImg(pix,exportimage);
}

void MainWindow::tracerGraphique()
{
    if(model_graphiques->_typesGraphiques->currentData() == modelGraphiques::Points){
    model_graphiques->drawPLB();
   }else if(model_graphiques->_typesGraphiques->currentData() == modelGraphiques::Line){
    model_graphiques->drawLines();
   }else {
    model_graphiques->drawBars();
}
if(model_graphiques->grilleCheck->isChecked())    model_graphiques->showGrid();
}

void MainWindow::aboutGraphiques()
{
QDialog * aproposgraphiques = new QDialog(this);
QGridLayout *about = new QGridLayout(aproposgraphiques);
aproposgraphiques->setFixedSize(600,200);

    QLabel *aboutThis= new QLabel(tr("Cette application a été réalisé par Djamel MANADI pour \nun projet de Qt L3 informatique"));
    aboutThis->setStyleSheet("font-family: LM Sans Demi Cond 10;");

    QImage icn(":/icone/mainwindow/bar.svg");
    QPixmap pix_img;
    pix_img.convertFromImage(icn);
//    pix_img.load(":/icone/aide/verified.gif");
    pix_img.setDevicePixelRatio(3);
    QLabel * imaglab = new QLabel;
    imaglab->setPixmap(pix_img);

about->addWidget(aboutThis,0,1,Qt::AlignRight);
about->addWidget(imaglab,0,0,Qt::AlignLeft);
        aproposgraphiques->exec();
}

void MainWindow::customizeColor1()
{
QColorDialog *c1 = new QColorDialog(Qt::red,this);
QString c1Color = c1->getColor().name();
QColor c1c(c1Color);
model_graphiques->costum1->setStyleSheet("background-color:"+c1Color+";");
model_graphiques->setclrArrValue(0,c1c);
}


void MainWindow::customizeColor2()
{
QColorDialog *c2 = new QColorDialog(Qt::green,this);
QString c2Color = c2->getColor().name();
QColor c2c(c2Color);
model_graphiques->costum2->setStyleSheet("background-color:"+c2Color+";");
model_graphiques->setclrArrValue(1,c2c);
}


void MainWindow::customizeColor3()
{

QColorDialog *c3 = new QColorDialog(Qt::blue,this);
QString c3Color = c3->getColor().name();
QColor c3c(c3Color);
model_graphiques->costum3->setStyleSheet("background-color:"+c3Color+";");
model_graphiques->setclrArrValue(2,c3c);
}

void MainWindow::customizeFont()
{
//    qApp->setStyleSheet("MainWindow{background-color:lightblack;border : 3px solid lightgray}"
//                        "QTableWidget{background-color:black ; border : 3px solid yellow ; color : white}");
QFontDialog *f = new QFontDialog(this);
bool ok;
QFont fFont = f->getFont(&ok , this);
QString fontName = fFont.toString();
model_graphiques->fontButton->setText(fFont.toString().split(',').first());
qApp->setStyleSheet("QWidget {font-family :"+fFont.toString().split(',').first()+";}");

}

void MainWindow::customizeFontColor()
{
    QColorDialog *fc = new QColorDialog(Qt::red,this);
    QString fcColor = fc->getColor().name();
    QColor cfc(fcColor);
    qApp->setStyleSheet("QWidget {color :"+fcColor+";}");
    model_graphiques->FontColor->setStyleSheet("background-color:"+fcColor+";");
}

void MainWindow::customizeAppTheme()
{
qApp->setStyleSheet("QPushButton:hover {  background-color: gray;}"
                    "QPushButton{ "
                    "padding: 10px 15px;"
                    "font-size: 15px;"
                    "background-color:lightgray;"
                     "border-style : double;"
                    "border-radius: 15px;}"
                     "QPushButton:pressed {background-color: #3e8e41;border-radius: 10px;border-color:lightgray;border-width:6px;}");

}

void MainWindow::RestoreAppTheme()
{
    qApp->setStyleSheet("");
}

void MainWindow::ColorFond()
{

    QColorDialog *cf = new QColorDialog(Qt::red,this);
    QString cfColor = cf->getColor().name();
    QColor cfd(cfColor);
    model_graphiques->fondClrButton->setStyleSheet("background-color:"+cfColor+";");
    model_graphiques->getGraphics().setBackgroundBrush(cfd);
//    return cfColor;
}

void MainWindow::ColorAxis()
{
    QColorDialog *ca = new QColorDialog(Qt::red,this);
    QString caColor = ca->getColor().name();

    model_graphiques->axescolorbtn->setStyleSheet("background-color:"+caColor+";");
    model_graphiques->penAxis.setColor(caColor);
}

void MainWindow::trieASC()
{
    update();
    _tablecsv->sortItems(0,Qt::SortOrder::AscendingOrder);
}
void MainWindow::trieDESC(){
    update();
    _tablecsv->sortItems(0,Qt::SortOrder::DescendingOrder);
}

void MainWindow::EnableGrid()
{
    if(model_graphiques->grilleCheck->isChecked())    model_graphiques->showGrid();
    if(!model_graphiques->grilleCheck->isChecked())     model_graphiques->hideGrid();
}


void MainWindow::updateQTabCells()
{
    model_graphiques->updateWordList(_tablecsv);
}

void MainWindow::setAxisWidth()
{
   int w = model_graphiques->penwidth_Ratio->value();
   model_graphiques->penAxis.setWidth(w);
}

void MainWindow::personnalizeTableWidget()
{
    stylesheetSetter(_tablecsv);

}

void MainWindow::ResetTabStyleSheet()
{
    _tablecsv->setStyleSheet("");
}

void MainWindow::justifyView()
{
    model_graphiques ->getGraphics().fitInView(model_graphiques->getScene().itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
}

void MainWindow::CloseDialog()
{
    loading_verified->close();
    mov->stop();
    delete mov;
}



MainWindow::~MainWindow()
{
    delete ui;
}


