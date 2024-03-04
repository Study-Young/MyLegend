#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_openSta = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_openFile_clicked()
{
    QString filePath;
    QString fileName = QFileDialog::getOpenFileName(this, tr("文件路径"), filePath, tr("*.ini"));
    ui->label_filePath->setText(fileName);

    m_file = new QFile(fileName);
    if(!m_file->open(QFile::ReadWrite | QIODevice::Append))
    {
        m_openSta = false;
        return;
    }
    m_openSta = true;
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->textBrowser_input->clear();
}

void MainWindow::on_pushButton_write_clicked()
{
    //weapon_1,1,旋风剑,1,1,50,100,50,1000,1,10,20,10,200,3,20,40,20,300
    //exp_1,1,经验怪,10,10,30,20,500
    if(m_openSta)
    {
        QString dataStr = ui->textBrowser_input->toPlainText();
        QStringList dataStrList = dataStr.simplified().split(";");
        for(int i=0; i<dataStrList.size(); i++)
        {
            QString curStr = dataStrList.at(i).simplified();
            if(!curStr.isEmpty())
            {
                QByteArray writeDataArr = curStr.toUtf8();
                m_file->write(writeDataArr.toBase64());
                m_file->write("\n");
                m_file->flush();
            }
        }
        QMessageBox::information(this, "成功", "写入成功!");
    }
}

