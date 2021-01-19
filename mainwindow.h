#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core.h"
#include "projectbutton.h"
#include <QGridLayout>
#include <QDebug>
#include "elementselector.h"
#include "taskselectorview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Core *core;
    ProjectButton *button;
    QGridLayout *layout;
    ElementSelector *elementSelector;
    QWidget *projectSelector;

public:
    explicit MainWindow(Core *core, QWidget *parent = nullptr);
    ~MainWindow();

signals:

private slots:
    void changeWindow(QString &name, int id );
    void assetWindow();
    void shotWindow();
    void creatElementWindow();

public slots:
    void readProjectList();


};

#endif // MAINWINDOW_H
