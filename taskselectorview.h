#ifndef TASKSELECTORVIEW_H
#define TASKSELECTORVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "core.h"
#include <QDebug>

class TaskSelectorView : public QWidget
{
    Q_OBJECT

private:
    Core *core;
    int element;

    QListWidget *leftListView;
    QListWidget *centerListView;
    QListWidget *rightListView;

    void setLeftListView();

public:
    explicit TaskSelectorView(Core *core,int element,QWidget *parent = nullptr);

signals:
    void goToElementSelector();

private slots:
    void clickBackButton();
    void leftListViewSelected(QString currentText);
    void centerListViewSelected(QString currentText);
    void rightListViewDoubleClick(QListWidgetItem *item);

};

#endif // TASKSELECTORVIEW_H
