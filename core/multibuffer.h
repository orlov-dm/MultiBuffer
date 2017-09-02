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

protected slots:
    void onKeyPressed(Key keyId, Qt::KeyboardModifiers keyMods);
    void onClipboardChanged();
    void onItemActivated(QString data);

protected:
    void showHistory();
    void addCurrentClipboardValue();
    void pasteInCurrentActiveWindow();

private:
    HistoryModel *m_historyModel = nullptr;
    HistoryForm *m_history = nullptr;

    QClipboard *m_clipboard;
    QString m_lastClipboardValue = "";
    bool m_skipNextAddition = false;
};

#endif // MULTIBUFFER_H
