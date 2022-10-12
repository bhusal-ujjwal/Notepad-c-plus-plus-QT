#include "mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setting the geometry of the window
    setGeometry(100, 100, 640, 400);

    //creating the menu list
    QMenu *filemenu1 = new QMenu("File");

    //creating the file item
    QAction *actOpen = new QAction("Open Text File...");
    actOpen->setShortcut(QKeySequence::Open);

    //creating the save item on menu
    QAction *actSaveAs = new QAction("Save file as...");
    actSaveAs->setShortcut(QKeySequence::Save);

    //creating the exit
    QAction *actQuit = new QAction("Quit");

    //pointing to the actions
    filemenu1->addAction(actOpen);
    filemenu1->addAction(actSaveAs);
    filemenu1->addSeparator();
    filemenu1->addAction(actQuit);


    //crating the menu bar
    menuBar()->addMenu(filemenu1);


    m_memo = new QTextEdit(this);
    setCentralWidget(m_memo);


    //statusbar creation
    statusBar()->showMessage("Ready...", 10000);

    //here we connect the triggers to the slots
    connect(actQuit, &QAction::triggered, this, &MainWindow::close);
    connect(actSaveAs, &QAction::triggered, this, &MainWindow::saveAs);
    connect(actOpen, &QAction::triggered, this, &MainWindow::open);
}



MainWindow::~MainWindow()
{
}

//this is the save as function
void MainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Text As", "","Text Files(*.txt");
    if(!filename.isEmpty()){
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            out << m_memo->toPlainText();
            file.close();
            statusBar()->showMessage("The File was saved..", 5000);
        }else{
            QMessageBox::critical(this, "My Notepad", "Unable to save the file");
        }
    }
}

//this is the open function
void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open FIle", "","Text Files(*.txt)");
    if(! filename.isEmpty()){
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            m_memo->setText(in.readAll());
            file.close();
            statusBar()->showMessage(QString("File %1 was opend...").arg(filename), 5000);
        }else{
            QMessageBox::critical(this, "MY Notepad", "Unable to open a file");
        }

}
}

