#include "app.h"


MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

 QQuickWidget * pv = new QQuickWidget;
 pv->setSource(QUrl("qrc:/main.qml"));
 QVBoxLayout * ptr =  new QVBoxLayout;
 ptr->addWidget(pv);
 setLayout(ptr);
}
