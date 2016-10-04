/*
 * MIT License
 * Copyright (c) 2016 Alexey Edelev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UNIVERSALLISTMODEL_H
#define UNIVERSALLISTMODEL_H

#include <QAbstractListModel>

#include <QObject>
#include <QList>
#include <QHash>
#include <QPointer>
#include <QMetaProperty>
#include <QMetaObject>

#include <QDebug>

template <typename T>
class UniversalListModel : public QAbstractListModel
{
public:
    ~UniversalListModel() {
        foreach (QPointer<T> value, m_container) {
            delete value.data();
        }
        m_container.clear();
    }

    int rowCount(const QModelIndex &parent) const {
        Q_UNUSED(parent)
        return m_container.count();
    }

    QHash<int, QByteArray> roleNames() const {
        if(s_roleNames.isEmpty()) {
            int propertyCount = T::staticMetaObject.propertyCount();
            for(int i = 0; i < propertyCount; i++) {
                s_roleNames.insert(Qt::UserRole + i, T::staticMetaObject.property(i).name());
            }
        }
        return s_roleNames;
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        int row = index.row();

        if(row < 0 || row >= m_container.count()) {
            return QVariant();
        }

        T* dataPtr = m_container.at(row).data();
        return dataPtr->property(s_roleNames.value(role));
    }

    bool add(T* value) {
        Q_ASSERT_X(value != nullptr, fullTemplateName(), "Trying to add member of NULL");

        if(m_container.indexOf(value) >= 0) {
#ifdef DEBUG
            qDebug() << fullTemplateName() << "Member already exists";
#endif
            return false;
        }
        beginInsertRows(QModelIndex(), m_container.count(), m_container.count());
        m_container.append(QPointer<T>(value));
        endInsertRows();
        return true;
    }

    void remove(T* value) {
        Q_ASSERT_X(value != nullptr, fullTemplateName(), ": Trying to remove member of NULL");

        int valueIndex = m_container.indexOf(value);

        if(valueIndex >= 0) {
            beginRemoveRows(QModelIndex(), valueIndex, valueIndex);
            m_container.removeAt(valueIndex);
            endRemoveRows();
        }
    }

protected:
    UniversalListModel(QObject* parent = 0) : QAbstractListModel(parent) {}

    QList<QPointer<T>> m_container;
    static QHash<int, QByteArray> s_roleNames;


private:
#ifdef DEBUG
    static QByteArray fullTemplateName() { //Debug helper
        return QString("UniversalListModel<%1>").arg(T::staticMetaObject.className()).toLatin1();
    }
#endif
};

template<typename T>
QHash<int, QByteArray> UniversalListModel<T>::s_roleNames;

#endif // UNIVERSALLISTMODEL_H
