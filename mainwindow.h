#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include <QStandardItemModel>

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


    void on_pushButtonExit_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

    void on_checkBox_clicked(bool checked);

    void on_listView_entered(const QModelIndex &index);

private:
    void fillModel();
    Ui::MainWindow *ui;
    QModelIndex index;
    QStandardItemModel *model;
    QStringListModel *modelStr;
    //QItemSelectionModel *selectionModel;
    QStringList strList = {"С++", "Python", "Java", "C#","PHP","JavaScript"};
    bool listMode = true; // true - list (checkbox unchecked), false - icon.

};
#endif // MAINWINDOW_H
