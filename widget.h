#ifndef WIDGET_H
#define WIDGET_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QWidget>
namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

private slots:
  void on_tableWidget_clicked(const QModelIndex &index);
  void MContextMenu(const QPoint &);
  void CloseAllLed();
  void ChangeMode();

private:
  Ui::Widget *ui;
  QSerialPort serial;
};

#endif // WIDGET_H
