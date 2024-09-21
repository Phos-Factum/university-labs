/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Mar 28 12:35:11 2013
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionShowEdit1;
    QAction *actionShowEdit2;
    QAction *actionShowEdiAll;
    QAction *actionHideEdit1;
    QAction *actionHideEdit2;
    QAction *actionHideEditAll;
    QWidget *centralWidget;
    QLineEdit *Edit1;
    QLineEdit *Edit2;
    QMenuBar *menuBar;
    QMenu *menuShow;
    QMenu *menuHide;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        actionShowEdit1 = new QAction(MainWindow);
        actionShowEdit1->setObjectName(QString::fromUtf8("actionShowEdit1"));
        actionShowEdit2 = new QAction(MainWindow);
        actionShowEdit2->setObjectName(QString::fromUtf8("actionShowEdit2"));
        actionShowEdiAll = new QAction(MainWindow);
        actionShowEdiAll->setObjectName(QString::fromUtf8("actionShowEdiAll"));
        actionHideEdit1 = new QAction(MainWindow);
        actionHideEdit1->setObjectName(QString::fromUtf8("actionHideEdit1"));
        actionHideEdit2 = new QAction(MainWindow);
        actionHideEdit2->setObjectName(QString::fromUtf8("actionHideEdit2"));
        actionHideEditAll = new QAction(MainWindow);
        actionHideEditAll->setObjectName(QString::fromUtf8("actionHideEditAll"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Edit1 = new QLineEdit(centralWidget);
        Edit1->setObjectName(QString::fromUtf8("Edit1"));
        Edit1->setGeometry(QRect(140, 100, 113, 27));
        Edit2 = new QLineEdit(centralWidget);
        Edit2->setObjectName(QString::fromUtf8("Edit2"));
        Edit2->setGeometry(QRect(140, 160, 113, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 25));
        menuShow = new QMenu(menuBar);
        menuShow->setObjectName(QString::fromUtf8("menuShow"));
        menuHide = new QMenu(menuBar);
        menuHide->setObjectName(QString::fromUtf8("menuHide"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuShow->menuAction());
        menuBar->addAction(menuHide->menuAction());
        menuShow->addAction(actionShowEdit1);
        menuShow->addAction(actionShowEdit2);
        menuShow->addAction(actionShowEdiAll);
        menuHide->addAction(actionHideEdit1);
        menuHide->addAction(actionHideEdit2);
        menuHide->addAction(actionHideEditAll);
        mainToolBar->addAction(actionShowEdit1);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionShowEdit2);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionShowEdiAll);
        mainToolBar->addSeparator();
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionHideEdit1);
        mainToolBar->addAction(actionHideEdit2);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionHideEditAll);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\222\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217 \320\270 \321\201\320\276\320\272\321\200\321\213\321\202\320\270\320\265 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200\320\276\320\262", 0, QApplication::UnicodeUTF8));
        actionShowEdit1->setText(QApplication::translate("MainWindow", "ShowEdit1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionShowEdit1->setToolTip(QApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\262\320\265\321\200\321\205\320\275\320\270\320\271 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200\n"
"", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionShowEdit2->setText(QApplication::translate("MainWindow", "ShowEdit2", 0, QApplication::UnicodeUTF8));
        actionShowEdiAll->setText(QApplication::translate("MainWindow", "ShowEdiAll", 0, QApplication::UnicodeUTF8));
        actionHideEdit1->setText(QApplication::translate("MainWindow", "HideEdit1", 0, QApplication::UnicodeUTF8));
        actionHideEdit2->setText(QApplication::translate("MainWindow", "HideEdit2", 0, QApplication::UnicodeUTF8));
        actionHideEditAll->setText(QApplication::translate("MainWindow", "HideEditAll", 0, QApplication::UnicodeUTF8));
        menuShow->setTitle(QApplication::translate("MainWindow", "Show", 0, QApplication::UnicodeUTF8));
        menuHide->setTitle(QApplication::translate("MainWindow", "Hide", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
