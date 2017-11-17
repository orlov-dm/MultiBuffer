#ifndef LINUXEVENTFILTER_H
#define LINUXEVENTFILTER_H

#include "nativeeventfilter.h"
#include "includes/const.h"
#include <QVector>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class LinuxEventFilter : public NativeEventFilter//public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit LinuxEventFilter(QObject *parent = 0);

    // переопределяем метод nativeEventFilter
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
    void setShortcut();     // Добавляем метод установки хоткея
    void unsetShortcut();   // и метод удаления хоткея для полноты картины

    void paste();

private:
    Display * m_display;
    Window m_win;
    int m_keycode;                // код клавиши
    unsigned int m_modifier;      // код модификаторов
    static const QVector<quint32> m_maskModifiers;
};

#endif // LINUXEVENTFILTER_H
