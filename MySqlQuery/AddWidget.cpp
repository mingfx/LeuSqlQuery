#include "AddWidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSqlError>
#include <QDate>

AddWidget::AddWidget(QWidget *parent)
{
	uiAdd.setupUi(this);
	uiAdd.label->setVisible(false);
	uiAdd.progressBar->setVisible(false);
}
AddWidget::AddWidget(QSqlTableModel *modelIn, QWidget *parent /* = Q_NULLPTR */)
{
	uiAdd.setupUi(this);
	model = modelIn;
	uiAdd.label->setVisible(false);
	uiAdd.progressBar->setVisible(false);
}
AddWidget::~AddWidget()
{

}
//string q2s(const QString &s)
//{
//	return string((const char*)s.toLocal8Bit());
//}
void AddWidget::on_SelectButton_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(NULL,QString::fromLocal8Bit("选择数据文件"),"/","*.csv");
	qDebug() << filePath;
	if (filePath=="")
	{
		return;
	}
	QDir dir = QDir::current();
	QFile file(dir.filePath(filePath));
	if (!file.open(QIODevice::ReadOnly))
		qDebug() << "open file failed";
	QTextStream *out = new QTextStream(&file);
	QStringList tempOption = out->readAll().split("\n");
	QStringList headerList = tempOption.at(0).split(",");
	QStandardItemModel *tableModel = new QStandardItemModel();
	uiAdd.tableView->setModel(tableModel);
	tableModel->setHorizontalHeaderLabels(headerList);
	QStandardItem* item = 0;
	int cutRowCount = model->rowCount();
	double rate = 100 / tempOption.count();
	for (int i = 1; i < tempOption.count();i++)
	{
		setProgress(100, i);
		if (tempOption[i]==NULL)
		{
			continue;
		}
		QStringList tempbar = tempOption.at(i).split(",");
		qDebug() << tempbar;
		model->insertRow(cutRowCount);
		for (int j = 0; j < tempbar.count();j++)
		{
			item = new QStandardItem(tempbar[j]);
			tableModel->setItem(i - 1, j, item);
			
			if (j == 0)
				model->setData(model->index(cutRowCount, j), tempbar[j].toInt());
			else if (j == 3 || j == 4 || j == 6)
			{
				if (tempbar[j] == NULL)
				{
					model->setData(model->index(cutRowCount, j),NULL);
				}
				//strBuffer = "2010-07-02 17:35:00";

				QDateTime time = QDateTime::fromString(tempbar[j], "yyyy-MM-ddThh:mm:ss");
				qDebug() << time;
				model->setData(model->index(cutRowCount, j), time);
			}
			else
				model->setData(model->index(cutRowCount, j), tempbar[j]);
		}
		cutRowCount += 1;
		setProgress(100, i*rate);
	}
	setProgress(100, 100);
	//model->submitAll();
	file.close();
}

void AddWidget::on_AddButton_clicked()
{
	//model->submitAll();
	model->database().transaction(); //开始事务操作
	if (model->submitAll()) {
		model->database().commit(); //提交
	}
	else {
		model->database().rollback(); //回滚
		QMessageBox::warning(this, tr("tableModel"),
			tr("数据库错误: %1")
			.arg(model->lastError().text()));
	}
}

void AddWidget::setProgress(int maxValue, int value)
{
	uiAdd.label->setVisible(true);
	uiAdd.progressBar->setVisible(true);
	if (!hasDataProgressBarMaxSet)
	{
		uiAdd.progressBar->setMaximum(maxValue);
		hasDataProgressBarMaxSet = true;
	}
	uiAdd.progressBar->setValue(value);
}
