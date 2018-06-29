#include "AddWidget.h"
#include <QFileDialog>
#include <QDebug>

AddWidget::AddWidget(QWidget *parent)
{
	uiAdd.setupUi(this);
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
	for (int i = 1; i < tempOption.count();i++)
	{
		QStringList tempbar = tempOption.at(i).split(",");
		qDebug() << tempbar;
	}
	file.close();
	
}

