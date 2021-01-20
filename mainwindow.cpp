#include "mainwindow.h"

MainWindow::MainWindow(Core *core, QWidget *parent) : QMainWindow(parent)
{
    this->core = core;
//    elementSelector = new ElementSelector();

//    connect(elementSelector,SIGNAL(goToProjectSelector()),this,SLOT(readProjectList()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::readProjectList()
{
    core->readProjcetList();

    int count = core->qList.size();
    int wCount = 5;
//    qDebug() << "count Size" << count;
    this->resize(800,600);

    layout = new QGridLayout;

    for(int i = 0;i<(count+wCount)/wCount;i++){
        for(int n=0;n<wCount;n++){
            if(i*wCount+n < count){
                QMap<QString,QString> qItem = core->qList.at(i*wCount+n);
                button = new ProjectButton(qItem["name"]);
                button->setInfo(qItem["name"],qItem["id"].toInt());
                button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
                layout->addWidget(button,i,n);
                connect(button,SIGNAL(selectProject(QString&,int)),this,SLOT(changeWindow(QString&,int)));
            }else{
                break;
            }
        }
    }


    projectSelector = new QWidget;
    projectSelector->setLayout(layout);
    setCentralWidget(projectSelector);
}

void MainWindow::changeWindow(QString &name, int id)
{
    qDebug() << name << id;
    core->setSelectedProject(id, name);
    creatElementWindow();
//    elementSelector = new ElementSelector;
//    connect(elementSelector,SIGNAL(goToProjectSelector()),this,SLOT(readProjectList()));
//    connect(elementSelector,SIGNAL(goToAssetSelector()),this,SLOT(assetWindow()));
//    connect(elementSelector,SIGNAL(goToShotSelector()),this,SLOT(shotWindow()));

//    setCentralWidget(elementSelector);
//    delete projectSelector;

}

void MainWindow::creatElementWindow()
{
    elementSelector = new ElementSelector;
    connect(elementSelector,SIGNAL(goToProjectSelector()),this,SLOT(readProjectList()));
    connect(elementSelector,SIGNAL(goToAssetSelector()),this,SLOT(assetWindow()));
    connect(elementSelector,SIGNAL(goToShotSelector()),this,SLOT(shotWindow()));

    setCentralWidget(elementSelector);
}

void MainWindow::assetWindow()
{
    core->setElement(ASSET);
    TaskSelectorView *widget = new TaskSelectorView(core,ASSET);
    connect(widget,SIGNAL(goToElementSelector()),this,SLOT(creatElementWindow()));
    setCentralWidget(widget);
}

void MainWindow::shotWindow()
{
    core->setElement(SHOT);
    TaskSelectorView *widget = new TaskSelectorView(core,SHOT);
    connect(widget,SIGNAL(goToElementSelector()),this,SLOT(creatElementWindow()));
    setCentralWidget(widget);
}
