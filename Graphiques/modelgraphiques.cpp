#include "modelgraphiques.h"

//Constructor init
modelGraphiques::modelGraphiques(QWidget *parent)
{
    _taille = 0;
    _type = Points;
    _nb_Y = 0;
    _nb_rows = 0 ;
    _max_val = 0;
    _min_val = 0;

    penAxis.setColor(Qt::gray);
    penAxis.setWidth(4);
    mainlayout = new QGridLayout(this);

    setAutoFillBackground(Qt::transparent);
    creerTools();
    paintGraphicsEngine();
}

//void modelGraphiques::wheelEvent(QWheelEvent *e)
//{
//    if(e->angleDelta().y() > 0) // haut
//            graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
//      else if(e->angleDelta().y() < 0) // bas
//            graphiques->fitInView(graphiques->geometry(),Qt::AspectRatioMode::KeepAspectRatio);

//}

//CREATING TOOLS
void modelGraphiques::creerTools(){
    QIcon DESCicon(":/icone/aide/desc.png");
    QIcon ASCicon(":/icone/aide/Asc.png");
    QLabel *formGroup = new QLabel;
    QFormLayout *toolsLayout = new QFormLayout;

    type = new QLabel(tr("&Type:"));
    _typesGraphiques = new QComboBox(type);
    _typesGraphiques->addItem("Points",modelGraphiques::Points);
    _typesGraphiques->addItem("Lignes",modelGraphiques::Line);
    _typesGraphiques->addItem("Barres",modelGraphiques::Bars);
    type->setBuddy(_typesGraphiques);

    _couleur1 = new QLabel(tr("&Couleur 1:"));
   costum1 = new QPushButton;
   costum1->setStyleSheet("background-color:red;");
    _couleur1->setBuddy(costum1);

    _couleur2 = new QLabel(tr("&Couleur 2:"));
   costum2 = new QPushButton;
   costum2->setStyleSheet("background-color:green;");
    _couleur2->setBuddy(costum2);

    _couleur3 = new QLabel(tr("&Couleur 3:"));
   costum3 = new QPushButton;
   costum3->setStyleSheet("background-color:blue;");
    _couleur3->setBuddy(costum3);

    police = new QLabel(tr("Police:"));
    fontButton = new QPushButton;
    FontColor = new QPushButton;
    FontColor->setStyleSheet("background-color:black;");
    QString fn =QFont("Ubuntu").toString().split(',').first();
    fontButton->setText(fn);
//    police->setBuddy(fontButton);


    Trier_lab = new QLabel(tr("Trier Par :"));
    _triMode = new QPushButton;
    _triMode->setStyleSheet("background-color:transparent;");
    _triMode->setIcon(DESCicon);
    _triMode2 = new QPushButton;
    _triMode2->setStyleSheet("background-color:transparent;");
    _triMode2->setIcon(ASCicon);

    largeur = new QLabel(tr("&Largeur:"));
    largeuredit = new QSpinBox;
    largeuredit->setMaximum(1024);
    largeuredit->setValue(800);
    largeur->setBuddy(largeur);


    hauteur= new QLabel(tr("&Hauteur:"));
    hauteruedit = new QSpinBox;
    hauteruedit->setMaximum(1024);
    hauteruedit->setValue(600);
    hauteur->setBuddy(hauteruedit);


    margeX= new QLabel(tr("&Marge x:"));
    margeXedit = new QSpinBox;
    margeXedit->setValue(20);
    margeX->setBuddy(margeXedit);

    margY= new QLabel(tr("&Marge y:"));
    margeYedit = new QSpinBox;
    margeYedit->setValue(20);
    margY->setBuddy(margeYedit);

    _couleurFond= new QLabel(tr("&Couleur de Fond:"));
    fondClrButton = new QPushButton;
    fondClrButton->setStyleSheet("background-color:white;");
    _couleurFond->setBuddy(fondClrButton);

    _couleurAxes= new QLabel(tr("Couleur des axes / Epaisseur:"));
    axescolorbtn = new QPushButton;
    axescolorbtn->setStyleSheet("background-color:gray;");
        penwidth_Ratio = new QSpinBox;
        penwidth_Ratio->setMaximum(8);
        penwidth_Ratio->setMinimum(1);
        penwidth_Ratio->setValue(3);
//    _couleurAxes->setBuddy(axescolorbtn);

    pasX= new QLabel(tr("&Pas X:"));
    pasXedit = new QSpinBox;
    pasXedit->setValue(1);
    pasX->setBuddy(pasXedit);

    pasY= new QLabel(tr("&Pas Y:"));
    pasYedit = new QSpinBox;
    pasYedit->setValue(1);
    pasY->setBuddy(pasYedit);

    Grille= new QLabel(tr("&Grille :"));
    grilleCheck = new QCheckBox;
    grilleCheck->setCheckState(Qt::CheckState::Unchecked);
    grilleCheck->setDisabled(true);
    Grille->setBuddy(grilleCheck);

    QLabel * tab_lab = new QLabel(tr("Personnalizer le tableur : "));
    theme_tabBtn = new QPushButton;
    theme_tabBtn->setIcon(QIcon(":/icone/aide/Qtab_theme.png"));
    theme_tabBtnReset = new QPushButton;
    theme_tabBtnReset->setIcon(QIcon(":/icone/aide/Qtab_themeReset.png"));

    QLabel * justify_lab = new QLabel(tr("Justifier la vue : "));
    justify_grp = new QPushButton;
    justify_grp->setIcon(QIcon(":/icone/aide/resize.png"));

    QLabel * theme_lab = new QLabel(tr("Thème : "));
    theme = new QPushButton;
    theme->setText("Default");
    theme2 = new QPushButton;
    theme2->setText("Apparence 2");

    QGridLayout *tri_lay = new QGridLayout;
    QGridLayout *customPen_lay = new QGridLayout;
    QGridLayout *custom_tab_lay = new QGridLayout;
    QGridLayout *customFont = new QGridLayout;
    QGridLayout *customThemeApp = new QGridLayout;
//    ratio_lab = new QLabel(tr("&Zoom Dedans :"));

//    ratio_lab->setBuddy(bigRatio);

    toolsLayout->addRow(type,_typesGraphiques);
    toolsLayout->addRow(_couleur1,costum1);
    toolsLayout->addRow(_couleur2,costum2);
    toolsLayout->addRow(_couleur3,costum3);
    customFont->addWidget(fontButton,0,0);
    customFont->addWidget(FontColor,0,1);
    toolsLayout->addRow(police,customFont);

    tri_lay->addWidget(_triMode,0,0);
    tri_lay->addWidget(_triMode2,0,1);
    toolsLayout->addRow(Trier_lab,tri_lay);
    toolsLayout->addRow(largeur,largeuredit);
    toolsLayout->addRow(hauteur,hauteruedit);
    toolsLayout->addRow(margeX,margeXedit);
    toolsLayout->addRow(margY,margeYedit);
    toolsLayout->addRow(_couleurFond,fondClrButton);

    customPen_lay->addWidget(axescolorbtn,0,0);
    customPen_lay->addWidget(penwidth_Ratio,0,1);
    toolsLayout->addRow(_couleurAxes,customPen_lay);
    toolsLayout->addRow(pasX,pasXedit);
    toolsLayout->addRow(pasY,pasYedit);
    toolsLayout->addRow(Grille,grilleCheck);

    custom_tab_lay->addWidget(theme_tabBtn,0,0);
    custom_tab_lay->addWidget(theme_tabBtnReset,0,1);
    toolsLayout->addRow(tab_lab,custom_tab_lay);
    toolsLayout->addRow(justify_lab,justify_grp);
    customThemeApp->addWidget(theme,0,0);
    customThemeApp->addWidget(theme2,0,1);
    toolsLayout->addRow(theme_lab,customThemeApp);

    toolsLayout->setAlignment(Qt::AlignLeft);

    formGroup->setLayout(toolsLayout);
   mainlayout->addWidget(formGroup,0,0);

}





void modelGraphiques::saveToImg(QPixmap &pix, QString &filename)
{

    pix = graphiques->grab(graphiques->rect());
    pix.save(filename,"png",100);
}




void modelGraphiques::lire_CSV(const QString &csv,QTableWidget *tab,QAction * dessAc,QAction * saveAc)
{
    QFile fichier(csv);

    tab->setAutoFillBackground(true);
       if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

         if(fichier.exists()){

             if(_nb_rows!=0){

             for (size_t i=0; i<= _nb_rows ;i++) {
                     _wordList.at(i).clear();
                    tab->removeRow(i+1);
             }

            }
             _taille = 0;
            while (!fichier.atEnd()) {

                QByteArray line = fichier.readLine();
                foreach( const QByteArray &value, line.split(',') ) {

                 _wordList.at(_taille)<<value;
               }
                _taille++;
            }

            size_t ss(_taille);int j(0);
            QString str("");


            tab->setRowCount(static_cast<int>(ss-1));
            tab->setColumnCount(_wordList.at(0).size());
            while(j< _wordList.at(0).size()){
                        QTableWidgetItem *headerItem = new QTableWidgetItem(_wordList.at(0).at(j));
                        tab->setHorizontalHeaderItem(j,headerItem);
                        j++;
                        }
             _nb_rows =  static_cast<unsigned short int>(_taille);
             _nb_Y = 0;
             _max_val = 0;
             _min_val = 0;
            for (size_t i=1;i<ss;++i) {
                j=0;

                while(j< _wordList.at(0).size()){
                QTableWidgetItem *XYZItem = new QTableWidgetItem(_wordList.at(i).at(j));

                if( j!=0 && _wordList.at(i).at(j).toDouble() > _max_val) { _max_val = _wordList.at(i).at(j).toDouble()+1;}
                if(j!=0 && _wordList.at(i).at(j).toDouble() < _min_val) { _min_val = _wordList.at(i).at(j).toDouble()-1; }
                if(i==1) _nb_Y++;
                tab->setItem(static_cast<int>(i-1) ,j,XYZItem);
                j++;
                }
             }
            dessAc->setDisabled(false);
            saveAc->setDisabled(false);
            grilleCheck->setDisabled(false);
    }


}

void modelGraphiques::updateWordList(QTableWidget *tab)
{
//    for (size_t i=1; i<= _nb_rows ;i++) {
//        _wordList.at(i).clear();
//    }
std::array<QStringList,200> _wordListTemp;
    for (size_t i=1;i <= _nb_rows ;i++) {
            for(int j=0 ; j <= _nb_Y/*static_cast<int>(t)*/ ;j++ ){

                _wordListTemp.at(i) <<   tab->itemAt(static_cast<int>(i),j)->text();
             }
        _wordList.at(i).swap(_wordListTemp.at(i));
     }

}

void modelGraphiques::drawPLB( /*QColor const c*/)
{
    axis_xnums.resize(0);
    axis__ynums.resize(0);
    axis_x_nums.resize(0);
    axis_y_nums.resize(0);

    scene->clear();
//    graphiques->viewportUpdateMode();

        QFont ArialFont("Arial", 30, QFont::Thin);
        QString s(QString::fromStdString(std::to_string(_nb_Y-1)));
        QString r(QString::fromStdString(std::to_string(_nb_rows-1)));
        QString m(QString::fromStdString(std::to_string(_max_val-1)));
         QString min(QString::fromStdString(std::to_string(_min_val+1)));


        pix_item = scene->addPixmap(pix_mark);
        pix_item->setPos(0,(height()/2)-600);
        pix_item->setOpacity(0.4);


        // COORDONNEES > 100 :
        if(_max_val>100) {

            QFont serifFont("Glass TTY VT220", 30, QFont::Bold);
           scene->addText("U A ' Faculté des sciences \n Nb Y :"+s+"\n Rows :"+r+"\n Max val :"+m+"\n min val : "+min ,serifFont);

            for(auto i=0; i<_max_val*10;i+=100){
               AxisX = scene->addLine((width()/2)+i,(height()/2),(width()/2)+i,(height()/2)-5,penAxis);
               AxisY = scene->addLine((width()/2),(height()/2)-i,(width()/2)+5,(height()/2)-i,penAxis);
            }

            if(_min_val < -100){
              for(auto i=0; i<_min_val*-(10);i+=100){
                               AxisX = scene->addLine((width()/2)-i,(height()/2),(width()/2)-i,(height()/2)-5,penAxis);
                             AxisY = scene->addLine((width()/2),(height()/2)+i,(width()/2)+5,(height()/2)+i,penAxis);
                  }
              } else {
                for(auto i=0; i< (-_min_val*100) ;i+=100){
                                 AxisX = scene->addLine((width()/2)-i,(height()/2),(width()/2)-i,(height()/2)-5,penAxis);
                                 AxisY = scene->addLine((width()/2),-(height()/2)-i,(width()/2)+5,height(),penAxis);
                    }
                for (int i = 0 ; i <= (-_min_val) ;i+=10) {
                    axis_xnums.push_back(scene->addText(QString::fromStdString(std::to_string(-i/10)),ArialFont));
                    axis_xnums.at(i/10)->setPos((width()/2)-(i*10),height()/2);
                    axis__ynums.push_back(scene->addText(QString::fromStdString(std::to_string(-i*2)),ArialFont));
                    axis__ynums.at(i/10)->setPos(width()/2,(height()/2)+(i*20));
                }
              }
//                line = scene->addLine(-400,(height()/2),width()+400,(height()/2),penAxis);
//                line = scene->addLine((width()/2),-height()-400,(width()/2),height()+400,penAxis);

            graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
            line = scene->addLine(scene->sceneRect().left(),(graphiques->height()/2),scene->sceneRect().right(),(graphiques->height()/2),penAxis);
            line = scene->addLine(width()/2,scene->sceneRect().top(),width()/2,scene->sceneRect().bottom(),penAxis);

                for (int i = 0 ; i <= (_max_val/10) ;i++) {
                      axis_x_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i)),ArialFont));
                      axis_x_nums.at(i)->setPos((width()/2)+(i*100),height()/2);
//                       axis_xnums.push_back(scene->addText(QString::fromStdString(std::to_string(-i))));
//                       axis_xnums.at(i)->setPos((width()/2)-(i*100),height()/2);

                       axis_y_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i*10)),ArialFont));
                       axis_y_nums.at(i)->setPos(width()/2,(height()/2)-(i*100));
//                        axis__ynums.push_back(scene->addText(QString::fromStdString(std::to_string(-i*10))));
//                        axis__ynums.at(i)->setPos(width()/2,(height()/2)+(i*100));
                }

            _pen1.setWidth(20);

            for (int j = 1 ; j < _nb_Y ; j++) {
                 _pen1.setColor(clrArr.at(static_cast<size_t>(j-1)));
                  for (size_t i=1;i<_nb_rows;i++) {
                      scene->addLine((width()/2)+(_wordList.at(i).at(0).toDouble()*100),
                                 (height()/2)-(_wordList.at(i).at(j).toDouble()*10),
                                 (width()/2)+(_wordList.at(i).at(0).toDouble())*100,
                                 (height()/2)-(_wordList.at(i).at(j).toDouble()*10),_pen1);

                 }
               }
//            graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
//            graphiques->adjustSize();
        }
        // COORDONNEES < 100 :
        else {

            QFont serifFont("Glass TTY VT220", 18, QFont::Bold);
           scene->addText("U A ' Faculté des sciences \n Nb Y :"+s+"\n Rows :"+r+"\n Max val :"+m+"\n min val : "+min ,serifFont);
        for(auto i=0; i<(_max_val-1)*100;i+=100){
             AxisX = scene->addLine((width()/2)+i,(height()/2),(width()/2)+i,(height()/2)-5,penAxis);
             AxisX = scene->addLine((width()/2)-i,(height()/2),(width()/2)-i,(height()/2)-5,penAxis);
             AxisY = scene->addLine((width()/2),(height()/2)+i,(width()/2)+5,(height()/2)+i,penAxis);
            AxisY = scene->addLine((width()/2),(height()/2)-i,(width()/2)+5,(height()/2)-i,penAxis);
         }


        for (int i = 0 ; i <= _max_val ;i++) {
              axis_x_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i)),ArialFont));
              axis_x_nums.at(i)->setPos((width()/2)+(i*100),height()/2);

               axis_y_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i)),ArialFont));
               axis_y_nums.at(i)->setPos(width()/2,(height()/2)-(i*100));
        }
        for (int i = 0 ; i <= (-_min_val) ;i++) {
            axis_xnums.push_back(scene->addText(QString::fromStdString(std::to_string(-i)),ArialFont));
            axis_xnums.at(i)->setPos((width()/2)-(i*100),height()/2);
            axis__ynums.push_back(scene->addText(QString::fromStdString(std::to_string(-i)),ArialFont));
            axis__ynums.at(i)->setPos(width()/2,(height()/2)+(i*100));
        }


        graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
        line = scene->addLine(scene->sceneRect().left(),(graphiques->height()/2),scene->sceneRect().right(),(graphiques->height()/2),penAxis);
        line = scene->addLine(width()/2,scene->sceneRect().top(),width()/2,scene->sceneRect().bottom(),penAxis);

        _pen1.setWidth(10);

          for (int j = 1 ; j < _nb_Y ; j++) {
               _pen1.setColor(clrArr.at(static_cast<size_t>(j-1)));
                for (size_t i=1;i<_nb_rows;i++) {
                    scene->addLine((width()/2)+(_wordList.at(i).at(0).toDouble()*100),
                               (height()/2)-(_wordList.at(i).at(j).toDouble()*100),
                               (width()/2)+(_wordList.at(i).at(0).toDouble()*100),
                               (height()/2)-(_wordList.at(i).at(j).toDouble()*100),_pen1);

               }
             }

        }
}

void modelGraphiques::drawLines()
{
    axis_xnums.resize(0);
    axis__ynums.resize(0);
    axis_x_nums.resize(0);
    axis_y_nums.resize(0);
    scene->clear();

        QFont ArialFont("Arial", 30, QFont::Thin);
        QFont serifFont("Glass TTY VT220", 15, QFont::Bold);
        QString s(QString::fromStdString(std::to_string(_nb_Y-1)));
        QString r(QString::fromStdString(std::to_string(_nb_rows-1)));
        QString m(QString::fromStdString(std::to_string(_max_val-1)));
        QString min(QString::fromStdString(std::to_string(_min_val+1)));


         pix_item = scene->addPixmap(pix_mark);
        pix_item->setPos(0,(height()/2)-600);
        pix_item->setOpacity(0.4);


        // COORDONNEES > 100 :
        if(_max_val>100) {

            QFont serifFont("Glass TTY VT220", 30, QFont::Bold);
           scene->addText("U A ' Faculté des sciences \n Nb Y :"+s+"\n Rows :"+r+"\n Max val :"+m+"\n min val : "+min+"\n" ,serifFont);

            for(auto i=0; i<_max_val*10;i+=100){
               AxisX = scene->addLine((width()/2)+i,(height()/2),(width()/2)+i,(height()/2)-5,penAxis);

               AxisY = scene->addLine((width()/2),(height()/2)-i,(width()/2)+5,(height()/2)-i,penAxis);
            }
          if(_min_val < -100){
            for(auto i=0; i<_min_val*-(10);i+=100){
                             AxisX = scene->addLine((width()/2)-i,(height()/2),(width()/2)-i,(height()/2)-5,penAxis);
                           AxisY = scene->addLine((width()/2),(height()/2)+i,(width()/2)+5,(height()/2)+i,penAxis);
                }
            for (int i = 0 ; i <= (-_min_val) ;i++) {
                axis_xnums.push_back(scene->addText(QString::fromStdString(std::to_string(-i)),ArialFont));
                axis_xnums.at(i)->setPos((width()/2)-(i*100),height()/2);
                axis__ynums.push_back(scene->addText(QString::fromStdString(std::to_string(-i)),ArialFont));
                axis__ynums.at(i)->setPos(width()/2,(height()/2)+(i*200));
            }
            } else {
              for(auto i=0; i< (-_min_val*100) ;i+=100){
                               AxisX = scene->addLine((width()/2)-i,(height()/2),(width()/2)-i,(height()/2)-5,penAxis);
                             AxisY = scene->addLine((width()/2),-(height()/2)-i,(width()/2)+5,height(),penAxis);
                  }
              for (int i = 0 ; i <= (-_min_val) ;i+=10) {
                  axis_xnums.push_back(scene->addText(QString::fromStdString(std::to_string(-i/10)),ArialFont));
                  axis_xnums.at(i/10)->setPos((width()/2)-(i*10),height()/2);
                  axis__ynums.push_back(scene->addText(QString::fromStdString(std::to_string(-i*2)),ArialFont));
                  axis__ynums.at(i/10)->setPos(width()/2,(height()/2)+(i*20));
              }
            }

//              line = scene->addLine(0,(height()/2),width()+400,(height()/2),penAxis);
//                line = scene->addLine((width()/2),-height()-400,(width()/2),height(),penAxis);

          graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
          line = scene->addLine(scene->sceneRect().left(),(graphiques->height()/2),scene->sceneRect().right(),(graphiques->height()/2),penAxis);
          line = scene->addLine(width()/2,scene->sceneRect().top(),width()/2,scene->sceneRect().bottom(),penAxis);

                for (int i = 0 ; i <= (_max_val/10) ;i++) {
                      axis_x_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i)),ArialFont));
                      axis_x_nums.at(i)->setPos((width()/2)+(i*100),height()/2);
//                       axis_xnums.push_back(scene->addText(QString::fromStdString(std::to_string(-i))));
//                       axis_xnums.at(i)->setPos((width()/2)-(i*100),height()/2);

                       axis_y_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i*10)),ArialFont));
                       axis_y_nums.at(i)->setPos(width()/2,(height()/2)-(i*100));
//                        axis__ynums.push_back(scene->addText(QString::fromStdString(std::to_string(-i*10))));
//                        axis__ynums.at(i)->setPos(width()/2,(height()/2)+(i*100));
                }


                // LINES
                    _pen1.setWidth(3);
                for (int j = 1 ; j < _nb_Y ; j++) {
                    _pen1.setColor(clrArr.at(static_cast<size_t>(j-1)));
                    for (size_t i=1;i<_nb_rows;i++) {

                        // si Dernier point Y #fin de laison
                        if(i==(_nb_rows-1)) {
                            scene->addLine((width()/2)+(_wordList.at(i).at(0).toDouble()*10),
                                               (height()/2)-(_wordList.at(i).at(j).toDouble()*10),

                                               (width()/2)+(_wordList.at(i).at(0).toDouble()*10),
                                               (height()/2)-(_wordList.at(i).at(j).toDouble())*10,_pen1);
            graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
                        }
                        //Sinon
                        else {
                            scene->addLine((width()/2)+(_wordList.at(i).at(0).toDouble())*100,
                                               (height()/2)-(_wordList.at(i).at(j).toDouble())*10,

                                               (width()/2)+(_wordList.at(i+1).at(0).toDouble())*100,
                                               (height()/2)-(_wordList.at(i+1).at(j).toDouble())*10,_pen1);
                        }
                    }
                }
//                    graphiques->adjustSize();

        }
            // COORDONNEES < 100 :
        else {
           QFont serifFont("Glass TTY VT220", 18, QFont::Bold);
           scene->addText("U A ' Faculté des sciences \n Nb Y :"+s+"\n Rows :"+r+"\n Max val :"+m+"\n min val : "+min+"\n",serifFont);

            // AXES
            for(auto i=0; i<(_max_val-1)*100;i+=100){
             AxisX = scene->addLine((width()/2)+i,(height()/2),(width()/2)+i,(height()/2)-5,penAxis);
             AxisX = scene->addLine((width()/2)-i,(height()/2),(width()/2)-i,(height()/2)-5,penAxis);
             AxisY = scene->addLine((width()/2),(height()/2)+i,(width()/2)+5,(height()/2)+i,penAxis);
             AxisY = scene->addLine((width()/2),(height()/2)-i,(width()/2)+5,(height()/2)-i,penAxis);
             }
//            line = scene->addLine(0,(height()/2),width(),(height()/2),penAxis);
//            line = scene->addLine((width()/2),-400,(width()/2),height()+400,penAxis);

            for (int i = 0 ; i <= _max_val ;i++) {
                  axis_x_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i)),ArialFont));
                  axis_x_nums.at(i)->setPos((width()/2)+(i*100),height()/2);

                   axis_y_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i)),ArialFont));
                   axis_y_nums.at(i)->setPos(width()/2,(height()/2)-(i*100));

            }
            for (int i = 0 ; i <= (-_min_val) ;i++) {
                axis_xnums.push_back(scene->addText(QString::fromStdString(std::to_string(-i)),ArialFont));
                axis_xnums.at(i)->setPos((width()/2)-(i*100),height()/2);
                axis__ynums.push_back(scene->addText(QString::fromStdString(std::to_string(-i)),ArialFont));
                axis__ynums.at(i)->setPos(width()/2,(height()/2)+(i*100));
            }
            graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
            line = scene->addLine(scene->sceneRect().left(),(graphiques->height()/2),scene->sceneRect().right(),(graphiques->height()/2),penAxis);
            line = scene->addLine(width()/2,scene->sceneRect().top(),width()/2,scene->sceneRect().bottom(),penAxis);

        // LINES
        //    _pen1.setColor(c.name());
            _pen1.setWidth(3);
        for (int j = 1 ; j < _nb_Y ; j++) {
            _pen1.setColor(clrArr.at(static_cast<size_t>(j-1)));
            for (size_t i=1;i<_nb_rows;i++) {


                if(i==(_nb_rows-1)) {
                    scene->addLine((width()/2)+(_wordList.at(i).at(0).toDouble()*100),
                                       (height()/2)-(_wordList.at(i).at(j).toDouble()*100),

                                       (width()/2)+(_wordList.at(i).at(0).toDouble()*100),
                                       (height()/2)-(_wordList.at(i).at(j).toDouble()*100),_pen1);

                }else {
                    scene->addLine((width()/2)+(_wordList.at(i).at(0).toDouble()*100),
                                       (height()/2)-(_wordList.at(i).at(j).toDouble()*100),

                                       (width()/2)+(_wordList.at(i+1).at(0).toDouble()*100),
                                       (height()/2)-(_wordList.at(i+1).at(j).toDouble()*100),_pen1);
                }
               }
            }
//        graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
        }

}

void modelGraphiques::drawBars()
{
    axis_xnums.resize(0);
    axis__ynums.resize(0);
    axis_x_nums.resize(0);
    axis_y_nums.resize(0);
    scene->clear();
//    QPen pen(Qt::gray);
//        pen.setWidth(4);
        QFont ArialFont("Arial", 30, QFont::Thin);
        QFont serifFont("Glass TTY VT220", 15, QFont::Bold);
        QString s(QString::fromStdString(std::to_string(_nb_Y-1)));
        QString r(QString::fromStdString(std::to_string(_nb_rows-1)));
        QString m(QString::fromStdString(std::to_string(_max_val-1)));
        QString min(QString::fromStdString(std::to_string(_min_val+1)));
        pix_item = scene->addPixmap(pix_mark);
        pix_item->setPos(0,(height()/2)-600);
        pix_item->setOpacity(0.4);
        // COORDONNEES > 100 :
        if(_max_val>100) {

            QFont serifFont("Glass TTY VT220", 30, QFont::Bold);
           scene->addText("U A ' Faculté des sciences \n Nb Y :"+s+"\n Rows :"+r+"\n Max val :"+m+"\n min val : "+min ,serifFont);
            for(auto i=0; i<_max_val*10;i+=100){
               AxisX = scene->addLine((width()/2)+i,(height()/2),(width()/2)+i,(height()/2)-5,penAxis);
               AxisY = scene->addLine((width()/2),(height()/2)-i,(width()/2)+5,(height()/2)-i,penAxis);
            }

            if(_min_val < -100){
              for(auto i=0; i<_min_val*-(10);i+=100){
                               AxisX = scene->addLine((width()/2)-i,(height()/2),(width()/2)-i,(height()/2)-5,penAxis);
                             AxisY = scene->addLine((width()/2),(height()/2)+i,(width()/2)+5,(height()/2)+i,penAxis);
                  }
              } else {
                for(auto i=0; i< (-_min_val*100) ;i+=100){
                                 AxisX = scene->addLine((width()/2)-i,(height()/2),(width()/2)-i,(height()/2)-5,penAxis);
                                 AxisY = scene->addLine((width()/2),-(height()/2)-i,(width()/2)+5,height(),penAxis);
                    }
                for (int i = 0 ; i <= (-_min_val) ;i+=10) {
                    axis_xnums.push_back(scene->addText(QString::fromStdString(std::to_string(-i/10)),ArialFont));
                    axis_xnums.at(i/10)->setPos((width()/2)-(i*10),height()/2);
                    axis__ynums.push_back(scene->addText(QString::fromStdString(std::to_string(-i*2)),ArialFont));
                    axis__ynums.at(i/10)->setPos(width()/2,(height()/2)+(i*20));
                }
              }
//                line = scene->addLine(-400,(height()/2),width()+400,(height()/2),penAxis);
//                line = scene->addLine((width()/2),-height()-400,(width()/2),height()+400,penAxis);

            graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
            line = scene->addLine(scene->sceneRect().left(),(graphiques->height()/2),scene->sceneRect().right(),(graphiques->height()/2),penAxis);
            line = scene->addLine(width()/2,scene->sceneRect().top(),width()/2,scene->sceneRect().bottom(),penAxis);
                for (int i = 0 ; i <= (_max_val/10) ;i++) {
                      axis_x_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i)),ArialFont));
                      axis_x_nums.at(i)->setPos((width()/2)+(i*100),height()/2);
                       axis_y_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i*10)),ArialFont));
                       axis_y_nums.at(i)->setPos(width()/2,(height()/2)-(i*100));

                }

            _pen1.setWidth(5);

            for (int j = 1 ; j < _nb_Y ; j++) {
                _pen1.setColor(clrArr.at(static_cast<size_t>(j-1)));
                if(j!=1) _pen1.setWidth(1+(j*2));
                for (size_t i=1;i<_nb_rows;i++) {

                        scene->addLine((width()/2)+(_wordList.at(i).at(0).toDouble()*100),(height()/2)-20,
                                       (width()/2)+(_wordList.at(i).at(0).toDouble()*100),
                                       (height()/2)-(_wordList.at(i).at(j).toDouble()*10),_pen1);
                            }
              }
//            graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
//            graphiques->adjustSize();

        }


        // COORDONNES < 100 :
        else {

            QFont serifFont("Glass TTY VT220", 30, QFont::Bold);
           scene->addText("U A ' Faculté des sciences \n Nb Y :"+s+"\n Rows :"+r+"\n Max val :"+m+"\n min val : "+min ,serifFont);
             for(auto i=0; i<_max_val*100;i+=100){
               AxisX = scene->addLine((width()/2)+i,(height()/2),(width()/2)+i,(height()/2)-5,penAxis);
               AxisX = scene->addLine((width()/2)-i,(height()/2),(width()/2)-i,(height()/2)-5,penAxis);
               AxisY = scene->addLine((width()/2),(height()/2)+i,(width()/2)+5,(height()/2)+i,penAxis);
               AxisY = scene->addLine((width()/2),(height()/2)-i,(width()/2)+5,(height()/2)-i,penAxis);
           }
//        line = scene->addLine(0,(height()/2),width(),(height()/2),penAxis);
//        line = scene->addLine((width()/2),-400,(width()/2),height()+400,penAxis);

        for (int i = 0 ; i <= _max_val ;i++) {
              axis_x_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i)),ArialFont));
              axis_x_nums.at(i)->setPos((width()/2)+(i*100),height()/2);

               axis_y_nums.push_back(scene->addText(QString::fromStdString(std::to_string(i)),ArialFont));
               axis_y_nums.at(i)->setPos(width()/2,(height()/2)-(i*100));

        }
        for (int i = 0 ; i <= (-_min_val) ;i++) {
            axis_xnums.push_back(scene->addText(QString::fromStdString(std::to_string(-i)),ArialFont));
            axis_xnums.at(i)->setPos((width()/2)-(i*100),height()/2);
            axis__ynums.push_back(scene->addText(QString::fromStdString(std::to_string(-i)),ArialFont));
            axis__ynums.at(i)->setPos(width()/2,(height()/2)+(i*100));
        }
        graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);
        line = scene->addLine(scene->sceneRect().left(),(graphiques->height()/2),scene->sceneRect().right(),(graphiques->height()/2),penAxis);
        line = scene->addLine(width()/2,scene->sceneRect().top(),width()/2,scene->sceneRect().bottom(),penAxis);

        _pen1.setWidth(12);

          for (int j = 1 ; j < _nb_Y ; j++) {
              _pen1.setColor(clrArr.at(static_cast<size_t>(j-1)));
               if(j!=1) _pen1.setWidth(1+(j*2));
              for (size_t i=1;i<_nb_rows;i++) {

                scene->addLine((width()/2)+(_wordList.at(i).at(0).toDouble()*100),(height()/2)-20,
                               (width()/2)+(_wordList.at(i).at(0).toDouble()*100),
                               (height()/2)-(_wordList.at(i).at(j).toDouble()*100),_pen1);
                    }
            }
//          graphiques->fitInView(scene->itemsBoundingRect(),Qt::AspectRatioMode::KeepAspectRatio);

        }
}

void modelGraphiques::showGrid()
{
    AxisGridX.resize(0);
    AxisGridY.resize(0);
    QPen gridPen(Qt::black);
    gridPen.setWidth(1);
    int j(0);
    if(_max_val>100){
        for(auto i=100; i<_max_val*5;i+=100){
           AxisGridX.push_back( scene->addLine((width()/2)+i,-height()-600,(width()/2)+i,height(),gridPen));
           AxisGridX.push_back( scene->addLine((width()/2)-i,-height()-600,(width()/2)-i,height(),gridPen));

           AxisGridY.push_back( scene->addLine(-width()-400,(height()/2)-i,width()+400,(height()/2)-i,gridPen));
           AxisGridY.push_back( scene->addLine(-width()-400,-(height()-600)-i,width()+400,-(height()-600)-i,gridPen));
           j++;
   }
  }  else {
            for(auto i=100; i<_max_val*100;i+=100){
       AxisGridX.push_back( scene->addLine((width()/2)+i,height()+230,(width()/2)+i,-230,gridPen));
       AxisGridX.push_back( scene->addLine((width()/2)-i,height()+230,(width()/2)-i,-230,gridPen));
       AxisGridY.push_back( scene->addLine(0,(height()/2)+i,width(),(height()/2)+i,gridPen));
       AxisGridY.push_back( scene->addLine(0,(height()/2)-i,width(),(height()/2)-i,gridPen));
    j++;
    }
    }
}

void modelGraphiques::hideGrid()
{
    if(_max_val>100){
        for(size_t it = 0 ; it < AxisGridX.size(); it++ ){
       AxisGridX.at(it)->hide();
        }
        for(size_t it = 0 ; it < AxisGridX.size() ; it++ ){
       AxisGridY.at(it)->hide();
        }
    }    else {
     for(size_t it = 0 ; it < AxisGridX.size()/*static_cast<size_t>(_max_val)+6*/; it++ ){
    AxisGridX.at(it)->hide();
     }
     for(size_t it = 0 ; it < AxisGridX.size() /*static_cast<size_t>(_max_val)+6*/ ; it++ ){
    AxisGridY.at(it)->hide();
     }
        }
}



void modelGraphiques::paintGraphicsEngine()
{

    QImage img(":/watermark/unnamed.ico");
    pix_mark.convertFromImage(img);

    QHBoxLayout * grpLayout = new QHBoxLayout;
    grpLAB = new QLabel(this);

    graphiques = new QGraphicsView(this);
    scene = new QGraphicsScene;

    graphiques->setScene(scene);
    graphiques->setMinimumSize(600,600);

    grpLayout->addWidget(graphiques);

    grpLAB->setLayout(grpLayout);

    mainlayout->addWidget(grpLAB,0,1,1,2);
}


