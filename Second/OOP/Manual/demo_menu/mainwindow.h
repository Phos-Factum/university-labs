#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

private slots:
    void on_actionHideEditAll_triggered();
    void on_actionHideEdit2_triggered();
    void on_actionHideEdit1_triggered();
    void on_actionShowEdiAll_triggered();
    void on_actionShowEdit2_triggered();
    void on_actionShowEdit1_triggered();
};

#endif // MAINWINDOW_H
