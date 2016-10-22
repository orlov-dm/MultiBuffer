#include <QApplication>
#include "core/multibuffer.h"
#include "core/nativeeventfilter.h"

#include <windows.h>

#include <QDebug>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto font = a.font();
    font.setPointSize(10);
    a.setFont(font);

    NativeEventFilter *filter = new NativeEventFilter(&a);
    /*MultiBuffer *mb = */new MultiBuffer(filter, &a);


    return a.exec();
}
