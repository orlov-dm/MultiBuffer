#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QVector>

class HistoryModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit HistoryModel(QObject *parent);
//    virtual ~HistoryModel();

    void addValue(const QString &value);
    QString getValueByRow(uint row);

    uint getMaxCount() { return MAX_BUFFER_SIZE; }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QVector<QString> m_buffer;
    const uint MAX_BUFFER_SIZE = 10;

};

#endif // HISTORYMODEL_H
