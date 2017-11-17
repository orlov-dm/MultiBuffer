#include <QApplication>
#include <QDebug>
#include "core/multibuffer.h"
#include "core/eventfilterfactory.h"
#include "core/nativeeventfilter.h"
//#ifdef Q_OS_WIN
//#include <windows.h>
//#endif

#include <QFont>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    qDebug() << "Main";
    qWarning() << "Warn";
    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(10);
    a.setFont(font);

//    LinuxEventFilter *filter = new LinuxEventFilter(&a);
    NativeEventFilter * filter = EventFilterFactory::eventFilter(&a);
    filter->setShortcut();
    //a.installNativeEventFilter(filter);
    /*MultiBuffer *mb = */new MultiBuffer(filter, &a);


    return a.exec();
}
