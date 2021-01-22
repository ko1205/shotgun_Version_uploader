#ifndef CORE_H
#define CORE_H

enum element{ ASSET = 0,SHOT = 1 };

#include <QObject>
#include <Python.h>


class Core : public QObject
{
    Q_OBJECT

private:
    PyObject *pModule;
    PyObject *pFunc;
    PyObject *pSG;

    QString login;
    int selectedProject;
    QString selectedProjectName;
    int selectedElement;

    QString leftViewCurrent;
    QString centerViewCurrent;
    QString rightViewCurrent;

    void passingProjectList(PyObject *list);


public:
    QList<QMap<QString,QString> > qList;

    explicit Core(QObject *parent = nullptr);
    ~Core();
    bool connectSite(QString site, QString login, QString passwd);
    void readProjcetList();
    void setSelectedProject(int id, QString name);
    int readSelectedProject();
    void setElement(int element);

    QStringList getAssetTypeList();
    QStringList getSequenceList();
    QStringList getAssetList();
    QStringList getShotList();
    QStringList getAssetTaskList();
    QStringList getShotTaskList();

    bool uploadMovie(QString mp4,QString webm, QString thumbnail);

    void setLeftViewCurrent(QString text);
    void setCenterViewCurrent(QString text);
    void setRightViewCurrent(QString text);

    QString getProjectName();
    QString getLoginUser();
    int getElementType();
    QString getLeftViewCurrent();
    QString getCenterViewCurrent();
    QString getRightViewCurrent();



signals:

};

#endif // CORE_H
