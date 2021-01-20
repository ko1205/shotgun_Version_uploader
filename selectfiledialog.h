#ifndef SELECTFILEDIALOG_H
#define SELECTFILEDIALOG_H

#include <QDialog>
#include "core.h"

class SelectFileDialog : public QDialog
{
    Q_OBJECT

private:
    Core *core;

public:
    SelectFileDialog(Core *core);
};

#endif // SELECTFILEDIALOG_H
