#pragma once
#include <QtWidgets/QMainWindow>
#include <QSqlTableModel>
#include "ui_MainWindow.h"
#include "SavePicThread.h"
#include "SaveDataThread.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	
private:
	Ui::MainWindowClass ui;
	QSqlTableModel *model;
	SavePicThread *picThread;
	SaveDataThread *dataThread;
	QStringList headerList;
	QStringList dataList;
	QStringList picDir;
	bool hasPicProgressBarMaxSet;
	bool hasDataProgressBarMaxSet;

	void query(QSqlTableModel *srcTable, QDate dateStart, QDate dateEnd);
private slots:
void on_Query_clicked();
void on_Save_clicked();
void on_Add_clicked();
void setPicProgress(int max,int value);
void setDataProgress(int max, int value);
};
