#include <QtTest>
#include "C:\Users\ahdre\Desktop\ISTINNA_interface\Server\task1.h"

#include <QObject>


// add necessary includes here

class FuncForServer_Test : public QObject
{
    Q_OBJECT

public:
    FuncForServer_Test();
    ~FuncForServer_Test();

private slots:
    void test_case1();

};

FuncForServer_Test::FuncForServer_Test()
{

}

FuncForServer_Test::~FuncForServer_Test()
{

}

void FuncForServer_Test::test_case1()
{
    QString var = "0";
    QString a = "-6";
    QString b = "7";
    QString eps = "0.0369091";
    QString res1 = newtonMethod(var, a, b, eps);
    QString value1 = "-12";
    QVERIFY2 (res1 == value1  ,"task_1_false");
}





QTEST_APPLESS_MAIN(FuncForServer_Test)

#include "tst_funcforserver_test.moc"
