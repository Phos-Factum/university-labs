#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionShowEdit1_triggered()
{
    ui->Edit1->show();
}

void MainWindow::on_actionShowEdit2_triggered()
{
     ui->Edit2->show();
}

void MainWindow::on_actionShowEdiAll_triggered()
{
     ui->Edit1->show();
     ui->Edit2->show();
}

void MainWindow::on_actionHideEdit1_triggered()
{
    ui->Edit1->hide();
}

void MainWindow::on_actionHideEdit2_triggered()
{
    ui->Edit2->hide();
}

void MainWindow::on_actionHideEditAll_triggered()
{
     ui->Edit1->hide();
     ui->Edit2->hide();

}
