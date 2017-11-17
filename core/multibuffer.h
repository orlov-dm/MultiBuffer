#ifndef MULTIBUFFER_H
#define MULTIBUFFER_H

#include <QObject>
#include <QVector>
#include <QString>
#include "core/nativeeventfilter.h"


#include <QClipboard>

class QWidget;
class QClipboard;
class HistoryModel;
class HistoryForm;

class MultiBuffer : public QObject
{
    Q_OBJECT
public:
    explicit MultiBuffer(NativeEventFilter *filter, QObject *parent = 0);
    virtual ~MultiBuffer();

signals:
    void changed();

public slots:
    void showHistory();

protected slots:
    void onClipboardChanged();
    void onItemActivated(const QString data);

protected:

    void addCurrentClipboardValue();
    void pasteInCurrentActiveWindow();

private:
    HistoryModel *m_historyModel = nullptr;
    HistoryForm *m_history = nullptr;

    QClipboard *m_clipboard;
    QString m_lastClipboardValue = "";
    bool m_skipNextAddition = false;

    NativeEventFilter *m_filter;
};

#endif // MULTIBUFFER_H
