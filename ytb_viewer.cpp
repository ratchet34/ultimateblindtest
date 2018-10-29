#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QUrl>
#include <QWidget>
#include <QTimer>

#include "ytb_viewer.h"
#include "mainwindow.h"

ytb_viewer::ytb_viewer()
{
    QObject::connect(this, SIGNAL(loadFinished(bool)), this, SLOT(waitClick(bool)));
    this->hide();

}

void ytb_viewer::waitClick(bool loaded)
{
    if (loaded)
    {
        QTimer::singleShot(5000, this, SLOT(clickCinema()));
    }
}

void ytb_viewer::clickCinema()
{
    QString jsClick = QStringLiteral("var button = document.getElementsByClassName(\"ytp-size-button ytp-button\")[0];if (button) {button.click();}");
    this->page()->runJavaScript(jsClick, [](const QVariant &result){ qDebug() << result; });
}

void ytb_viewer::showYtbViewer()
{
    this->show();
}

void ytb_viewer::hideYtbViewer()
{
    this->hide();
}

void ytb_viewer::clickAd()
{
    QString jsClick = QStringLiteral("var button = document.getElementsByClassName(\"videoAdUiSkipButton videoAdUiAction videoAdUiFixedPaddingSkipButton\")[0];if (button) {button.click();}");
    this->page()->runJavaScript(jsClick, [](const QVariant &result){ qDebug() << result; });
}

void ytb_viewer::blockCinema()
{
    QObject::disconnect(this, SIGNAL(loadFinished(bool)), this, SLOT(waitClick(bool)));
}
