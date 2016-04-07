#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <Encryption.h>

QString filename;
QFile read_file, encryptedFile;
QString text1, text2, text3;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("Выберите файл");
    ui->pushButton_3->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    filename.clear();
    filename=QFileDialog::getOpenFileName(this, tr("Open Key File"), "C://", "Key file (*.key)");
    ui->lineEdit->setText(filename);
    ui->pushButton_2->setEnabled(1);
}


void MainWindow::on_pushButton_2_clicked()
{

    if (filename.isEmpty()) QMessageBox::warning(0, tr("Ошибка доступа"), "Выберите файл");
    else {

        read_file.setFileName(filename);

        if (!read_file.exists()) {QMessageBox::warning(0, tr("Ошибка доступа - файла не существует"), "Выберите существующий файл"); return;}

        if(read_file.open(QIODevice::ReadOnly|QIODevice::Text)) //Вывод текста выбранного файла
        {
            QTextStream out(&read_file);
            out.setCodec("UTF-8");          // Установка кодека
            text1 = out.readAll();       // Считываем весь файл в QString
            read_file.close();
        }

        QString folder2;
        //while (folder2=="")
        {
        folder2=QFileDialog::getSaveFileName(this, tr("Выберете место сохранения ключ-лицензии"), "C://", tr("License file (*.lic)"));
        }
        if (folder2=="") return;
        encryptedFile.setFileName(folder2);


        if(encryptedFile.open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text))    //Копирование текста выбранного файла в новый + нужно добавить соль
        {
            QTextStream data2(&encryptedFile);
            data2.setCodec("UTF-8");

            text2=text1;
            text2=stringDecrypt(text2,"65sdfgh98sdf1sdf4");
            text2=stringEncrypt(text2,"456789ApOiNtR55$%^&*&^%$#");

            data2<<text2;
            encryptedFile.close();
            QMessageBox::information(0,"Success", "Файл лицензии был успешно создан!");
        }

       /* if(encryptedFile.open(QIODevice::ReadOnly|QIODevice::Text)) //Вывод полученного файла
        {
            QTextStream out(&encryptedFile);
            out.setCodec("UTF-8");          // Установка кодека
            text3 = out.readAll();       // Считываем весь файл в QString
            encryptedFile.close();
        }

        //if (!text1.isEmpty()) QMessageBox::information(this, tr("SimpleData"), text1);
        //if (!text3.isEmpty()) QMessageBox::information(this, tr("EncryptedKey"), text3);*/
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    filename=ui->lineEdit->text();
}

void MainWindow::on_pushButton_3_clicked()//FOR DEBUG
{
    filename.clear();
    filename=QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "All files (*.*)");
    ui->lineEdit->setText(filename);

    if (filename.isEmpty()) QMessageBox::warning(0, tr("Ошибка доступа"), "Выберите файл для расшифровки");
    else {

        read_file.setFileName(filename);

        if (!read_file.exists()) {QMessageBox::warning(0, tr("Ошибка доступа - файла не существует"), "Выберите существующий файл"); return;}

        if(read_file.open(QIODevice::ReadOnly|QIODevice::Text)) //Вывод текста выбранного файла
        {
            QTextStream out(&read_file);
            out.setCodec("UTF-8");          // Установка кодека
            text1 = out.readAll();       // Считываем весь файл в QString
            read_file.close();
        }


        encryptedFile.setFileName("C://MY QT PROJECTS//decryptedKey.lic");


        if(encryptedFile.open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text))    //Копирование текста выбранного файла в новый + нужно добавить соль
        {
            QTextStream data2(&encryptedFile);
            data2.setCodec("UTF-8");

            text2=text1;
            text2=stringDecrypt(text2,"65sdfgh98sdf1sdf4");

            data2<<text2;
            encryptedFile.close();
        }

        if(encryptedFile.open(QIODevice::ReadOnly|QIODevice::Text)) //Вывод полученного файла
        {
            QTextStream out(&encryptedFile);
            out.setCodec("UTF-8");          // Установка кодека
            text3 = out.readAll();       // Считываем весь файл в QString
            encryptedFile.close();
        }

        if (!text1.isEmpty()) QMessageBox::information(this, tr("SimpleData"), text1);
        if (!text3.isEmpty()) QMessageBox::information(this, tr("EncryptedKey"), text3);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    exit(1);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About Kursach Server"),
              tr("<h2>Created by Andrei Abramov SSAU group 6310</h2>"
              "<p>Copyright &copy; 2014 Adventorium Inc."
              "<p>It is a small application that "
              "<p>demonstrates my professional skills "));
}
