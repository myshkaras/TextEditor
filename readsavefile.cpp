#include "readsavefile.h"

#include <QTextStream>
#include <QTextDocumentFragment>
#include <QTextDocumentWriter>
#include <QTextCodec>

FileOperator::FileOperator():
    _file()
{
    _fileName = "untitled.txt";
    setCodec("UTF-8");
}

bool FileOperator::saveFile(const QTextDocument* fragment)
{
    QTextDocumentWriter writer(_fileName);
    writer.setCodec(codec);
    return writer.write(fragment);
}

QString FileOperator::loadFileTo(const QString& fName)
{
    if (!QFile::exists(fName))
    {
        return QString("");
    }

    _fileName =  fName;
    _file.setFileName(_fileName);

    if (!_file.open(QFile::ReadOnly))
    {
        return QString("");
    }

    QTextStream stream (&_file);
    stream.setCodec(codec);

    return stream.readAll();;
}

bool FileOperator::exists(const QString& fName)
{
    return QFile::exists(fName);
}

QString FileOperator::getFileName()
{
    return _fileName;
}

void FileOperator::setFileName(const QString& fName)
{
    _fileName = fName;
}

bool FileOperator::setCodec(const QString&  codecName)
{
    QTextCodec* newCodec = QTextCodec::codecForName(codecName.toStdString().c_str());

    if (newCodec!=nullptr)
    {
        codec = newCodec;

        return true;
    }else
    {
        return false;
    }
}

FileOperator::~FileOperator()
{
    if (_file.isOpen())
    {
        _file.close();
    }
}
