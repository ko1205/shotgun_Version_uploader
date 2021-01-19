#include "dialog.h"
#include <QMessageBox>
#include <Qurl>

Dialog::Dialog(Core *core, MainWindow *mainWindow, QWidget *parent)
    : QDialog(parent)
{
    this->core = core;
    this->mainWindow = mainWindow;

    urlLabel = new QLabel("URL :");
    loginLabel = new QLabel("Login :");
    passwdLabel = new QLabel("Password :");
    urlEdit = new QLineEdit("https://wswg.shotgunstudio.com");
    loginEdit = new QLineEdit("cgilh");
    passwdEdit = new QLineEdit("goemffjA12");
    passwdEdit->setEchoMode(QLineEdit::Password);
    connectButton = new QPushButton("Connect");

    gridLayout = new QGridLayout();
    gridLayout->addWidget(urlLabel,0,0);
    gridLayout->addWidget(urlEdit,0,1,1,2);
    gridLayout->addWidget(loginLabel,1,0);
    gridLayout->addWidget(loginEdit,1,1,1,2);
    gridLayout->addWidget(passwdLabel,2,0);
    gridLayout->addWidget(passwdEdit,2,1,1,2);
    gridLayout->addWidget(connectButton,3,2);

    setLayout(gridLayout);
    connectButton->setDisabled(true);
    setConnnectBtnDisable();
    this->setFixedSize(400,150);

    connect(urlEdit,SIGNAL(textChanged(QString)),this,SLOT(setConnnectBtnDisable()));
    connect(loginEdit,SIGNAL(textChanged(QString)),this,SLOT(setConnnectBtnDisable()));
    connect(passwdEdit,SIGNAL(textChanged(QString)),this,SLOT(setConnnectBtnDisable()));
    connect(connectButton,SIGNAL(clicked(bool)),this,SLOT(connectSite()));
}

Dialog::~Dialog()
{

}


void Dialog::setConnnectBtnDisable()
{
    if (urlEdit->text() != NULL && loginEdit->text() != NULL && passwdEdit->text() != NULL)
    {
        connectButton->setDisabled(false);

    }else{
        connectButton->setDisabled(true);
    }
}

void Dialog::connectSite()
{
    if(core->connectSite(urlEdit->text(),loginEdit->text(),passwdEdit->text()))
    {
        this->hide();
        mainWindow->readProjectList();
        mainWindow->show();
    }
}
