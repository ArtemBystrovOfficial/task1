#ifndef APP_H
#define APP_H

#include <QObject>
#include <QWidget>
#include <QQuickWidget>
#include <QLayout>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget * parent = nullptr );
    virtual ~MyWidget(){}
};
#endif // APP_H
