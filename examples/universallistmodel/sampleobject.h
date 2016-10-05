#ifndef SAMPLEOBJECT_H
#define SAMPLEOBJECT_H

#include <QString>
#include <QObject>

class SampleObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int param1 READ param1 WRITE setParam1 NOTIFY param1Changed)
    Q_PROPERTY(float param2 READ param2 WRITE setParam2 NOTIFY param2Changed)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    SampleObject(int aParam1, float aParam2, const QString& aName);
    int param1() const
    {
        return m_param1;
    }
    float param2() const
    {
        return m_param2;
    }
    QString name() const
    {
        return m_name;
    }

public slots:
    void setParam1(int param1)
    {
        if (m_param1 == param1)
            return;

        m_param1 = param1;
        emit param1Changed(param1);
    }
    void setParam2(float param2)
    {
        if (m_param2 == param2)
            return;

        m_param2 = param2;
        emit param2Changed(param2);
    }
    void setName(const QString& name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(name);
    }

signals:
    void param1Changed(int param1);
    void param2Changed(float param2);
    void nameChanged(const QString& name);

private:
    int m_param1;
    float m_param2;
    QString m_name;
};

#endif // SAMPLEOBJECT_H
