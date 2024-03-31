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

    gameManager = new GameManager();

    boardDrawer.drawSquares(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nextMove_clicked()
{
    if (gameManager->hasNextMove())
    {
        qDebug() << "";
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
    gameManager = new GameManager(fileName);

    boardDrawer.drawPieces(scene, gameManager->getPieces());
}

