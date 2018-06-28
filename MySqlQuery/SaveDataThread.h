#pragma once
#include <QThread>
#include <QObject>

class SaveDataThread :public QThread
{
	Q_OBJECT
public:
	SaveDataThread();
	SaveDataThread(QString &toDir, QStringList &headerList, QStringList &dataList, QObject *parent = 0);
	~SaveDataThread();

	virtual void run();
	void setDataString(QString &toDir, QStringList &headerList, QStringList &dataList);
signals:
	void processProgress(int maxValue, int progress);
private:
	QStringList headerList;
	QStringList dataList;
	QString toDir;
};
