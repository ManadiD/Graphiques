#ifndef MODELGRAPHIQUES_H
#define MODELGRAPHIQUES_H
#include <list>
#include <vector>
#include <QLabel>
#include <QSize>
#include <QAction>
#include <QFile>
#include <QTableWidget>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QFormLayout>
#include <QLayout>
#include <QWheelEvent>
#include <QGraphicsItem>
#include <QSlider>
#include <QMovie>
#include <QDialog>
class modelGraphiques : public QWidget {
public:
public:
    enum Shape { Line, Points, Bars };
    enum TriMode { Ascendant , Descendant};
    explicit modelGraphiques(QWidget *parent = nullptr);
    ~modelGraphiques(){
        delete graphiques;
        delete  scene;

    }
    QGraphicsView & getGraphics() const  {
        return  *graphiques;
    }
    QGraphicsScene & getScene() const  {
        return  *scene;
    }
    std::array<QColor,5> getClrArr() const {
        return  clrArr;
    }
    void setclrArrValue(size_t index,QColor & c){
        clrArr.at(index)=c;
    }

//    void wheelEvent(QWheelEvent *);
    virtual void paintGraphicsEngine();
    void lire_CSV(QString const &csv,QTableWidget* tab,QAction * dess,QAction * saveAc);
    void updateWordList(QTableWidget* tab);
    void drawPLB();
    void drawLines();
    void drawBars();
    void showGrid();
    void hideGrid();
    void creerTools();
    void saveToImg(QPixmap & pix, QString & filename);

public:

    QPen _pen1,penAxis,_pen3;
    QLabel *image,*type,*_couleur1,*_couleur2,*_couleur3,*police,*largeur,*hauteur,
            *margeX,*margY,*_couleurFond,*_couleurAxes,*pasX,*pasY,*Grille,*Trier_lab,*ratio_lab;

    QPushButton * costum1,*costum2,*costum3,*fontButton,*fondClrButton,*axescolorbtn,
                *_triMode,*_triMode2,* theme_tabBtn,*theme_tabBtnReset,*justify_grp,*FontColor,*theme,*theme2;
    QComboBox *_typesGraphiques;
    QSpinBox *largeuredit,*hauteruedit,*margeXedit,*margeYedit,*pasXedit,*pasYedit;
    QGridLayout *mainlayout;
    QCheckBox *grilleCheck;
    QSpinBox * penwidth_Ratio;
private:
std::array<QStringList,200> _wordList;
size_t _taille;
double _min_val,_max_val;
unsigned short int _nb_Y,_nb_rows;
std::array<QColor,5> clrArr = {Qt::red ,  Qt::green , Qt::blue, Qt::black , Qt::cyan};
    Shape _type;
    QVBoxLayout *graphicsLayout;
    QLabel *grpLAB;
   QPixmap pix_mark;

    QGraphicsView *graphiques;
    QGraphicsScene *scene;
    QGraphicsRectItem * rect;
    QGraphicsLineItem * line,*AxisX,*AxisY;

    QGraphicsPixmapItem *pix_item;
    std::vector<QGraphicsTextItem *> axis_x_nums,axis_xnums,axis_y_nums,axis__ynums;
    std::vector<QGraphicsLineItem *> AxisGridX,AxisGridY;

};

#endif // MODELGRAPHIQUES_H
