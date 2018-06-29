#include "AddWidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QStandardItemModel>

AddWidget::AddWidget(QWidget *parent)
{
	uiAdd.setupUi(this);
}
AddWidget::AddWidget(QSqlTableModel *modelIn, QWidget *parent /* = Q_NULLPTR */)
{
	uiAdd.setupUi(this);
	model = modelIn;
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
	for (int i = 1; i < tempOption.count();i++)
	{
		QStringList tempbar = tempOption.at(i).split(",");
		qDebug() << tempbar;
		for (int j = 0; j < tempbar.count();j++)
		{
			item = new QStandardItem(tempbar[j]);
			tableModel->setItem(i-1, j, item);
		}
	}
	file.close();
}


