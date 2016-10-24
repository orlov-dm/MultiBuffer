#include "nativeeventfilter.h"
#include <QCoreApplication>
#include "includes/const.h"
#include <QCoreApplication>

#ifdef Q_OS_WIN
#include "windows.h"
#endif

NativeEventFilter::NativeEventFilter(QObject *parent): QObject(parent)
{
    qApp->installNativeEventFilter(this);
}

bool NativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(result);
//    (void)result;
#ifdef Q_OS_WIN
    if (eventType == "windows_generic_MSG") {
        auto msg = static_cast<MSG*>(message);
        if (msg->message == WM_HOTKEY) {            
            Qt::KeyboardModifiers modifiers = Qt::NoModifier;
            if(msg->lParam & MOD_CONTROL) {
                modifiers |= Qt::ControlModifier;
                if(msg->lParam & MOD_SHIFT) {
                    modifiers |= Qt::ShiftModifier;
                }                                
            }
            emit keyPressed(static_cast<Key>(msg->wParam), modifiers);
        }
    }
#endif
    return false;
}
