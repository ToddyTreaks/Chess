#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    GameManager manager;
    gameManager = &manager;

    boardDrawer.initializeBoard(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nextMove_clicked()
{
    if (gameManager->hasNextMove())
    {
        gameManager->nextMove();
    }
    boardDrawer.drawPieces(scene, gameManager->getPieces());
}


void MainWindow::on_previousMove_clicked()
{
    if (gameManager->hasPreviousMove())
    {
        gameManager->previousMove();
    }
    boardDrawer.drawPieces(scene, gameManager->getPieces());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    GameManager manager(fileName);
    gameManager = &manager;

    boardDrawer.drawPieces(scene, gameManager->getPieces());
}

