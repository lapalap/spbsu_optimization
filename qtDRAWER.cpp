#include "qtDRAWER.h"
#include "QPainter"
#include "iterator"
#include "FUNCTION_FIELD.h"

qtDRAWER::qtDRAWER(QWidget *parent) : QWidget(parent)
{
    field = new FUNCTION_FIELD();
    setMouseTracking(true);
}

void qtDRAWER::mouseMoveEvent(QMouseEvent *event) {
    int x=event->x();
    int y=event->y();
    QSize sz = size();
    int width=sz.width();
    int height=sz.height();
}


void qtDRAWER::mousePressEvent(QMouseEvent* event){
      int x=event->x();
      int y=event->y();
      QSize sz = size();
      int width=sz.width();
      int height=sz.height();
      field->Optimize(width,height,x,y);
      printResult();
      repaint();
};

void qtDRAWER::printResult()
{
    emit ResultVal(field->min_val_str);
    emit ResultArgmin(field->argmin_str);
    emit ResultNiter(field->n_iter_str);
}

QPointF qtDRAWER::ConvertVect(const std::vector<double> x0) {
    QSize sz = size();
    int width=sz.width();
    int height=sz.height();
    return QPointF(
                (x0[0]-field->rectangle->get_bounds()[0])/
            (field->rectangle->get_bounds()[1]-field->rectangle->get_bounds()[0])*width,
            (1-(x0[1]-field->rectangle->get_bounds()[2])/
        (field->rectangle->get_bounds()[3]-field->rectangle->get_bounds()[2]))*height);
}

void qtDRAWER::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen pen;
    QSize sz = size();

    int width=sz.width();
    int height=sz.height();

    field->CreateGrid(width,height,Npart);
    auto it = field->RangeField.begin();
    for (int i=0;i<width;++i) {
        for (int j=0;j<height;++j) {
            pen.setColor(QColor(255-(*it)[j]*3,255-(*it)[j]*3,255));
            p.setPen(pen);
            p.drawPoint(i,j);
        }
        ++it;
    }
    drawPath();
}


void qtDRAWER::drawPath() {
    if (field->Path.size()!=0) {
    auto it = field->Path.begin();
    std::vector<double> prev = *it;
    it++;
    int length = field->Path.size();

    QPainter p(this);
    int color = 0;

    for (;it!=field->Path.end();){
        p.setPen(QColor(color,color,color));
        p.setBrush(QColor(color,color,color));
        p.drawLine(ConvertVect(prev),ConvertVect(*it));
        p.drawEllipse(ConvertVect(prev),4,4);
        p.drawEllipse(ConvertVect(*it),4,4);
        prev=*it;
        it++;
        color += 250/length;
    }
    }
}

void qtDRAWER::ChangeMethod(int id) {
    field->ChangeMethod(id);
}

void qtDRAWER::ChangeFunction(int id)
{
    field->ChangeFunction(id);
    repaint();
}

qtDRAWER::~qtDRAWER() {
    delete field;
}

void qtDRAWER::ChangeRSCounter(const QString & text)
{
    double q = text.toInt();
    field->rs_iter->change_MAX(q);
}

void qtDRAWER::ChangeRSdist(double d)
{
    field->rs_argnorm->change_dist(d);
}

void qtDRAWER::ChangeRSStop(int id)
{
    field->ChangeRSStop(id);
}

void qtDRAWER::ChangeCWStop(int id)
{
    field->ChangeCWStop(id);
}

void qtDRAWER::ChangeRSprob(double prob)
{
    field->ChangeRSprob(prob);
}

void qtDRAWER::ChangeCWCounter(const QString & text)
{
    double q = text.toInt();
    field->cw_iter->change_MAX(q);
}

void qtDRAWER::ChangeCWdist(double d)
{
    field->cw_argnorm->change_dist(d);
}

void qtDRAWER::ChangeCWepsilon(double d)
{
    field->cw->update_epsilon(d);
}
