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
#include "jobthread.h"

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
    JobThread *thread;
//    QFileDialog *fileDialog;

public:
    SelectFileDialog(Core *core);
    ~SelectFileDialog();

private slots:
    void clickSelectFile();
    void clickCancel();
};

#endif // SELECTFILEDIALOG_H
