#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "core.h"
#include "mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

class Dialog : public QDialog
{
    Q_OBJECT

private:
    Core *core;
    MainWindow *mainWindow;

    QPushButton *connectButton;
    QLabel      *urlLabel;
    QLabel      *loginLabel;
    QLabel      *passwdLabel;
    QLineEdit   *urlEdit;
    QLineEdit   *loginEdit;
    QLineEdit   *passwdEdit;
    QGridLayout *gridLayout;
    QVBoxLayout *vboxlayout;
    QHBoxLayout *hboxlayout;

public:
    Dialog(Core *core,MainWindow *mainWindow, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void connectSite();
    void setConnnectBtnDisable();
};
#endif // DIALOG_H
