#ifndef WIDGETS_H
#define WIDGETS_H

#include <QWidget>
#include <QMainWindow>
#include <QDial>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsView>
//#include <QPixmap>
#include <QGraphicsScene>
//#include <QGraphicsPixmapItem>
#include <QPoint>
#include <QFont>


class Widgets : public QWidget
{
	Q_OBJECT

	QDial *qdial;
	QSpinBox *qspinbox;
	QPushButton *nord;
	QPushButton *sued;
	QPushButton *ost;
	QPushButton *west;
	QGridLayout *gridLayout;
	QGraphicsView *graphicsView;

	public:
	explicit Widgets(QMainWindow *parent = 0);

	QGraphicsScene* getSzene();
	};

#endif // WIDGETS_H
