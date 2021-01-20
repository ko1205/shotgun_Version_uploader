#ifndef SELECTFILEDIALOG_H
#define SELECTFILEDIALOG_H

#include <QDialog>
#include "core.h"
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QDebug>

class SelectFileDialog : public QDialog
{
    Q_OBJECT

private:
    Core *core;
    QLabel *label;
    QGridLayout *layout;
    QPushButton *fileSelectBtn;
    QPlainTextEdit *messageWindow;
    QString selectedFile;
//    QFileDialog *fileDialog;

public:
    SelectFileDialog(Core *core);

private slots:
    void clickSelectFile();
};

#endif // SELECTFILEDIALOG_H
