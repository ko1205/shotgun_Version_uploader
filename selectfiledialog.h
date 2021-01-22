#ifndef SELECTFILEDIALOG_H
#define SELECTFILEDIALOG_H

#include <QDialog>
#include "core.h"
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <QFileDialog>
#include <QDebug>
#include "jobthread.h"
#include <QProcess>
#include <QFileInfo>

class SelectFileDialog : public QDialog
{
    Q_OBJECT

private:
    Core *core;
    QLabel *label;
    QGridLayout *layout;
    QPushButton *fileSelectBtn;
    QTextBrowser*messageWindow;
    QString selectedFile;
//    JobThread *thread;
    QProcess *process;

    int transcodingStep;
    QDir tmpDir;
    QStringList outFormat;
    QStringList outputFile;

public:
    SelectFileDialog(Core *core);
    ~SelectFileDialog();

private slots:
    void clickSelectFile();
    void clickCancel();
    void writeMessage();

    void transeCodingProcess();
};

#endif // SELECTFILEDIALOG_H
