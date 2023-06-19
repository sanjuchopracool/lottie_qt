#include <parser/check.h>
#include <QTest>

class TestCheck : public QObject
{
    Q_OBJECT
private slots:
    void tst_is_ok() const;
};

void TestCheck::tst_is_ok() const
{
    check chk;
    QCOMPARE(chk.is_ok(false), false);
    QCOMPARE(chk.is_ok(true), true);
}

QTEST_MAIN(TestCheck)
#include "test_check.moc"
