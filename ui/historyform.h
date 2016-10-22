#ifndef HISTORYFORM_H
#define HISTORYFORM_H

#include <QWidget>

class HistoryModel;
class QFontMetrics;

namespace Ui {
class HistoryForm;
}

class HistoryForm : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryForm(HistoryModel *model, QWidget *parent = 0);
    virtual ~HistoryForm();

public slots:
    void adjustFormSize();

protected:
    void copyStringToClipboard(const QString &value);

protected slots:
    void onListDoubleClicked(const QModelIndex &index);

private:
    Ui::HistoryForm *ui;
    HistoryModel *m_model = nullptr;

    QFontMetrics *m_metrics = nullptr;
signals:
    void itemDoubleClicked(uint row);
};

#endif // HISTORYFORM_H
