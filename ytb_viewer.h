#ifndef YTB_VIEWER_H
#define YTB_VIEWER_H

#include <QWebEngineView>
#include <QWidget>
#include <QString>

class ytb_viewer : public QWebEngineView
{
    Q_OBJECT

public:
    ytb_viewer();
    void showYtbViewer();
    void hideYtbViewer();
    void clickAd();
    void blockCinema();
public slots:
    void waitClick(bool loaded);
    void clickCinema();
};

#endif // YTB_VIEWER_H
