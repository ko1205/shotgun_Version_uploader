#include "core.h"
#include <QDebug>

Core::Core(QObject *parent) : QObject(parent)
{
    Py_Initialize();
    PyRun_SimpleString("import sys\n"
                       "sys.path.insert(0,'')\n");

//    Py_DECREF(pName);
//    if(pModule != NULL){
//        qDebug() << "Shotgun Module OK";
////        pFunc = PyObject_GetAttrString(pModule,"connect");
//        if(pFunc != NULL){
//            qDebug() << "Func OK";
//        }
//    }


}

Core::~Core()
{
    if(pModule != NULL){
        Py_DECREF(pModule);
    }
    if(pFunc != NULL){
        Py_DECREF(pFunc);
    }
    if(pSG != NULL){
//        Py_DECREF(pSG);
    }
    Py_Finalize();
}

bool Core::connectSite(QString site, QString login, QString passwd)
{
    PyObject *pName = PyString_FromString("run");
    pModule = PyImport_Import(pName);
    pFunc = PyObject_GetAttrString(pModule,"connect");
    qDebug() << site << login << passwd;

    this->login = login;

    PyObject *pySite, *pyLogin, *pyPasswd, *pArgs ;

    pySite =PyString_FromString(site.toLocal8Bit());
    pyLogin = PyString_FromString(login.toLocal8Bit());
    pyPasswd = PyString_FromString(passwd.toLocal8Bit());

    pArgs = PyTuple_New(3);

    PyTuple_SetItem(pArgs,0,pySite);
    PyTuple_SetItem(pArgs,1,pyLogin);
    PyTuple_SetItem(pArgs,2,pyPasswd);
    pSG = PyObject_CallObject(pFunc,pArgs);
    Py_DECREF(pySite);
    Py_DECREF(pyLogin);
    Py_DECREF(pyPasswd);
//    Py_DECREF(pArgs);
    if(pSG != NULL){
//        qDebug() << "SG OK";
        return true;
    }else{
        return false;
    }
}

void Core::readProjcetList()
{
    pFunc = PyObject_GetAttrString(pModule,"findProjectList");
    PyObject *pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs,0,pSG);
    PyObject *result = PyObject_CallObject(pFunc,pArgs);
//    Py_DECREF(pFunc);
//    Py_DECREF(pArgs);
    qDebug() << PyList_Size(result);
    passingProjectList(result);
}

void Core::passingProjectList(PyObject *list)
{
    int size = PyList_Size(list);
    qList.clear();

    for(int i = 0; i< size; i++){
        PyObject *item = PyList_GetItem(list,i);
        PyObject *name = PyDict_GetItemString(item,"name");
        PyObject *id = PyDict_GetItemString(item,"id");
//        qDebug() << PyString_AsString(name);
//        qDebug() << PyInt_AsLong(id);
        QMap<QString,QString> qItem;
        qItem["name"] = PyString_AsString(name);
        qItem["id"] = QString::number(PyInt_AsLong(id));
        qList.append(qItem);
    }

}

QStringList Core::getAssetTypeList()
{
    QStringList assetTypeList;
    qDebug() << "getAssetTypeList Func Run";
    pFunc = PyObject_GetAttrString(pModule,"findAssetTypeList");
    PyObject *pArgs = PyTuple_New(2);
    PyObject *projectID = PyInt_FromSize_t(selectedProject);
    PyTuple_SetItem(pArgs,0,pSG);
    PyTuple_SetItem(pArgs,1,projectID);
    PyObject *result = PyObject_CallObject(pFunc,pArgs);

    int size = PyList_Size(result);
    for(int i=0 ; i < size; i++)
    {
        PyObject *item = PyList_GetItem(result,i);
        QString assetType = PyString_AsString(item);
        assetTypeList.append(assetType);
    }
    return assetTypeList;
}

QStringList Core::getSequenceList()
{
    QStringList sequenceList;
    qDebug() << "getAssetTypeList Func Run";
    pFunc = PyObject_GetAttrString(pModule,"findSequenceList");
    PyObject *pArgs = PyTuple_New(2);
    PyObject *projectID = PyInt_FromSize_t(selectedProject);
    PyTuple_SetItem(pArgs,0,pSG);
    PyTuple_SetItem(pArgs,1,projectID);
    PyObject *result = PyObject_CallObject(pFunc,pArgs);

    int size = PyList_Size(result);
    for(int i=0 ; i < size; i++)
    {
        PyObject *item = PyList_GetItem(result,i);
        QString sequenceCode = PyString_AsString(item);
        sequenceList.append(sequenceCode);
    }
    return sequenceList;
}

QStringList Core::getAssetList()
{
    QStringList assetList;
    pFunc = PyObject_GetAttrString(pModule,"findAssetList");
    PyObject *pArgs = PyTuple_New(3);
    PyObject *projectID = PyInt_FromSize_t(selectedProject);
    PyObject *assetType = PyString_FromString(leftViewCurrent.toLocal8Bit());
    PyTuple_SetItem(pArgs,0,pSG);
    PyTuple_SetItem(pArgs,1,projectID);
    PyTuple_SetItem(pArgs,2,assetType);
    PyObject *result = PyObject_CallObject(pFunc,pArgs);

    int size = PyList_Size(result);
    for(int i=0 ; i < size; i++)
    {
        PyObject *item = PyList_GetItem(result,i);
        QString assetCode = PyString_AsString(item);
        assetList.append(assetCode);
    }
    return assetList;
}

QStringList Core::getShotList()
{
    QStringList shotList;
    pFunc = PyObject_GetAttrString(pModule,"findShotList");
    PyObject *pArgs = PyTuple_New(3);
    PyObject *projectID = PyInt_FromSize_t(selectedProject);
    PyObject *sequenceCode = PyString_FromString(leftViewCurrent.toLocal8Bit());
    PyTuple_SetItem(pArgs,0,pSG);
    PyTuple_SetItem(pArgs,1,projectID);
    PyTuple_SetItem(pArgs,2,sequenceCode);
    PyObject *result = PyObject_CallObject(pFunc,pArgs);

    int size = PyList_Size(result);
    for(int i=0 ; i < size; i++)
    {
        PyObject *item = PyList_GetItem(result,i);
        QString shotCode = PyString_AsString(item);
        shotList.append(shotCode);
    }
    return shotList;
}

QStringList Core::getAssetTaskList()
{
    QStringList taskList;
    pFunc = PyObject_GetAttrString(pModule,"findAssetTaskList");
    PyObject *pArgs = PyTuple_New(3);
    PyObject *projectID = PyInt_FromSize_t(selectedProject);
    PyObject *assetCode = PyString_FromString(centerViewCurrent.toLocal8Bit());
    PyTuple_SetItem(pArgs,0,pSG);
    PyTuple_SetItem(pArgs,1,projectID);
    PyTuple_SetItem(pArgs,2,assetCode);
    PyObject *result = PyObject_CallObject(pFunc,pArgs);

    int size = PyList_Size(result);
    for(int i=0 ; i < size; i++)
    {
        PyObject *item = PyList_GetItem(result,i);
        QString taskContent = PyString_AsString(item);
        taskList.append(taskContent);
    }
    return taskList;
}

QStringList Core::getShotTaskList()
{
    QStringList taskList;
    pFunc = PyObject_GetAttrString(pModule,"findShotTaskList");
    PyObject *pArgs = PyTuple_New(3);
    PyObject *projectID = PyInt_FromSize_t(selectedProject);
    PyObject *shotCode = PyString_FromString(centerViewCurrent.toLocal8Bit());
    PyTuple_SetItem(pArgs,0,pSG);
    PyTuple_SetItem(pArgs,1,projectID);
    PyTuple_SetItem(pArgs,2,shotCode);
    PyObject *result = PyObject_CallObject(pFunc,pArgs);

    int size = PyList_Size(result);
    for(int i=0 ; i < size; i++)
    {
        PyObject *item = PyList_GetItem(result,i);
        QString taskContent = PyString_AsString(item);
        taskList.append(taskContent);
    }
    return taskList;
}

bool Core::uploadMovie(QStringList outputFile, QString basename)
{
    if(selectedElement == ASSET)
    {
        qDebug() << "Asset Version upLoad";
        pFunc = PyObject_GetAttrString(pModule,"uploadAssetVersion");
        PyObject *pArgs = PyTuple_New(9);
        PyObject *projectID = PyInt_FromSize_t(selectedProject);
        PyObject *assetCode = PyString_FromString(centerViewCurrent.toLocal8Bit());
        PyObject *taskContent = PyString_FromString(rightViewCurrent.toLocal8Bit());
        PyObject *pybasename = PyString_FromString(basename.toLocal8Bit());
        PyObject *orgMovie = PyString_FromString(selectedFile.toLocal8Bit());
        PyObject *mp4 = PyString_FromString(outputFile.at(0).toLocal8Bit());
        PyObject *webm = PyString_FromString(outputFile.at(1).toLocal8Bit());
        PyObject *thumbnail = PyString_FromString(outputFile.at(2).toLocal8Bit());

        PyTuple_SetItem(pArgs,0,pSG);
        PyTuple_SetItem(pArgs,1,projectID);
        PyTuple_SetItem(pArgs,2,assetCode);
        PyTuple_SetItem(pArgs,3,taskContent);
        PyTuple_SetItem(pArgs,4,pybasename);
        PyTuple_SetItem(pArgs,5,orgMovie);
        PyTuple_SetItem(pArgs,6,mp4);
        PyTuple_SetItem(pArgs,7,webm);
        PyTuple_SetItem(pArgs,8,thumbnail);

        PyObject *result = PyObject_CallObject(pFunc,pArgs);
        qDebug() << "upload fin";

    }else if(selectedElement == SHOT){
        qDebug() << "Shot Version upLoad";
        pFunc = PyObject_GetAttrString(pModule,"uploadShotVersion");
        PyObject *pArgs = PyTuple_New(9);
        PyObject *projectID = PyInt_FromSize_t(selectedProject);
        PyObject *shotCode = PyString_FromString(centerViewCurrent.toLocal8Bit());
        PyObject *taskContent = PyString_FromString(rightViewCurrent.toLocal8Bit());
        PyObject *pybasename = PyString_FromString(basename.toLocal8Bit());
        PyObject *orgMovie = PyString_FromString(selectedFile.toLocal8Bit());
        PyObject *mp4 = PyString_FromString(outputFile.at(0).toLocal8Bit());
        PyObject *webm = PyString_FromString(outputFile.at(1).toLocal8Bit());
        PyObject *thumbnail = PyString_FromString(outputFile.at(2).toLocal8Bit());

        PyTuple_SetItem(pArgs,0,pSG);
        PyTuple_SetItem(pArgs,1,projectID);
        PyTuple_SetItem(pArgs,2,shotCode);
        PyTuple_SetItem(pArgs,3,taskContent);
        PyTuple_SetItem(pArgs,4,pybasename);
        PyTuple_SetItem(pArgs,5,orgMovie);
        PyTuple_SetItem(pArgs,6,mp4);
        PyTuple_SetItem(pArgs,7,webm);
        PyTuple_SetItem(pArgs,8,thumbnail);

        PyObject *result = PyObject_CallObject(pFunc,pArgs);
        qDebug() << "upload fin";
    }
    return true;
}

bool Core::uploadImage(QString basename)
{
    qDebug() << "upload Image Func run";
    if(selectedElement == ASSET){
        qDebug() << "Asset Version upLoad";
        pFunc = PyObject_GetAttrString(pModule,"uploadAssetVersionImage");
        PyObject *pArgs = PyTuple_New(6);
        PyObject *projectID = PyInt_FromSize_t(selectedProject);
        PyObject *assetCode = PyString_FromString(centerViewCurrent.toLocal8Bit());
        PyObject *taskContent = PyString_FromString(rightViewCurrent.toLocal8Bit());
        PyObject *pybasename = PyString_FromString(basename.toLocal8Bit());
        PyObject *orgImage = PyString_FromString(selectedFile.toLocal8Bit());
//        PyObject *mp4 = PyString_FromString(outputFile.at(0).toLocal8Bit());
//        PyObject *webm = PyString_FromString(outputFile.at(1).toLocal8Bit());
//        PyObject *thumbnail = PyString_FromString(outputFile.at(2).toLocal8Bit());

        PyTuple_SetItem(pArgs,0,pSG);
        PyTuple_SetItem(pArgs,1,projectID);
        PyTuple_SetItem(pArgs,2,assetCode);
        PyTuple_SetItem(pArgs,3,taskContent);
        PyTuple_SetItem(pArgs,4,pybasename);
        PyTuple_SetItem(pArgs,5,orgImage);
//        PyTuple_SetItem(pArgs,6,mp4);
//        PyTuple_SetItem(pArgs,7,webm);
//        PyTuple_SetItem(pArgs,8,thumbnail);

        PyObject *result = PyObject_CallObject(pFunc,pArgs);
        qDebug() << "upload fin";
    }else if(selectedElement == SHOT){
        qDebug() << "Asset Version upLoad";
        pFunc = PyObject_GetAttrString(pModule,"uploadShotVersionImage");
        PyObject *pArgs = PyTuple_New(6);
        PyObject *projectID = PyInt_FromSize_t(selectedProject);
        PyObject *shotCode = PyString_FromString(centerViewCurrent.toLocal8Bit());
        PyObject *taskContent = PyString_FromString(rightViewCurrent.toLocal8Bit());
        PyObject *pybasename = PyString_FromString(basename.toLocal8Bit());
        PyObject *orgImage = PyString_FromString(selectedFile.toLocal8Bit());
//        PyObject *mp4 = PyString_FromString(outputFile.at(0).toLocal8Bit());
//        PyObject *webm = PyString_FromString(outputFile.at(1).toLocal8Bit());
//        PyObject *thumbnail = PyString_FromString(outputFile.at(2).toLocal8Bit());

        PyTuple_SetItem(pArgs,0,pSG);
        PyTuple_SetItem(pArgs,1,projectID);
        PyTuple_SetItem(pArgs,2,shotCode);
        PyTuple_SetItem(pArgs,3,taskContent);
        PyTuple_SetItem(pArgs,4,pybasename);
        PyTuple_SetItem(pArgs,5,orgImage);
//        PyTuple_SetItem(pArgs,6,mp4);
//        PyTuple_SetItem(pArgs,7,webm);
//        PyTuple_SetItem(pArgs,8,thumbnail);

        PyObject *result = PyObject_CallObject(pFunc,pArgs);
        qDebug() << "upload fin";
    }
    return true;
}

void Core::setSelectedProject(int id, QString name)
{
    selectedProject = id;
    selectedProjectName = name;
}

int Core::readSelectedProject()
{
    return selectedProject;
}

void Core::setElement(int element)
{
    selectedElement = element;
    qDebug() << selectedElement;
}

void Core::setLeftViewCurrent(QString text)
{
    leftViewCurrent = text;
}

void Core::setCenterViewCurrent(QString text)
{
    centerViewCurrent = text;
}

void Core::setRightViewCurrent(QString text)
{
    rightViewCurrent = text;
}

void Core::setSelectedFile(QString filePath)
{
    selectedFile = filePath;
}


QString Core::getProjectName()
{
    return selectedProjectName;
}

QString Core::getLoginUser()
{
    return login;
}

int Core::getElementType()
{
    return selectedElement;
}

QString Core::getLeftViewCurrent()
{
    return leftViewCurrent;
}

QString Core::getCenterViewCurrent()
{
    return centerViewCurrent;
}

QString Core::getRightViewCurrent()
{
    return rightViewCurrent;
}
