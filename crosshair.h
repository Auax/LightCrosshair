#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <QMainWindow>
#include <QPen>

QT_BEGIN_NAMESPACE
namespace Ui { class crosshair; }
QT_END_NAMESPACE

struct RGBA {
    int r = 0;
    int g = 255;
    int b = 0;
    int a = 255;
};

class crosshair : public QMainWindow
{
    Q_OBJECT
public:
    crosshair(struct RGBA rgba,
              QWidget *parent = nullptr,
              int window_size = 24,
              int stroke_width = 2,
              int distance = 10);
    ~crosshair();

protected:
    void paintEvent(QPaintEvent *event);
    void center();

private:
    Ui::crosshair *ui;
    int window_size;
    int stroke_width;
    struct RGBA rgba;
    int distance;
    QPen pen;
};

#endif // CROSSHAIR_H
