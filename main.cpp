#include "widget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;

  QFile qssFile("D://vstest//untitled2//lightblue.css"); //资源文件":/css.qss"
  qssFile.open(QFile::ReadOnly);
  if (qssFile.isOpen()) {
    QString qss = QLatin1String(qssFile.readAll()); //读取
    qApp->setStyleSheet(qss);                       //设置
    qssFile.close();
  }
  w.show();

  return a.exec();
}
