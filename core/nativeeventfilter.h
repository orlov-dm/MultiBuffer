#ifndef NATIVEEVENTFILTER_H
#define NATIVEEVENTFILTER_H

#include <QObject>
#include <QAbstractNativeEventFilter>

class NativeEventFilter : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
    Q_DISABLE_COPY(NativeEventFilter)

public:
    explicit NativeEventFilter(QObject *parent = 0);    
    virtual bool nativeEventFilter(const QByteArray& eventType, void* message, long* result) override = 0;
    virtual void setShortcut() = 0;
    virtual void paste() = 0;
signals:
    void activated();
protected:
    virtual void unsetShortcut() = 0;
};

#endif // NATIVEEVENTFILTER_H
