#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boarddrawer.h"
#include "gamemanager.h"

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

private slots:
    void on_nextMove_clicked();

    void on_previousMove_clicked();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    GameManager *gameManager;
    BoardDrawer boardDrawer;

};
#endif // MAINWINDOW_H
