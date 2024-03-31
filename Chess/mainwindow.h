#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boarddrawer.h"

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;


    BoardDrawer boardDrawer;
};
#endif // MAINWINDOW_H
