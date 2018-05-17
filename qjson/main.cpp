#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QJsonArray>
#include <iostream>


void parseJson()
{
    QFile file("C:/Users/maoxingda/Documents/Visual Studio 2017/Projects/qjson/qjson/persons.txt");

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream ts(&file);

        QString strJson = ts.readAll();

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(strJson.toUtf8(), &err);

        if (QJsonParseError::NoError == err.error)
        {
            if (doc.isObject())
            {
                QJsonObject root = doc.object();

                if (root.contains("persons"))
                {
                    QJsonValue valPersons = root.take("persons");

                    if (valPersons.isObject())
                    {
                        QJsonObject objPersons = valPersons.toObject();

                        QVector<QPair<QString, int>> vectTeachers;

                        if (objPersons.contains("teachers"))
                        {
                            QJsonValue valTeachers = objPersons.take("teachers");

                            if (valTeachers.isArray())
                            {
                                QJsonArray arrTeachers = valTeachers.toArray();

                                for (auto ele : arrTeachers)
                                {
                                    if (ele.isObject())
                                    {
                                        QJsonObject objTeaher = ele.toObject();

                                        QString strName;
                                        int     nSex;

                                        if (objTeaher.contains("name"))
                                        {
                                            QJsonValue valName = objTeaher.take("name");

                                            if (valName.isString())
                                            {
                                                strName = valName.toString();
                                            }
                                        }

                                        if (objTeaher.contains("sex"))
                                        {
                                            QJsonValue valSex = objTeaher.take("sex");

                                            if (valSex.isDouble())
                                            {
                                                nSex = valSex.toDouble();
                                            }
                                        }

                                        vectTeachers.push_back(QPair<QString, int>(strName, nSex));
                                    }
                                }
                            }
                        }

                        QVector<QPair<QString, int>> vectStudents;

                        if (objPersons.contains("students"))
                        {
                            QJsonValue valStudents = objPersons.take("students");

                            if (valStudents.isArray())
                            {
                                QJsonArray arrStudents = valStudents.toArray();

                                for (auto ele : arrStudents)
                                {
                                    if (ele.isObject())
                                    {
                                        QJsonObject objStudent = ele.toObject();

                                        QString strName;
                                        int     nSex;

                                        if (objStudent.contains("name"))
                                        {
                                            QJsonValue valName = objStudent.take("name");

                                            if (valName.isString())
                                            {
                                                strName = valName.toString();
                                            }
                                        }

                                        if (objStudent.contains("sex"))
                                        {
                                            QJsonValue valSex = objStudent.take("sex");

                                            if (valSex.isDouble())
                                            {
                                                nSex = valSex.toDouble();
                                            }
                                        }

                                        vectStudents.push_back(QPair<QString, int>(strName, nSex));
                                    }
                                }
                            }
                        }

                        qDebug() << vectTeachers;
                        qDebug() << vectStudents;
                    }
                }
            }
        }
    }
}

void catJson()
{
    QJsonObject obj1;
    obj1.insert("name", "maoxd");
    obj1.insert("sex", 1);

    QJsonObject obj2;
    obj2.insert("name", "mengxw");
    obj2.insert("sex", 1);

    QJsonArray arrTeachers;
    arrTeachers.append(obj1);
    arrTeachers.append(obj2);

    QJsonObject obj3;
    obj3.insert("name", "zhangcheng");
    obj3.insert("sex", 1);

    QJsonObject obj4;
    obj4.insert("name", "zhangyp");
    obj4.insert("sex", 1);

    QJsonArray arrStudents;
    arrStudents.append(obj3);
    arrStudents.append(obj4);

    QJsonObject persons;
    persons.insert("teachers", arrTeachers);
    persons.insert("students", arrStudents);

    QJsonObject root;
    root.insert("persons", persons);

    QJsonDocument doc(root);

    QByteArray barrJson = doc.toJson(QJsonDocument::Indented);

    std::string strJson = QString(barrJson).toStdString();

    std::cout << strJson;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    parseJson();
    catJson();

    return a.exec();
}
