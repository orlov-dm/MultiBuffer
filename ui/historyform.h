#ifndef HISTORYFORM_H
#define HISTORYFORM_H

#include <QWidget>
#include <QColor>

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

    void setMainColor(const QColor &color);

public slots:
    void adjustFormSize();

protected:
    void copyStringToClipboard(const QString &value);
    virtual void showEvent(QShowEvent *event);

protected slots:
    void onListActivated(const QModelIndex &index);

private:
    Ui::HistoryForm *ui;
    HistoryModel *m_model = nullptr;

    QFontMetrics *m_metrics = nullptr;
signals:
    void itemDoubleClicked(uint row);
};

#endif // HISTORYFORM_H
