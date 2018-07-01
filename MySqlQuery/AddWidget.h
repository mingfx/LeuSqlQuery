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
	bool hasDataProgressBarMaxSet;
	QSqlTableModel *model;
	void setProgress(int maxValue, int value);
private slots :
		void on_SelectButton_clicked();
		void on_AddButton_clicked();
};
