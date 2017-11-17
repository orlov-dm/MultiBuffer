#include "multibuffer.h"

#include "includes/const.h"
#include "models/historymodel.h"
#include "ui/historyform.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>
#endif

#include <QApplication>
#include <QWidget>
#include <QClipboard>
#include <QTimer>
#include <QDesktopWidget>

#include <QDebug>

//#include <QMessageBox>
//#include "core/linuxeventfilter.h"

MultiBuffer::MultiBuffer(NativeEventFilter *filter, QObject *parent)
    : QObject(parent), m_clipboard(QApplication::clipboard())
{
    //RegisterHotKey(NULL, Key::V, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, Key::V);
    m_historyModel = new HistoryModel(this);
    m_historyModel = new HistoryModel(this);
    m_history = new HistoryForm(m_historyModel);
    m_filter = filter;
#ifdef Q_OS_WIN
    //get win color
    DWORD color = 0;
    BOOL opaque = FALSE;
    HRESULT hr = DwmGetColorizationColor(&color, &opaque);
    if(SUCCEEDED(hr)) {
        auto qtColor = QColor(color);
        if(opaque) {
            qtColor.setAlpha(125);
        }
        m_history->setMainColor(qtColor);
    }
#endif            
    qApp->installNativeEventFilter(filter);        
    if(!connect(filter, &NativeEventFilter::activated, this, &MultiBuffer::showHistory)) {
        qDebug() << "Error";
    }
//    if(!connect(static_cast<LinuxEventFilter*>(filter), &LinuxEventFilter::activated, this, &MultiBuffer::showHistory)) {
//        qDebug() << "Error";
//    }
    connect(m_clipboard, &QClipboard::dataChanged, this, &MultiBuffer::onClipboardChanged);
    connect(m_history, &HistoryForm::itemActivated, this, &MultiBuffer::onItemActivated);
    connect(this, &MultiBuffer::changed, m_history, &HistoryForm::adjustFormSize);    
}

MultiBuffer::~MultiBuffer()
{
    //UnregisterHotKey(NULL, Key::V);

    if(m_history) delete m_history;
    if(m_historyModel) delete m_historyModel;
}

void MultiBuffer::showHistory()
{
    Q_ASSERT(m_history);

    //m_history->move(QCursor::pos());
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - m_history->width()) / 2;
    int y = (screenGeometry.height() - m_history->height()) / 2;

    m_history->move(x, y);
    m_history->show();
}

void MultiBuffer::addCurrentClipboardValue()
{
    auto newValue = m_clipboard->text();
    if(!newValue.isEmpty() && m_lastClipboardValue != newValue)
    {
        m_historyModel->addValue(newValue);
        m_lastClipboardValue = newValue;
        emit changed();
    }
}

void MultiBuffer::onClipboardChanged() {    
    Q_ASSERT(m_historyModel);
    if(!m_skipNextAddition) {
        QTimer::singleShot(500, this, &MultiBuffer::addCurrentClipboardValue);
    }
    else {
        m_skipNextAddition = false;
    }
}


void MultiBuffer::onItemActivated(const QString data) {
    m_skipNextAddition = true;
    m_clipboard->setText(data);
    m_history->hide();

    pasteInCurrentActiveWindow();
}

void MultiBuffer::pasteInCurrentActiveWindow() {
      m_filter->paste();
}

