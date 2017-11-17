#include "historyform.h"
#include "ui_historyform.h"

#include "models/historymodel.h"
#include "includes/const.h"

#include <QClipboard>
#include <QFontMetrics>
#include <QLabel>
#include <QToolTip>

HistoryForm::HistoryForm(HistoryModel *model, QWidget *parent) :
    QWidget(parent, Qt::Popup),
    m_model(model),
    ui(new Ui::HistoryForm) {

    ui->setupUi(this);
    ui->listView->setModel(model);

    auto font = QApplication::font();
    m_metrics = new QFontMetrics(font);
    auto currentSize = size();
    currentSize.setHeight((m_metrics->height() + 3) * HistoryModel::getMaxCount());
    resize(currentSize);

    ui->listView->setSizeAdjustPolicy(QListView::AdjustToContents);
    connect(ui->listView, &QListView::activated, this, &HistoryForm::onListActivated);
}

HistoryForm::~HistoryForm() {
    delete ui;
}

void HistoryForm::setMainColor(const QColor &color) {    
    qDebug() << color;

    int luminance = color.red()*0.2126 + color.green()*0.7152 + color.blue()*0.0722;
    auto fontColor = luminance > 179 ? QColor(Qt::black) : QColor(Qt::white);

    auto styleBack = QString("*{background-color: rgb(%1, %2, %3);}")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue());
    auto styleFont = QString("QListView{color: rgb(%1, %2, %3);outline: none; show-decoration-selected: 0;}")
            .arg(fontColor.red())
            .arg(fontColor.green())
            .arg(fontColor.blue());

    auto styleItem = QString("QListView::item:selected{background-color: palette(highlight); color: palette(highlightedText);}");

    QStringList styles = {styleBack, styleFont, styleItem};
    ui->listView->setStyleSheet(styles.join(' '));
}

void HistoryForm::onListActivated(const QModelIndex &index) {
    emit itemActivated(m_model->getValueByRow(index.row()));
}

void HistoryForm::adjustFormSize() {
    Q_ASSERT(m_metrics);    

    QString longestStr = "";
    int longestPixels = 0;
    for(auto i = 0; i < m_model->rowCount(); ++i) {
        auto str = m_model->index(i).data().toString();
        auto strPixels = m_metrics->width(str);
        if(longestPixels < strPixels) {
            longestStr = str;
            longestPixels = strPixels;
        }
    }

    qDebug() << "Longest String is " << longestStr << " " << longestPixels;

    auto currentSize = size();
    qDebug() << "Size was " << currentSize;
    currentSize.setWidth(longestPixels + 10);
    qDebug() << "Size is set to " << currentSize;
    resize(currentSize);
    qDebug() << "Size now " << size();
}

void HistoryForm::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    ui->listView->setCurrentIndex(m_model->index(0));
    ui->listView->setFocus();
}
