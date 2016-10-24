#include "multibuffer.h"

#include <windows.h>
#include "includes/const.h"
#include "models/historymodel.h"
#include "ui/historyform.h"

#include <QApplication>
#include <QWidget>
#include <QClipboard>
#include <QTimer>

#include <QDebug>

MultiBuffer::MultiBuffer(NativeEventFilter *filter, QObject *parent)
    : QObject(parent), m_clipboard(QApplication::clipboard())
{
//    for(auto id: NUM_KEYS) {
//        RegisterHotKey(NULL, id, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, id);
//        RegisterHotKey(NULL, id + NUM_KEYS.size(), MOD_CONTROL | MOD_NOREPEAT, id);
//    }
    RegisterHotKey(NULL, Key::V, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, Key::V);

    m_historyModel = new HistoryModel(this);
    m_history = new HistoryForm(m_historyModel);

    connect(filter, &NativeEventFilter::keyPressed, this, &MultiBuffer::onKeyPressed);
    connect(m_clipboard, &QClipboard::dataChanged, this, &MultiBuffer::onClipboardChanged);
    connect(m_history, &HistoryForm::itemDoubleClicked, this, &MultiBuffer::onItemDoubleClicked);
    connect(this, &MultiBuffer::changed, m_history, &HistoryForm::adjustFormSize);
}

MultiBuffer::~MultiBuffer()
{
//    for(auto id: NUM_KEYS) {
//        UnregisterHotKey(NULL, id);
//    }
    UnregisterHotKey(NULL, Key::V);

    if(m_history) delete m_history;
    if(m_historyModel) delete m_historyModel;
}

void MultiBuffer::onKeyPressed(Key keyId, Qt::KeyboardModifiers keyMods)
{
    qDebug() << "Key Pressed " << (uint)keyId << " " << keyMods;
    if(keyId == Key::V && keyMods & Qt::ControlModifier && keyMods & Qt::ShiftModifier) {
        showHistory();
    }
}

void MultiBuffer::showHistory()
{
    Q_ASSERT(m_history);

    m_history->move(QCursor::pos());
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


void MultiBuffer::onItemDoubleClicked(uint row) {
    m_skipNextAddition = true;
    m_clipboard->setText(m_historyModel->getValueByRow(row));
    m_history->hide();

    pasteInCurrentActiveWindow();
}

void MultiBuffer::pasteInCurrentActiveWindow() {
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

