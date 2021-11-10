#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QRadioButton>
#include <stdio.h>

#include <QAction>
#include <QMenu>
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

  ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(ui->tableWidget, SIGNAL(customContextMenuRequested(const QPoint &)),
          this, SLOT(MContextMenu(const QPoint &)));
}

Widget::~Widget() {
  serial.close();
  delete ui;
}

void Widget::MContextMenu(const QPoint &pos) {
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);
  menu->addAction(tr("关闭所有led"), this, SLOT(CloseAllLed()));
  menu->addAction(tr("切换模式"), this, SLOT(ChangeMode()));
  menu->popup(ui->tableWidget->mapToGlobal(pos));
  ui->tableWidget->clearSelection();
}

void Widget::CloseAllLed() {
  serial.write("0");
  serial.write(" ");
  serial.write("0");
  serial.write(",");
}

void Widget::ChangeMode() {
  if (ui->tableWidget->selectionMode() == QAbstractItemView::SingleSelection) {
    ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
  } else {
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  }
}

void Widget::on_tableWidget_clicked(const QModelIndex &index) {
  qDebug() << "choosed pos " << index.row() + 1 << " " << index.column() + 1
           << endl;
  serial.write(QString::number(index.row() + 1).toLocal8Bit().data());
  serial.write(" ");
  serial.write(QString::number(index.column() + 1).toLocal8Bit().data());
  serial.write(",");
}
