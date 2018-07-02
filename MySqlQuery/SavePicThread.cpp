#include "SavePicThread.h"
#include <QDir>
#include <QDebug>
SavePicThread::SavePicThread()
{

}
SavePicThread::SavePicThread(QString& toDir, QStringList& picDir, QObject *parent /* = 0 */)
{
	this->toDir = toDir;
	this->picDir = picDir;
}
SavePicThread::~SavePicThread()
{

}

QString mkMutiDir(const QString path) {

	QDir dir(path);
	if (dir.exists(path)) {
		return path;
	}
	QString parentDir = mkMutiDir(path.mid(0, path.lastIndexOf('/')));
	QString dirname = path.mid(path.lastIndexOf('/') + 1);
	QDir parentPath(parentDir);
	if (!dirname.isEmpty())
		parentPath.mkpath(dirname);
	return parentDir + "/" + dirname;
}
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
	QDir sourceDir(fromDir);
	QDir targetDir(toDir);
	//if (!targetDir.exists()) {    /**< 如果目标目录不存在，则进行创建 */
	//	if (!targetDir.mkdir(targetDir.absolutePath()))
	//		return false;
	//}
	if (!targetDir.exists()) {    /**< 如果目标目录不存在，则进行创建 */
		mkMutiDir(targetDir.absolutePath());
		if (!targetDir.exists())
			return false;
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList) {
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		if (fileInfo.isDir()) {    /**< 当为目录时，递归的进行copy */
			if (!copyDirectoryFiles(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()),
				coverFileIfExist))
				return false;
		}
		else {            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
			if (coverFileIfExist && targetDir.exists(fileInfo.fileName())) {
				targetDir.remove(fileInfo.fileName());
			}

			/// 进行文件copy  
			if (!QFile::copy(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()))) {
				return false;
			}
		}
	}
	return true;
}

void SavePicThread::run()
{
	if (this->picDir.isEmpty())
	{
		qDebug() << "dir is null";
		return;
	}
	int counter = 0;
	int hasdone = 0;
	double rates = 100 / picDir.size();
	for (int i = 0; i < picDir.size(); i++)
	{
		emit processProgress(100, i*rates);
		QString dir1 = picDir[i].section(QRegExp("[-]"), 0, 0).trimmed();
		QString dir2 = picDir[i].section(QRegExp("[-]"), 1, 1).trimmed().remove("0");
		QString dir3 = picDir[i].section(QRegExp("[-]"), 2, 2).trimmed();
		qDebug() << dir3;
		if (dir3.toInt()<10)
		{
			dir3 = dir3.remove("0");
		}
		qDebug() << dir3;
		QString dir_all = QString("D:\\Photo_new\\") + dir1 + "\\" + dir2 + "\\" + dir3 + "\\";
		QString dstString = toDir + "\\" + dir1 + "\\" + dir2 + "\\" + dir3 + "\\";
		copyDirectoryFiles(dir_all, dstString, 1);
		emit processProgress(100, (i+1)*rates);
	}
	emit processProgress(100, 100);
	qDebug() << "pic copy compelete";
}
void SavePicThread::setDir(QString& toDir, QStringList& picDir)
{
	this->toDir = toDir;
	this->picDir = picDir;
}

