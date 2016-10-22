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
            Action action;
            if(msg->lParam & MOD_CONTROL) {
                if(msg->lParam & MOD_SHIFT) {
                    if(msg->wParam == Key::V) {
                        action = Action::SHOW_HISTORY;
                    }
                    else {
                        action = Action::COPY;
                    }
                }
                else {
                    action = Action::PASTE;
                }
                emit keyPressed(static_cast<Key>(msg->wParam), action);
            }            
        }
    }
#endif
    return false;
}
