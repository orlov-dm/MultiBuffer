#ifndef EVENTFILTERFACTORY_H
#define EVENTFILTERFACTORY_H

#include "nativeeventfilter.h"

class EventFilterFactory
{
public:
    EventFilterFactory() = delete;

    static NativeEventFilter * eventFilter(QObject *parent);
};

#endif // EVENTFILTERFACTORY_H
