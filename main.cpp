/*임시용 프로그램
 * 메모리관리 안됨
 * 설계없이 생각나는대로 작성
 * 로그인시에 계정 페스워드 체크 구문 없음
*/


#include "dialog.h"
#include "core.h"
#include "mainwindow.h"

#include <QApplication>
//#include <QCoreApplication>
//#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Core core;
    MainWindow mainWindow(&core);
    Dialog dialog(&core,&mainWindow);
    dialog.show();
//    qDebug() << QCoreApplication::applicationFilePath();
    return a.exec();
}
