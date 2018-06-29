#pragma once
#include "ui_AddWidget.h"
#include <QSqlTableModel>

class AddWidget :public QWidget
{
	Q_OBJECT
public:
	AddWidget(QWidget *parent = Q_NULLPTR);
	AddWidget(QSqlTableModel *modelIn, QWidget *parent = Q_NULLPTR);
	~AddWidget();

	Ui::AddWidget uiAdd;
private:
	QSqlTableModel *model;
private slots :
		void on_SelectButton_clicked();
};
