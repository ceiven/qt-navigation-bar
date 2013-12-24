#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "wnd.h"

Wnd::Wnd(QWidget *parent)
    : QWidget(parent)
{
    navBar       = new NavBar;
    signalWidget = new QListWidget;
    styleBox     = new QComboBox;

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    vLayout->addWidget(styleBox);
    vLayout->addWidget(signalWidget);
    hLayout->addWidget(navBar);
    hLayout->addLayout(vLayout);
    setLayout(hLayout);

    styleBox->addItem("Office2003Gray");
    styleBox->addItem("Office2007Blue");
    styleBox->addItem("Office2007Black");
    styleBox->addItem("Office2007Silver");
    connect(styleBox, SIGNAL(currentIndexChanged(QString)), SLOT(changeStylesheet(QString)));

    connect(navBar, SIGNAL(currentChanged(int)),     SLOT(navBarCurrentChanged(int)));
    connect(navBar, SIGNAL(visibleRowsChanged(int)), SLOT(navBarVisibleRowsChanged(int)));

    navBar->addPage(new QLabel("This is page 1"), "Page 1", QIcon(":/images/mail_yellow.png"));
    navBar->addPage(new QLabel("This is page 2"), "Page 2", QIcon(":/images/calendar.png"));
    navBar->addPage(new QLabel("This is page 3"), "Page 3", QIcon(":/images/client_account_template.png"));
    navBar->addPage(new QLabel("This is page 4"), "Page 4", QIcon(":/images/date_task.png"));
    navBar->addPage(new QLabel("This is page 5"), "Page 5", QIcon(":/images/note.png"));

    navBar->setVisibleRows(3);
    navBar->setStyleSheet(NavBar::loadStyle(":/styles/Office2003Gray.css"));
}

Wnd::~Wnd()
{    
}

void Wnd::changeStylesheet(const QString &styleName)
{
    navBar->setStyleSheet(NavBar::loadStyle(":/styles/" + styleName + ".css"));
}

void Wnd::navBarCurrentChanged(int index)
{
    signalWidget->addItem(QString("currentChanged(%1)").arg(index));
    signalWidget->scrollToBottom();
}

void Wnd::navBarVisibleRowsChanged(int rows)
{
    signalWidget->addItem(QString("visibleRowsChanged(%1)").arg(rows));
    signalWidget->scrollToBottom();
}
