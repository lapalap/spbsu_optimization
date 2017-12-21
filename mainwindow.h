#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtDRAWER.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    qtDRAWER *render;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBoxFunc_currentIndexChanged(int index);

    void on_radioButtonRS_iter_clicked(bool checked);
    void on_radioButtonRS_argnorm_clicked(bool checked);
    void on_radioButtonCW_iter_clicked(bool checked);
    void on_radioButtonCW_argnorm_clicked(bool checked);

    void on_radioButtonRS_clicked(bool checked);
    void on_radioButtonCW_clicked(bool checked);

    void aboutBox();

    void on_RSprob_valueChanged(double arg1);
    void on_CWepsilon_valueChanged(double arg1);

    void ResultEval(QString a);
    void ResultArgmin(QString a);
    void ResultNiter(QString a);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
