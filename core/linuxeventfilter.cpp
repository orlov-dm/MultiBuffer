#include "linuxeventfilter.h"
#include <QX11Info>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <xcb/xcb.h>
#include <X11/extensions/XTest.h>

const QVector<quint32> LinuxEventFilter::m_maskModifiers ({0, Mod2Mask, LockMask, (Mod2Mask | LockMask)});

LinuxEventFilter::LinuxEventFilter(QObject *parent) : NativeEventFilter(parent)
{
    m_display = QX11Info::display();
    m_win = QX11Info::appRootWindow();
    m_keycode = XKeysymToKeycode(m_display, XK_V);
    m_modifier = ControlMask | ShiftMask;
}

bool LinuxEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

    xcb_key_press_event_t *keyEvent = 0;

    if (eventType == "xcb_generic_event_t") {        
        xcb_generic_event_t *event = static_cast<xcb_generic_event_t *>(message);

        if ((event->response_type & 127) == XCB_KEY_PRESS){            
            keyEvent = static_cast<xcb_key_press_event_t *>(message);

            foreach (quint32 maskMods, m_maskModifiers) {
                if((keyEvent->state == (m_modifier | maskMods ))
                        &&  keyEvent->detail == m_keycode){
                    emit activated();   // и посылаем сигнал                    
                    return true;
                }
            }
        }
    }
    return false;
}

void LinuxEventFilter::setShortcut()
{
    unsetShortcut();        /* Just in case
                             * */    

    /* All combinations including Num Lock и Caps Lock
     * */
    for (auto maskMods: m_maskModifiers) {
        XGrabKey(m_display,
                 m_keycode ,
                 m_modifier | maskMods,
                 m_win,
                 True,
                 GrabModeAsync,
                 GrabModeAsync);
    }
}

void LinuxEventFilter::unsetShortcut()
{    
    for (auto maskMods: m_maskModifiers) {
        XUngrabKey(m_display,
                   m_keycode,
                   m_modifier | maskMods,
                   m_win);
    }
}

void LinuxEventFilter::paste() {
    qDebug() << "Paste";
    auto keycode = XKeysymToKeycode(m_display, XK_Control_L);
    XTestFakeKeyEvent(m_display, keycode, True, 0);

    keycode = XKeysymToKeycode(m_display, XK_V);
    XTestFakeKeyEvent(m_display, keycode, True, 0);

    //XFlush(m_display);
    keycode = XKeysymToKeycode(m_display, XK_V);
    XTestFakeKeyEvent(m_display, keycode, False, 0);

    keycode = XKeysymToKeycode(m_display, XK_Control_L);
    XTestFakeKeyEvent(m_display, keycode, False, 0);
    //XFlush(m_display);
}

