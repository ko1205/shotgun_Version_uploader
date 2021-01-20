#include "selectfiledialog.h"
#include <QFileInfo>

SelectFileDialog::SelectFileDialog(Core *core)
{
    this->core = core;
    QString projectName = core->getProjectName();
    QString leftView = core->getLeftViewCurrent();
    QString centerView = core->getCenterViewCurrent();
    QString rightView = core->getRightViewCurrent();

    QString elementType;

    if(core->getElementType() == ASSET){
        elementType = "Asset";
    }else{
        elementType = "Shot";
    }

    QString labelString;
    labelString = QString("Current Project : %1\nCurrent Linek : %2 -> %3 -> %4 -> %5").arg(projectName).arg(elementType).arg(leftView).arg(centerView).arg(rightView);

    label = new QLabel(labelString);
    fileSelectBtn = new QPushButton("Select Upload File");

    messageWindow = new QPlainTextEdit;
    messageWindow->setReadOnly(true);


    layout = new QGridLayout;

    layout->addWidget(label,0,0);
    layout->addWidget(fileSelectBtn,1,0);
    layout->addWidget(messageWindow,2,0);

    setLayout(layout);

    connect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickSelectFile()));

}

void SelectFileDialog::clickSelectFile()
{
    selectedFile = QFileDialog::getOpenFileName(this,"Select File",".","movie (*.mov *.mp4 *.avi);;image (*.jpg *.jpeg *.png)");
    QFileInfo check_file(selectedFile);
    if (check_file.exists() && check_file.isFile()) {
        messageWindow->appendHtml("<font color=blue> Selected File : " + selectedFile + "</font>");
        disconnect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickSelectFile()));
        connect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickCancel()));
        fileSelectBtn->setText("Cancel");

    }
    qDebug() << selectedFile;
}

void SelectFileDialog::clickCancel()
{

    fileSelectBtn->setText("Select Upload File");
    disconnect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickCancel()));
    connect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickSelectFile()));

}
