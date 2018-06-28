#include "SaveDataThread.h"
#include <fstream>
#include <QDebug>
using namespace std;
SaveDataThread::SaveDataThread()
{

}
SaveDataThread::SaveDataThread(QString &toDir, QStringList &headerList, QStringList &dataList, QObject *parent /* = 0 */)
{
	this->headerList = headerList;
	this->dataList = dataList;
	this->toDir = toDir;
}
SaveDataThread::~SaveDataThread()
{

}
string q2s(const QString &s)
{
	return string((const char*)s.toLocal8Bit());
}

void SaveDataThread::setDataString(QString &toDir, QStringList &headerList, QStringList &dataList)
{
	this->headerList = headerList;
	this->dataList = dataList;
	this->toDir = toDir;
}

void SaveDataThread::run()
{
	std::ofstream Ofile;
	Ofile.open(q2s(toDir) + ("\\result.csv"), ios::out | ios::trunc);
	//Ofile<<" ,"
	double rates = 100 / (headerList.size() + dataList.size());
	int i = 0;
	for (i = 0; i < headerList.size(); i++)
	{
		Ofile << q2s(headerList[i]) << ",";
		emit processProgress(100, i*rates);
	}
	
	Ofile << endl;
	for (int j = 0; j < dataList.size(); j++)
	{
		Ofile << q2s(dataList[j]) << ",";
		if (j % 37 == 36)
		{
			Ofile << endl;
		}
		emit processProgress(100, j*rates+i*rates);
	}
	emit processProgress(100, 100);
	qDebug() << "data copy compelete";
	Ofile.close();
}