#include "wineventfilter.h"
#include "includes/const.h"
#include "windows.h"

WinEventFilter::WinEventFilter(QObject *parent) : NativeEventFilter(parent)
{
    m_keycode = Key::V;
}

WinEventFilter::~WinEventFilter()
{

}

bool WinEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)   

    if (eventType == "windows_generic_MSG") {
        auto msg = static_cast<MSG*>(message);
        if (msg->message == WM_HOTKEY) {
            if(msg->lParam & MOD_CONTROL && msg->lParam & MOD_SHIFT && static_cast<Key>(msg->wParam) == m_keycode) {
                emit activated();
                return true;
            }
        }
    }
    return false;
}

void WinEventFilter::setShortcut()
{
    RegisterHotKey(NULL, m_keycode, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, m_keycode);
}

void WinEventFilter::unsetShortcut()
{    
    UnregisterHotKey(NULL, m_keycode);
}

void WinEventFilter::paste() {
    qDebug() << "Paste";
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Press the "Ctrl" key
    ip.ki.wVk = VK_CONTROL;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Press the "V" key
    ip.ki.wVk = 'V';
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "V" key
    ip.ki.wVk = 'V';
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "Ctrl" key
    ip.ki.wVk = VK_CONTROL;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}
