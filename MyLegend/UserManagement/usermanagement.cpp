#include "usermanagement.h"
#include "ui_usermanagement.h"
#include <QMessageBox>
#include <QListView>
#include <QDebug>

UserManagement::UserManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManagement)
{
    ui->setupUi(this);

    uiInit();
    setWindowTitle("用户登录");
}

UserManagement::~UserManagement()
{
    delete ui;
}

UserManagement *UserManagement::m_pInstance = nullptr;
UserManagement *UserManagement::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new UserManagement();
    }
    return m_pInstance;
}

void UserManagement::uiInit()
{
    ui->stackedWidget_password->setCurrentIndex(0);
    ui->stackedWidget_userManagement->setCurrentIndex(0);
}

void UserManagement::on_pushButton_login_clicked()
{
    m_loginOrManage = 1;
    QString userName = ui->lineEdit_userName->text();
    QString password = ui->lineEdit_password->text();
    if(userName.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "错误!", "输入信息不完整!");
        return;
    }

    emit checkUserNamePasswordSignal(userName, password, true);
}

void UserManagement::checkUserNamePasswordCompleteSlot(int sta)
{
    if(sta == 1)
    {
        if(m_loginOrManage == 1)
        {
            ui->lineEdit_userName->clear();
            ui->lineEdit_password->clear();
            accept();
        }
    }
    else if(sta == 2)
    {
        QMessageBox::warning(this, "错误!", "密码错误!");
    }
    else if(sta == 0)
    {
        QMessageBox::warning(this, "错误!", "该用户名不存在!");
    }
}

void UserManagement::on_pushButton_exit_clicked()
{
    reject();
}

void UserManagement::on_pushButton_modifyPassword_clicked()
{
    ui->stackedWidget_password->setCurrentIndex(1);
}

void UserManagement::on_pushButton_modifyConfirm_clicked()
{
    m_loginOrManage = 2;
    QString userName = ui->lineEdit_userName->text();
    QString oldPassword = ui->lineEdit_oldPassword->text();
    QString newPassword1 = ui->lineEdit_newPassword1->text();
    QString newPassword2 = ui->lineEdit_newPassword2->text();
    if(userName.isEmpty() || oldPassword.isEmpty() || newPassword1.isEmpty() || newPassword2.isEmpty())
    {
        QMessageBox::warning(this, "错误!", "输入信息不完整!");
        return;
    }

    if(newPassword1 != newPassword2)
    {
        QMessageBox::warning(this, "错误!", "两次输入密码不同,请重新输入密码!");
        return;
    }

    emit modifyPasswordSignal(userName, oldPassword, newPassword1);
}

void UserManagement::modifyPasswordCompleteSlot(bool flag)
{
    if(flag)
        QMessageBox::information(this, "成功!", "修改密码成功!");
    else
        QMessageBox::warning(this, "失败!", "修改密码失败!");
}

void UserManagement::on_pushButton_modifyCancel_clicked()
{
    ui->stackedWidget_password->setCurrentIndex(0);
}

void UserManagement::on_pushButton_createUser_clicked()
{
    ui->stackedWidget_userManagement->setCurrentIndex(1);
}

void UserManagement::on_pushButton_userManagement_addUser_clicked()
{
    QString userName = ui->lineEdit_userManagement_userName->text();
    QString password = ui->lineEdit_userManagement_password->text();
    if(userName.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "错误!", "输入信息不完整!");
        return;
    }

    emit addNewUserSignal(userName, password);
}

void UserManagement::addNewUserCompleteSlot(int sta)
{
    if(sta == 1)
    {
        QMessageBox::information(this, "成功!", "增加用户成功!");
    }
    else if(sta == -1)
    {
        QMessageBox::warning(this, "失败!", "增加用户失败!");
    }
    else if(sta == 0)
    {
        QMessageBox::warning(this, "失败!", "该用户名已存在!");
    }
}

void UserManagement::on_pushButton_userManagement_back_clicked()
{
    ui->stackedWidget_userManagement->setCurrentIndex(0);
    setWindowTitle("用户登录");
}
