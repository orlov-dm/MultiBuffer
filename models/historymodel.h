#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QVector>
#include <QColor>

class HistoryModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit HistoryModel(QObject *parent);
//    virtual ~HistoryModel();

    void addValue(const QString &value);
    QString getValueByRow(uint row);

    static char getMaxCount() { return MAX_BUFFER_SIZE; }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    void setMainColor(const QColor &color) { m_mainColor = color; }
private:
    QVector<QString> m_buffer;        
    QColor m_mainColor;

    static const char MAX_BUFFER_SIZE = 10;
    static const char DISPLAY_LENGTH = 60;
    static const char TOOLTIP_LENGTH = 100;
    static const char TOOLTIP_HEIGHT = 50;
};

#endif // HISTORYMODEL_H
