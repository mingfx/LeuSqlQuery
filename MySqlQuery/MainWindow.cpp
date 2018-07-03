#include "MainWindow.h"
#include "Widget.h"
#include "AddWidget.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QDir>
#include <fstream>
#include <QStandardItemModel>
#include <QFileDialog>
#include <iostream>
using namespace std;

bool IsDateInside(QDate dateStart,QDate dateEnd,QString dateTest)//dateTest:2018-05-01
{
	bool result = false;
	int year = dateTest.section(QRegExp("[-]"), 0, 0).trimmed().toInt();
	int mouth = dateTest.section(QRegExp("[-]"), 1, 1).trimmed().remove("0").toInt();
	int day = dateTest.section(QRegExp("[-]"), 2, 2).trimmed().toInt();
	int yearStart = dateStart.year();
	int mouthStart = dateStart.month();
	int dayStart = dateStart.day();
	int yearEnd = dateEnd.year();
	int monthEnd = dateEnd.month();
	int dayEnd = dateEnd.day();
	if (year>=yearStart&&year<=yearEnd)
	{
		if (mouth>=mouthStart&&mouth<= monthEnd)
		{
			if (day>=dayStart&&day<=dayEnd)
			{
				result = true;
			}
		}
	}
	return result;
}
//递归创建文件夹
//QString mkMutiDir(const QString path) {
//
//	QDir dir(path);
//	if (dir.exists(path)) {
//		return path;
//	}
//	QString parentDir = mkMutiDir(path.mid(0, path.lastIndexOf('/')));
//	QString dirname = path.mid(path.lastIndexOf('/') + 1);
//	QDir parentPath(parentDir);
//	if (!dirname.isEmpty())
//		parentPath.mkpath(dirname);
//	return parentDir + "/" + dirname;
//}
//bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
//{
//	QDir sourceDir(fromDir);
//	QDir targetDir(toDir);
//	//if (!targetDir.exists()) {    /**< 如果目标目录不存在，则进行创建 */
//	//	if (!targetDir.mkdir(targetDir.absolutePath()))
//	//		return false;
//	//}
//	if (!targetDir.exists()) {    /**< 如果目标目录不存在，则进行创建 */
//		mkMutiDir(targetDir.absolutePath());
//		if (!targetDir.exists())
//			return false;
//	}
//
//	QFileInfoList fileInfoList = sourceDir.entryInfoList();
//	foreach(QFileInfo fileInfo, fileInfoList) {
//		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
//			continue;
//
//		if (fileInfo.isDir()) {    /**< 当为目录时，递归的进行copy */
//			if (!copyDirectoryFiles(fileInfo.filePath(),
//				targetDir.filePath(fileInfo.fileName()),
//				coverFileIfExist))
//				return false;
//		}
//		else {            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
//			if (coverFileIfExist && targetDir.exists(fileInfo.fileName())) {
//				targetDir.remove(fileInfo.fileName());
//			}
//
//			/// 进行文件copy  
//			if (!QFile::copy(fileInfo.filePath(),
//				targetDir.filePath(fileInfo.fileName()))) {
//				return false;
//			}
//		}
//	}
//	return true;
//}

//QSqlTableModel* query(QSqlTableModel *srcTable,QString date)
//{
//	
//	int rowCount = srcTable->rowCount();
//	qDebug() << rowCount;
//	//QString tmp = srcTable->record(0).value(6).toString();
//	//qDebug() << tmp;
//	//QString split_tmp = tmp.section(QRegExp("[T]"), 0, 0).trimmed();
//	//qDebug() << split_tmp;
//	//QSqlTableModel *newModel =new QSqlTableModel;
//	QSqlTableModel newModel(srcTable);
//	newModel.clear();
//	qDebug() << srcTable->headerData(4, Qt::Horizontal);
//	qDebug() << newModel.headerData(4,Qt::Horizontal);
//	int t = 0;
//	for (int i = 0; i < rowCount; i++)
//	{
//		QString tmp = srcTable->record(i).value(6).toString();
//		if (!tmp.isEmpty())
//		{
//			QString split_tmp = tmp.section(QRegExp("[T]"), 0, 0).trimmed();
//			qDebug() << split_tmp;
//			if (date == split_tmp)
//			{
//				QSqlRecord trecord;
//				trecord = srcTable->record();
//				qDebug() << trecord;
//				//trecord.setValue(6, "2018");
//				newModel.insertRecord(-1,trecord);
//				if (!newModel.submitAll())
//					qDebug() << "error";
//				qDebug() << newModel.headerData(4, Qt::Horizontal);
//				qDebug() << newModel.record(t);
//				t = t + 1;
//				qDebug() << int(newModel.rowCount());
//				QString dir1 = split_tmp.section(QRegExp("[-]"), 0, 0).trimmed();
//				QString dir2 = split_tmp.section(QRegExp("[-]"), 1, 1).trimmed().remove("0");
//				QString dir3 = split_tmp.section(QRegExp("[-]"), 2, 2).trimmed();
//				qDebug() << dir1 << dir2 << dir3;
//				QString dir_all = QString("D:\\Photo_new\\") + dir1 + "\\" + dir2 + "\\" + dir3 + "\\";
//				QString dstString = QString("F:\\Moemil\\Leu\\picture\\");
//				copyDirectoryFiles(dir_all, dstString, 0);
//			}
//		}
//		//srcTable->removeRow(i);
//	}
//	//srcTable->removeRows(0, rowCount);
//	int rowCount_t = newModel.rowCount();
//	qDebug() << "size=" << t;
//	qDebug() << "复制完成";
//	qDebug() << newModel.record(1).value(6).toString();
//	TableWidget *tableWidget = new TableWidget();
//	tableWidget->ui1.tableView->setModel(&newModel);
//	tableWidget->ui1.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//	tableWidget->show();
//	return srcTable;
//}
void MainWindow::query(QSqlTableModel *srcTable, QDate dateStart,QDate dateEnd)
{
	headerList.clear();
	dataList.clear();
	int rowCount = srcTable->rowCount();
	qDebug() << rowCount;
	int i = 0;
	while (srcTable->headerData(i, Qt::Horizontal).compare(QString("%1").arg(i + 1)))
	{
		headerList.push_back(srcTable->headerData(i, Qt::Horizontal).toString());
		i = i + 1;
	}
	int size = headerList.size();//37
	qDebug() << headerList.size();

	//QString header = srcTable->headerData(0, Qt::Horizontal).toString();
	//bool headerIsNull = srcTable->headerData(0, Qt::Horizontal).compare(QString("1")); //相等时返回false
	//qDebug() << header;
	//qDebug() << headerIsNull;

	for (int i = 0; i < rowCount; i++)
	{
		//QString tmp = srcTable->record(i).value(6).toString();
		QString tmp = srcTable->record(i).value(3).toString();

		if (!tmp.isEmpty())
		{
			QString split_tmp = tmp.section(QRegExp("[T]"), 0, 0).trimmed();
			//qDebug() << split_tmp;
			if (IsDateInside(dateStart, dateEnd, split_tmp))
			{
				QSqlRecord trecord = srcTable->record(i);
				for (int j = 0; j < size; j++)
				{
					dataList.push_back(trecord.value(j).toString());
				}
				picDir.push_back(split_tmp);
			}
		}
	}
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label_3->setVisible(false);
	ui.label_4->setVisible(false);
	ui.progressBar->setVisible(false);
	ui.progressBar_2->setVisible(false);
	hasDataProgressBarMaxSet = false;
	hasPicProgressBarMaxSet = false;
	model = new QSqlTableModel(this);
	model->setTable("sample_2018");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();
	ui.tableView->setModel(model);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	/*QSqlRecord record_tmp = model->record(1);
	QString chText = record_tmp.value(5).toString();*/
	//cout << chText.toStdString() << endl;
	//qDebug() << chText;
	this->picThread = new SavePicThread();
	this->dataThread = new SaveDataThread();

	connect(picThread, SIGNAL(processProgress(int, int)), this, SLOT(setPicProgress(int, int)));
	connect(dataThread, SIGNAL(processProgress(int, int)), this, SLOT(setDataProgress(int, int)));
}

void MainWindow::on_Query_clicked()
{
	ui.label_3->setVisible(false);
	ui.label_4->setVisible(false);
	ui.progressBar->setVisible(false);
	ui.progressBar_2->setVisible(false);
	hasDataProgressBarMaxSet = false;
	hasPicProgressBarMaxSet = false;
	QDate dateStart = ui.dateEdit->date();
	QDate dateEnd = ui.dateEdit_2->date();
	query(model, dateStart,dateEnd);
	//新建窗口，在表格中显示结果
	QStandardItemModel *tableModel = new QStandardItemModel();
	TableWidget *tableWidget = new TableWidget;
	tableWidget->ui1.tableView->setModel(tableModel);
	tableModel->setHorizontalHeaderLabels(headerList);
	QStandardItem* item = 0;
	for (int q = 0; q < dataList.size(); q++)
	{
		int row = int(q / 37);
		int col = q % 37;
		item = new QStandardItem(dataList[q]);
		tableModel->setItem(row, col, item);
	}
	tableWidget->setWindowTitle(QObject::tr("Result"));
	tableWidget->show();
}

void MainWindow::on_Save_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
		"/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
	//qDebug() << dir;
	//copy picture
	if (dir=="")
	{
		QMessageBox *warnBox = new QMessageBox;
		warnBox->warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("选择路径为空"), QMessageBox::Abort);
		return;
	}
	/*for (int i = 0; i < picDir.size(); i++)
	{
		QString dir1 = picDir[i].section(QRegExp("[-]"), 0, 0).trimmed();
		QString dir2 = picDir[i].section(QRegExp("[-]"), 1, 1).trimmed().remove("0");
		QString dir3 = picDir[i].section(QRegExp("[-]"), 2, 2).trimmed();
		QString dir_all = QString("D:\\Photo_new\\") + dir1 + "\\" + dir2 + "\\" + dir3 + "\\";
		QString dstString = dir + "\\" + dir1 + "\\" + dir2 + "\\" + dir3 + "\\";
		copyDirectoryFiles(dir_all, dstString, 1);
	}*/
	this->picThread->setDir(dir, picDir);
	this->picThread->start();
	//copy data
	//std::ofstream Ofile;
	//Ofile.open(q2s(dir) + ("\\result.csv"), ios::out | ios::trunc);
	////Ofile<<" ,"
	//for (int i = 0; i < headerList.size(); i++)
	//{
	//	Ofile << q2s(headerList[i]) << ",";
	//}
	//Ofile << endl;
	//for (int j = 0; j < dataList.size(); j++)
	//{
	//	Ofile << q2s(dataList[j]) << ",";
	//	if (j % 37 == 36)
	//	{
	//		Ofile << endl;
	//	}
	//}
	this->dataThread->setDataString(dir, headerList, dataList);
	this->dataThread->start();
	//qDebug() << QString::fromLocal8Bit("复制完成");
}

void MainWindow::setPicProgress(int max, int value)
{
	ui.label_3->setVisible(true);
	ui.progressBar->setVisible(true);
	if (!hasPicProgressBarMaxSet)
	{
		ui.progressBar->setMaximum(max);
		hasPicProgressBarMaxSet = true;
	}
	ui.progressBar->setValue(value);
}

void MainWindow::setDataProgress(int max, int value)
{
	ui.label_4->setVisible(true);
	ui.progressBar_2->setVisible(true);
	if (!hasDataProgressBarMaxSet)
	{
		ui.progressBar_2->setMaximum(max);
		hasDataProgressBarMaxSet = true;
	}
	ui.progressBar_2->setValue(value);
}

void MainWindow::on_Add_clicked()
{
	AddWidget *addWidget = new AddWidget(model);
	addWidget->show();
}