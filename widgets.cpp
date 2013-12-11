#include <QFont>
#include "widgets.h"

Widgets::Widgets(QMainWindow *parent) : QWidget(parent)
	{
	qdial=new QDial;
	qspinbox=new QSpinBox;
	maxWertButton = new QPushButton("100%");
	graphicsView = new QGraphicsView;

	maxWertButton->setFont(QFont("Helvetica", 16, QFont::Normal));
	qdial->setNotchesVisible(true);
	qspinbox->setFont(QFont("Helvetica", 12, QFont::StyleNormal));

	gridLayout = new QGridLayout(this);
	gridLayout->addWidget(maxWertButton, 0, 0);
	gridLayout->addWidget(qspinbox, 1, 0);
	gridLayout->addWidget(qdial, 2, 0);
	gridLayout->addWidget(graphicsView, 0,1,3,1);


	gridLayout->setColumnStretch(1, 10);
	setLayout(gridLayout);
	qdial->setValue(50);
	}
