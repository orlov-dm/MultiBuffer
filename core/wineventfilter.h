#ifndef WINEVENTFILTER_H
#define WINEVENTFILTER_H

#include "nativeeventfilter.h"
#include "includes/const.h"

class WinEventFilter : public NativeEventFilter
{
    Q_OBJECT
public:
    explicit WinEventFilter(QObject *parent = 0);
    virtual ~WinEventFilter();

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
    void setShortcut();
    void unsetShortcut();

    void paste();

private:    
    Key m_keycode;
};

enum Key {
    NUM_0 = 0x30,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,

    V = 0x56
};

const QList<Key> NUM_KEYS = {
    Key::NUM_0,
    Key::NUM_1,
    Key::NUM_2,
    Key::NUM_3,
    Key::NUM_4,
    Key::NUM_5,
    Key::NUM_6,
    Key::NUM_7,
    Key::NUM_8,
    Key::NUM_9
};

#endif // WINEVENTFILTER_H
