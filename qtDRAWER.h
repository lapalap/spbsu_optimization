#ifndef QTDRAWER_H
#define QTDRAWER_H
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include "FUNCTION_FIELD.h"



class qtDRAWER : public QWidget
{
    Q_OBJECT
public:
    explicit qtDRAWER(QWidget *parent = 0);
    ~qtDRAWER();
protected:
    int Npart=50;
    FUNCTION_FIELD *field;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent * event) override;
    QPointF ConvertVect(const std::vector<double> x0);
    void drawPath();
signals:
    void ResultVal(QString s);
    void ResultArgmin(QString s);
    void ResultNiter(QString s);
public slots:
     void printResult();

     void ChangeFunction(int id);
     void ChangeMethod(int id);
     void ChangeRSStop(int id);
     void ChangeCWStop(int id);
     void ChangeRSprob (double prob);
     void ChangeCWepsilon(double d);

     void ChangeRSCounter(const QString & text);
     void ChangeRSdist(double d);

     void ChangeCWCounter(const QString & text);
     void ChangeCWdist(double d);

};

#endif // QTDRAWER_H
