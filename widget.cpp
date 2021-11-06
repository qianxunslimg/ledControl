#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QRadioButton>
#include <stdio.h>
#pragma execution_character_set("utf-8")

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  this->setWindowTitle("肖哥的LED点阵");
  //   QIcon mIcon("1");
  //   this->setWindowIcon(mIcon);:/rc/rc/LED.png
  setWindowIcon(QIcon(":/rc/rc/LED.png"));
  serial.setPortName("COM3");
  serial.setBaudRate(QSerialPort::Baud9600);
  serial.setParity(QSerialPort::NoParity);
  serial.setDataBits(QSerialPort::Data8);
  serial.setStopBits(QSerialPort::OneStop);
  serial.setFlowControl(QSerialPort::NoFlowControl);

  if (!serial.open(QIODevice::ReadWrite))
    QMessageBox::warning(this, "警告", "打开串口COM3失败！");

  ui->tableWidget->verticalHeader()->setVisible(0);
  ui->tableWidget->horizontalHeader()->setVisible(0);
  ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

Widget::~Widget() {
  serial.close();
  delete ui;
}

void Widget::on_tableWidget_clicked(const QModelIndex &index) {
  qDebug() << "choosed pos " << index.row() + 1 << " " << index.column() + 1
           << endl;
  serial.write(QString::number(index.row() + 1).toLocal8Bit().data());
  serial.write(QString::number(index.column() + 1).toLocal8Bit().data());
}
