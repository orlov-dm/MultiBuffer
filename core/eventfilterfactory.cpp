#include "eventfilterfactory.h"

#ifdef Q_OS_LINUX
#include "linuxeventfilter.h"
#endif
#ifdef Q_OS_WIN
#include "wineventfilter.h"
#endif

NativeEventFilter *EventFilterFactory::eventFilter(QObject *parent)
{
#ifdef Q_OS_LINUX
    return new LinuxEventFilter(parent);
#endif
#ifdef Q_OS_WIN
    return new WinEventFilter(parent);
#endif
}
