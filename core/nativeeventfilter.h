#ifndef NATIVEEVENTFILTER_H
#define NATIVEEVENTFILTER_H

#include <QObject>
#include <QAbstractNativeEventFilter>
#include "includes/const.h"

class NativeEventFilter : public QObject, QAbstractNativeEventFilter
{
    Q_OBJECT
    Q_DISABLE_COPY(NativeEventFilter)

public:
    explicit NativeEventFilter(QObject *parent = 0);
    bool nativeEventFilter(const QByteArray& eventType, void* message, long* result) override;

signals:
    void keyPressed(Key keyId, Action action);

public slots:
};

#endif // NATIVEEVENTFILTER_H
