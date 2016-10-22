#include "historyform.h"
#include "ui_historyform.h"

#include "models/historymodel.h"
#include "includes/const.h"

#include <QClipboard>
#include <QFontMetrics>

HistoryForm::HistoryForm(HistoryModel *model, QWidget *parent) :
    QWidget(parent, Qt::Popup),
    m_model(model),
    ui(new Ui::HistoryForm) {

    ui->setupUi(this);
    ui->listView->setModel(model);

    auto font = QApplication::font();
    m_metrics = new QFontMetrics(font);
    auto currentSize = size();
    currentSize.setHeight(m_metrics->height() * model->getMaxCount());
    resize(currentSize);

    ui->listView->setSizeAdjustPolicy(QListView::AdjustToContents);
    connect(ui->listView, &QListView::doubleClicked, this, &HistoryForm::onListDoubleClicked);
}

HistoryForm::~HistoryForm() {
    delete ui;
}

void HistoryForm::onListDoubleClicked(const QModelIndex &index) {
    emit itemDoubleClicked(index.row());
}

void HistoryForm::adjustFormSize() {
    Q_ASSERT(m_metrics);

    QString longestStr = "";
    int longestPixels = 0;
    bool longestPixelsValid = true;
    for(auto i = 0; i < m_model->rowCount(); ++i) {
        auto str = m_model->index(i).data().toString();
        if(str.size() > longestStr.size()) {
            longestStr = str;
            longestPixelsValid = false;
        }
        else if (str.size() == longestStr.size()) {
            auto strPixels = m_metrics->width(str);
            if(!longestPixelsValid) {
               longestPixels = m_metrics->width(longestStr);
               longestPixelsValid = true;
            }
            if(longestPixelsValid && longestPixels < strPixels) {
                longestStr = str;
                longestPixels = strPixels;
            }
        }
    }

    if(!longestPixelsValid) {
       longestPixels = m_metrics->width(longestStr);
    }

    qDebug() << "Longest String is " << longestStr << " " << longestPixels;

    auto currentSize = size();
    qDebug() << "Size was " << currentSize;
    currentSize.setWidth(longestPixels + 10);
    qDebug() << "Size is set to " << currentSize;
    resize(currentSize);
    qDebug() << "Size now " << size();
}
