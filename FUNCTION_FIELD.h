#ifndef FUNCTION_FIELD_H
#define FUNCTION_FIELD_H
#pragma once
#include "FUNC.h"
#include "AREA.h"
#include "OPTIMISATION.h"
#include <vector>
#include <iterator>
#include "QString"

class FUNCTION_FIELD
{
friend class qtDRAWER;
public:
    FUNCTION_FIELD();
private:
    ~FUNCTION_FIELD();

    FUNC* f=0;
    AREA* rectangle=0;
    Random_search* rs=0;
    Coordinate_wise* cw=0;
    Iterations* rs_iter =0;
    Iterations* cw_iter =0;
    ArgNorm* rs_argnorm =0;
    ArgNorm* cw_argnorm =0;
    int opt_type=0; //0-RS 1-CV
    int rs_stop_type=0; //0-counter 1-fail 2-distance
    int cw_stop_type=1; //0-counter 1-fail 2-distance

    double min_val = 0;
    unsigned int n_iter = 0;
    std::vector<double> argmin;

    QString min_val_str;
    QString argmin_str;
    QString n_iter_str;

    void CreateGrid(int width, int height, int Npart);
    void Optimize(int width,int height, double x, double y);

    std::vector<double> ConvertPoint(int width,int height,int x, int y) const;

    void ChangeFunction(const unsigned int id);
    void ChangeStopper(const unsigned int id);
    void ChangeMethod(const unsigned int id);
    void ChangeArea(const std::vector<double> bounds);

    void ChangeRSStop(const unsigned int id);
    void ChangeCWStop(const unsigned int id);

    void ChangeRSprob(double prob);

    std::vector<std::vector<double>> Path;
    std::vector<std::vector<int>> RangeField;
};

#endif // FUNCTION_FIELD_H
