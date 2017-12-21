#include "FUNCTION_FIELD.h"
#include "FUNC.h"
#include "QString"
#include <iostream>

FUNCTION_FIELD::FUNCTION_FIELD()
{
    f = new Parabolic();
    rectangle = new AREA(2,{-5,5,-5,5});
    rs_iter = new Iterations(1000);
    rs_argnorm = new ArgNorm(0.0001);
    cw_iter = new Iterations(1000);
    cw_argnorm = new ArgNorm(0.0001);
    rs = new Random_search(f,rectangle,rs_iter);
    cw = new Coordinate_wise(f,rectangle,cw_argnorm);
}
FUNCTION_FIELD::~FUNCTION_FIELD() {
    delete f;
    delete rectangle;
};

void FUNCTION_FIELD::CreateGrid(int width,int height, int Npart) {
    std::vector<std::vector<double>> EvaluateField;
    double value;
    std::vector<double> bounds = rectangle->get_bounds();
    double xmin = bounds[0];
    double ymin = bounds[2];
    double xmax = bounds[1];
    double ymax = bounds[3];

    double step_x=(xmax-xmin)/width;
    double step_y=(ymax-ymin)/height;

    double min_value=f->val({xmin,ymax});
    double max_value=f->val({xmin,ymax});

    std::vector<double> row(height);
    for (int i=0;i<width;++i) {
        row.clear();
        for (int j=0;j<height;++j) {
            value = f->val({xmin+i*step_x,ymax-j*step_y});
            if (min_value>value) min_value=value;
            if (max_value<value) max_value=value;
            row.push_back(value);
        }
        EvaluateField.push_back(row);
    }

    RangeField=std::vector<std::vector<int>>(width);
    for (int i=0; i<width;++i) {
       RangeField[i]=std::vector<int>(height);

        std::transform(EvaluateField[i].begin(),
                       EvaluateField[i].end(),
                      RangeField[i].begin(),
                       [&](double x) -> int {
            return Npart*(log((x-min_value)+1)/log(max_value-min_value+1));
        });
  };
};

void FUNCTION_FIELD::ChangeFunction(const unsigned int id)
{
    delete f;
    switch (id) {
    case 0: f = new Parabolic(); break;
    case 1: f = new Wavy(); break;
    case 2:  f = new LeviN13(); break;
    }
    rs->update_func(f);
    cw->update_func(f);

    Path.clear();
    Path.shrink_to_fit();
}

std::vector<double> FUNCTION_FIELD::ConvertPoint(int width,int height,int x, int y) const {
    std::vector<double> point(2);
    std::vector<double> bounds = rectangle->get_bounds();
    double xmin = bounds[0];
    double ymin = bounds[2];
    double xmax = bounds[1];
    double ymax = bounds[3];

    double step_x=(xmax-xmin)/width;
    double step_y=(ymax-ymin)/height;

    point[0]=xmin+x*step_x;
    point[1]=ymax-y*step_y;
    return point;
};

void FUNCTION_FIELD::Optimize(int width,int height, double x, double y)
{
    Path.clear();
    Path.shrink_to_fit();
    std::vector<double> x0 = ConvertPoint(width,height,x,y);
    if (opt_type==0)
    {
        rs->clear();
        rs->optimise(x0);
        Path = rs->get_journal();
        min_val = rs->get_val();
        argmin  = rs->get_arg();
        n_iter = rs->get_iterations();
    }
    else
    {
        cw->clear();
        cw->optimise(x0);
        Path = cw->get_journal();
        min_val = cw->get_val();
        argmin  = cw->get_arg();
        n_iter = cw->get_iterations();
    }

    min_val_str = QString::number(min_val);
    argmin_str = "["+QString::number(argmin[0]) + ", "+QString::number(argmin[1])+"]";
    n_iter_str = QString::number(n_iter);
}

//void FUNCTION_FIELD::ChangeStopper(const unsigned int id)
//{
//    delete stop;
//    switch (id) {
//    case 0: stop = new Iterations(); break;
//    case 1: st = new ArgNorm(); break;
//    }

//}

void FUNCTION_FIELD::ChangeMethod(const unsigned int id)
{
    opt_type = id;
}

void FUNCTION_FIELD::ChangeRSStop(const unsigned int id)
{
    rs_stop_type = id;
    if (id ==0){
        rs->update_stop(rs_iter);
    }
    else{
        rs->update_stop(rs_argnorm);
    }
}

void FUNCTION_FIELD::ChangeCWStop(const unsigned int id)
{
    cw_stop_type = id;
    if (id ==0){
        cw->update_stop(cw_iter);
    }
    else{
        cw->update_stop(cw_argnorm);
    }
}

void FUNCTION_FIELD::ChangeRSprob(const double prob)
{
    rs->update_prob(prob);
}
//void FUNCTION_FIELD::ChangeArea(const std::vector<double> bounds);
