#include "historymodel.h"

#include <QApplication>
#include <QFont>

HistoryModel::HistoryModel(QObject *parent):
    QAbstractListModel(parent)
{

}

void HistoryModel::addValue(const QString &value)
{
    auto first = 0;
    auto last = first;
    beginInsertRows(QModelIndex(), 0, 0);
    m_buffer.push_front(value);
    endInsertRows();
    if((uint)m_buffer.size() > MAX_BUFFER_SIZE) {
        first = MAX_BUFFER_SIZE;
        last = first;
        beginRemoveRows(QModelIndex(), first, last);
        m_buffer.pop_back();
        endRemoveRows();
    }
}

QString HistoryModel::getValueByRow(uint row)
{
    QString result = "";
    if(row <= MAX_BUFFER_SIZE) {
        result = m_buffer[row];
    }
    return result;
}

int HistoryModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
        return m_buffer.size();
    }
    return 0;
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if(index.isValid()) {
        if(index.row() < m_buffer.size()) {
            auto string = m_buffer[index.row()];
            QString sResult = "";
            if(role == Qt::DisplayRole) {
                if(string.size() > DISPLAY_LENGTH) {
                    sResult = "...";
                }
                sResult.prepend(string.simplified().left(DISPLAY_LENGTH));
                result.setValue(sResult);
            }
            else if(role == Qt::ToolTipRole) {
                auto strings = string.split('\n');
                if(strings.size() > TOOLTIP_HEIGHT) {
                    strings = strings.mid(0, TOOLTIP_HEIGHT);
                    strings.append("...");
                }
                for(auto &tempString: strings) {
                    if(tempString.size() > TOOLTIP_LENGTH) {
                        tempString = tempString.left(TOOLTIP_LENGTH).append("...");
                    }
                }
                result.setValue(strings.join("\n"));
            }
            else if(role == Qt::FontRole) {
                result.setValue(QApplication::font());
            }
        }
    }
    return result;
}





