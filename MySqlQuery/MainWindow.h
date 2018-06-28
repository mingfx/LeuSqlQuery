#pragma once
#include <QtWidgets/QMainWindow>
#include <QSqlTableModel>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	
private:
	Ui::MainWindowClass ui;
	QSqlTableModel *model;
	QStringList headerList;
	QStringList dataList;
	QStringList picDir;

	void query(QSqlTableModel *srcTable, QDate dateStart, QDate dateEnd);
private slots:
void on_Query_clicked();
void on_Save_clicked();
};
