#ifndef PROJECTBUTTON_H
#define PROJECTBUTTON_H

#include <QPushButton>
#include <QDebug>

class ProjectButton : public QPushButton
{
    Q_OBJECT

private:
    QString name;
    int id;

public:
    ProjectButton();
    ProjectButton(const QString &text);
    void setInfo(const QString &name,int id);
    QString projectName();
    int projectId();
    ~ProjectButton();

signals:
    void selectProject(QString &name,int id);

private slots:
    void emitSignal();

};

#endif // PROJECTBUTTON_H
