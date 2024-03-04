#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_openFile_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_write_clicked();

private:
    QString toXOREncryptUncrypt(QString src, const QChar key);

private:
    Ui::MainWindow *ui;

    QFile *m_file;
    bool m_openSta;
};
#endif // MAINWINDOW_H
