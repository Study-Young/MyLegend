#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QDialog>

namespace Ui {
class UserManagement;
}

class UserManagement : public QDialog
{
    Q_OBJECT

public:
    static UserManagement* getInstance();
    ~UserManagement();

public slots:
    void checkUserNamePasswordCompleteSlot(int sta);
    void modifyPasswordCompleteSlot(bool flag);
    void addNewUserCompleteSlot(int sta);

signals:
    void checkUserNamePasswordSignal(QString userName, QString password, bool flag);
    void modifyPasswordSignal(QString userName, QString oldPassword, QString newPassword);
    void addNewUserSignal(QString userName, QString password);

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_modifyPassword_clicked();
    void on_pushButton_modifyConfirm_clicked();
    void on_pushButton_modifyCancel_clicked();

    void on_pushButton_createUser_clicked();
    void on_pushButton_userManagement_addUser_clicked();
    void on_pushButton_userManagement_back_clicked();



private:
    explicit UserManagement(QWidget *parent = nullptr);
    void uiInit();

private:
    Ui::UserManagement *ui;

    static UserManagement* m_pInstance;

    int m_loginOrManage;
};

#endif // USERMANAGEMENT_H
