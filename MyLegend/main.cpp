#include "mainwindow.h"
#include "Model/splashscreen.h"
#include "DataBase/database.h"
#include "UserManagement/usermanagement.h"
#include "GameService/gameserviceglobal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置QSetting在注册列表中默认保存位置
    QCoreApplication::setOrganizationName("Young");
    QCoreApplication::setApplicationName("Legend");

    SplashScreen *splash = new SplashScreen();
    splash->show();
    splash->showMessage("软件初始化...", Qt::AlignLeft |Qt::AlignBottom, Qt::black);

    GameServiceGlobal::getInstance();

    MainWindow w;
    splash->finish(&w);
    delete splash;

    if(UserManagement::getInstance()->exec() == QDialog::Rejected)
    {
        exit(0);
    }

    w.updateCurrentUserInfo();
    w.show();
    return a.exec();
}
