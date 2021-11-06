#include "crosshair.h"
#include "./ui_crosshair.h"
#include <math.h>
#include <QtCore>
#include <QPen>
#include <QPainter>
#include<QScreen>

crosshair::crosshair(struct RGBA rgba,
                     QWidget *parent,
                     int window_size,
                     int stroke_width,
                     int distance): QMainWindow(parent), ui(new Ui::crosshair)
{
    // Init checks
    assert(("Distance is too long!", distance <= window_size / 2 - 1));
    assert(("Window size must be an even number!", window_size % 2 == 0));

    ui->setupUi(this);

    this->window_size = window_size;
    this->stroke_width = stroke_width;
    this->rgba = rgba;
    this->distance = distance;
    this->pen = QPen(QColor(rgba.r, rgba.g, rgba.b, rgba.a));
    this->pen.setWidth(stroke_width);

    // Resize window to desired size
    this->resize(window_size, window_size);
    // Disable small resize icon
    this->statusBar()->setSizeGripEnabled(false);

    // Set windows features
    // Transparent, on top, and frameless
    this->setWindowFlags(
        Qt::FramelessWindowHint |
        Qt::WindowStaysOnTopHint |
        Qt::WindowTransparentForInput |
        Qt::Tool);

    // Set transparent attribute
    this->setAttribute(Qt::WA_TranslucentBackground);

    // Center screen
    move(screen()->geometry().center() - frameGeometry().center());
}

crosshair::~crosshair()
{
    delete ui;
}

// Override the paintEvent method
void crosshair::paintEvent(QPaintEvent *e) {

    // Distance from the center
    // (higher the number the closer it is from the center)
    QPainter painter(this);
    painter.setPen(this->pen);

    // Half screen size
    int half_s = reinterpret_cast<int>(this->window_size / 2);
    int m_const = 1;
    int dist = this->distance + ceil(this->pen.width() / 2);

    // Drawing the crosshair

    // Top
    painter.drawLine(half_s, 0, half_s, half_s - dist);
     // Bottom
    painter.drawLine(half_s, half_s + dist, half_s, this->window_size - m_const);
    // Left
    painter.drawLine(0, half_s, half_s - dist, half_s);
    // Right
    painter.drawLine(half_s + dist, half_s, this->window_size - m_const, half_s);
}

