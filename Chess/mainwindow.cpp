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

    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    GameManager manager(fileName);
    gameManager = &manager;

    boardDrawer.initializeBoard(scene);
    boardDrawer.drawPieces(scene, gameManager->getPieces());
}

MainWindow::~MainWindow()
{
    delete ui;
}
