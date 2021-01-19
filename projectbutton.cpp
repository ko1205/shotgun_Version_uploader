#include "projectbutton.h"

ProjectButton::ProjectButton()
{

}

ProjectButton::ProjectButton(const QString &text) : QPushButton(text)
{
    connect(this,SIGNAL(clicked(bool)),this,SLOT(emitSignal()));
}

ProjectButton::~ProjectButton()
{

}

void ProjectButton::setInfo(const QString &name, int id)
{
    this->name = name;
    this->id = id;
}

QString ProjectButton::projectName()
{
    return this->name;
}

int ProjectButton::projectId()
{
    return this->id;
}

void ProjectButton::emitSignal()
{
    qDebug()<< "emit show";
    emit selectProject(this->name,this->id);
}
