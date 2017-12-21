#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtDRAWER.h"
#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout* layout = findChild<QGridLayout*>("LayoutMain");
    render = new qtDRAWER();
    Q_ASSERT(layout);
    layout->addWidget(render);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::aboutBox);
    QObject::connect(ui->MinDist,
                     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),render,&qtDRAWER::ChangeRSdist);
    QObject::connect(ui->MaxCounter,&QLineEdit::textEdited,render,&qtDRAWER::ChangeRSCounter);

    QObject::connect(ui->MinDist_2,
                     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),render,&qtDRAWER::ChangeCWdist);
    QObject::connect(ui->MaxCounter_2,&QLineEdit::textEdited,render,&qtDRAWER::ChangeCWCounter);

    QLineEdit* MaxCounter = findChild<QLineEdit*>("MaxCounter");
    MaxCounter->setValidator(new QIntValidator(50,40000,MaxCounter));
    QLineEdit* MaxCounter_2 = findChild<QLineEdit*>("MaxCounter_2");
    MaxCounter_2->setValidator(new QIntValidator(50,40000,MaxCounter_2));

    QObject::connect(render,&qtDRAWER::ResultVal,this,&MainWindow::ResultEval);
    QObject::connect(render,&qtDRAWER::ResultArgmin,this,&MainWindow::ResultArgmin);
    QObject::connect(render,&qtDRAWER::ResultNiter,this,&MainWindow::ResultNiter);
}

void MainWindow::on_radioButtonRS_iter_clicked(bool checked) {
    if (checked) render->ChangeRSStop(0);
}

void MainWindow::on_radioButtonRS_argnorm_clicked(bool checked) {
    if (checked) render->ChangeRSStop(1);
}


void MainWindow::on_radioButtonCW_iter_clicked(bool checked) {
    if (checked) render->ChangeCWStop(0);
}

void MainWindow::on_radioButtonCW_argnorm_clicked(bool checked) {
    if (checked) render->ChangeCWStop(1);
}
void MainWindow::on_comboBoxFunc_currentIndexChanged(int index)
{
    std::cout<<index;
   render->ChangeFunction(index);
}

void MainWindow::aboutBox()
{
  QMessageBox::about(this, "SPbSU C++ class", "(c) lapalap 2017");
}

void MainWindow::on_radioButtonRS_clicked(bool checked)
{
    if (checked) {
        render->ChangeMethod(0);
    }
}

void MainWindow::on_radioButtonCW_clicked(bool checked)
{
    if (checked) {
        render->ChangeMethod(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete render;
}

void MainWindow::on_RSprob_valueChanged(double arg1)
{
    render->ChangeRSprob(arg1);
}

void MainWindow::ResultEval(QString a) {
    findChild<QLabel*>("lab_min")->setText(a);
}

void MainWindow::ResultArgmin(QString a) {
    findChild<QLabel*>("lab_argmin")->setText(a);
}

void MainWindow::ResultNiter(QString a) {
   findChild<QLabel*>("lab_n_iter")->setText(a);
}

void MainWindow::on_CWepsilon_valueChanged(double arg1)
{
    render->ChangeCWepsilon(arg1);
}
