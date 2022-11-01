#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QModelIndex>
#include <QModelIndexList>
#include <QCoreApplication>
#include <QStandardItemModel>
/*
 * Создать список с названиями языков программирования
 * (С++, Python, Java, C#, PHP, JavaScript). Для каждого
 * элемента списка рядом отобразить иконку с логотипом
 * языка программирования. Предусмотреть возможно изменения
 * текста в каждом элементе списка. Добавить возможность
 * перемещения элементов в списке. Создать кнопку для
 * добавления нового языка программирования в список.
 *  Иконку для него поставить любую (по-умолчанию).
 *  Создать кнопку для удаления элемента из списка (в этом
 *  случае элемент должен быть выбран). Создать CheckBox и
 *  когда будет стоять галочка, отобразить список в режиме
 *  иконок (нужен метод setViewMode()). Когда галочка не
 *  стоит, то список должен отображаться в обычном режиме.
 *  Подсказка: используйте справку qt, вызов F1.
 * */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // тут я сделал две модели чтобы получить два представления
    // без картинок и с картинками. Но добиться синхронизации
    // данных в моделях после редактирования элемента у меня пока
    // не получилось.
    // Кроме того перемещение (drug & drop) реализовано только для
    // отображения без иконок. По какой причине свойства ui касающиеся
    // drug & drop не влияют на QStandardItemModel я не знаю.
    model=new QStandardItemModel(strList.size(),1,this);
    modelStr = new QStringListModel(strList,this);

    fillModel();
  //  selectionModel = new QItemSelectionModel(model, this);

    ui->listView->setModel(modelStr); // после этого элементы уже можно редактировать после двойного клика
    ui->listView->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);
    //ui->listView->setSelectionModel(selectionModel);

}

void MainWindow::fillModel()
{
    index=model->index(0,0);
    model->setData(index,strList[0],Qt::DisplayRole);
    model->setData(index,QIcon("./pix/cpp.jpg"), Qt::DecorationRole);

    index=model->index(1,0);
    model->setData(index,strList[1],Qt::DisplayRole);
    model->setData(index,QIcon("./pix/python.jpg"), Qt::DecorationRole);

    index=model->index(2,0);
    model->setData(index,strList[2],Qt::DisplayRole);
    model->setData(index,QIcon("./pix/java.jpg"), Qt::DecorationRole);

    index=model->index(3,0);
    model->setData(index,strList[3],Qt::DisplayRole);
    model->setData(index,QIcon("./pix/csharp.jpg"), Qt::DecorationRole);

    index=model->index(4,0);
    model->setData(index,strList[4],Qt::DisplayRole);
    model->setData(index,QIcon("./pix/php.jpg"), Qt::DecorationRole);

    index=model->index(5,0);
    model->setData(index,strList[5],Qt::DisplayRole);
    model->setData(index,QIcon("./pix/javascript.jpg"), Qt::DecorationRole);
}



MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete modelStr;
    //delete selectionModel;
}


void MainWindow::on_pushButtonExit_clicked()
{
    QCoreApplication::exit(0);
}


void MainWindow::on_pushButtonAdd_clicked()
{
    int breakpoint=0;
    model->insertRow(model->rowCount());
    index=model->index(model->rowCount()-1,0);
    model->setData(index,"NEWITEM",Qt::DisplayRole);
    model->setData(index,QIcon("./pix/new.jpg"), Qt::DecorationRole);
    strList.append("NEWITEM");
    modelStr->insertRow(modelStr->rowCount());
    index=modelStr->index(model->rowCount()-1,0);
    modelStr->setData(index,"NEWITEM",Qt::DisplayRole);
    if (listMode == false) {
        ui->listView->setModel(model);
    }
    else {
        ui->listView->setModel(modelStr);
    }
    breakpoint++;
//    selectionModel->clearSelection();
/*  это не работает так:
 *  index=model->index(model->rowCount());
    if(index.isValid()) {
        selectionModel->select(index,QItemSelectionModel::Select);
    }
*/

}

void MainWindow::on_pushButtonDelete_clicked()
{
    int row = ui->listView->currentIndex().row();
    model->removeRow(row);
    modelStr->removeRow(row);

}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked) {
        ui->listView->setModel(model);
        ui->listView->setViewMode(QListView::IconMode);
        listMode = false;
    }
    else {
        ui->listView->setModel(modelStr);
        ui->listView->setViewMode(QListView::ListMode);
        listMode = true;
    }
}


void MainWindow::on_listView_entered(const QModelIndex &index)
{
    // Всё ниже не работает. Возможно on_listView_entered вызывается
    // не в момент когда завершено редактирование элемента списка.

    QString text;
    if(listMode) {
       // тут надо получить по индексу модели modelStr строку которую
       // вставлял и скопировать ее в другую модель model с таким же
       // индексом чтобы данные в двух моделях были синхронизированы
       // при вводе (чтобы одинаковыми строки были после редактирования).
       text = modelStr->data(index, Qt::DisplayRole).toString();
       model->setData(index,text,Qt::DisplayRole);
       ui->listView->setModel(modelStr);
    }
    else {
        // тоже самое, только из model в modelStr.
        text = model->data(index, Qt::DisplayRole).toString();
        modelStr->setData(index,text,Qt::DisplayRole);
        ui->listView->setModel(model);
    }
}

