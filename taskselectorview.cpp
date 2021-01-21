#include "taskselectorview.h"
#include "QGridLayout"
#include <QListWidgetItem>
#include "selectfiledialog.h"

TaskSelectorView::TaskSelectorView(Core *core, int element, QWidget *parent) : QWidget(parent)
{
    this->core = core;
    this->element = element;

    leftListView = new QListWidget;
    centerListView = new QListWidget;
    rightListView = new QListWidget;

    QPushButton *backButton = new QPushButton("<-Back");

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(leftListView,0,0);
    layout->addWidget(centerListView,0,1);
    layout->addWidget(rightListView,0,2);

    layout->addWidget(backButton,1,0,1,3);

    setLayout(layout);

    setLeftListView();

    connect(backButton,SIGNAL(clicked(bool)),this,SLOT(clickBackButton()));
    connect(leftListView,SIGNAL(currentTextChanged(QString)),this,SLOT(leftListViewSelected(QString)));
    connect(centerListView,SIGNAL(currentTextChanged(QString)),this,SLOT(centerListViewSelected(QString)));
    connect(rightListView,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(rightListViewDoubleClick(QListWidgetItem*)));
}

void TaskSelectorView::clickBackButton()
{
    emit goToElementSelector();
}

void TaskSelectorView::setLeftListView()
{
    if(element == ASSET){
        QStringList assetTypeList = core->getAssetTypeList();
        qDebug() << assetTypeList;
        leftListView->addItems(assetTypeList);

    }else if(element == SHOT){
        QStringList sequenceList = core->getSequenceList();
        qDebug() << sequenceList;
        leftListView->addItems(sequenceList);
    }
}

void TaskSelectorView::leftListViewSelected(QString currentText)
{
    centerListView->clear();
    rightListView->clear();
    qDebug() << "Lefte List Click" << currentText;
    core->setLeftViewCurrent(currentText);
    if(element == ASSET){
        QStringList assetTypeList = core->getAssetList();
        qDebug() << assetTypeList;
        centerListView->addItems(assetTypeList);

    }else if(element == SHOT){
        QStringList sequenceList = core->getShotList();
        qDebug() << sequenceList;
        centerListView->addItems(sequenceList);
    }
}

void TaskSelectorView::centerListViewSelected(QString currentText)
{
    rightListView->clear();
    qDebug() << "centerListView item select" << currentText;
    core->setCenterViewCurrent(currentText);
    if(element == ASSET){
        QStringList TaskContentList = core->getAssetTaskList();
        rightListView->addItems(TaskContentList);
    }else if(element == SHOT){
        QStringList TaskContentList = core->getShotTaskList();
        rightListView->addItems(TaskContentList);
    }

}

void TaskSelectorView::rightListViewDoubleClick(QListWidgetItem *item)
{
    qDebug() << item->text();
    core->setRightViewCurrent(item->text());
    SelectFileDialog *dialog = new SelectFileDialog(core);
    dialog->resize(600,500);
    dialog->exec();
    delete dialog;
}
