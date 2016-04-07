#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
/*ВСЕ ИНТЕРЕСНЫЕ ФУНКЦИИ
EncryptFile(L"C://MY QT PROJECTS//encryptedKey.txt");

if (encryptedFile.exists()) {encryptedFile.remove(); encryptedFile.setFileName("C://MY QT PROJECTS//encryptedKey");}

read_file.copy(filename,"C://MY QT PROJECTS//encryptedKey2");


ИДЕЯ! передавать данные компьютера и ключ - шифрованнными!

клиент шифрует первым шифром, и отправляет файл серверу
сервер - дешифрует полученные данные первым шифром, потом шифрует вторым, передаёт файл клиенту
клиент получает файл и дешифрует его вторым шифром
Если полученная последовательность равна отправленной - permission alloyed
ПРОФИТ!!!


*/
