#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QWidget>

class ClickLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickLabel(QWidget* parent=nullptr);
    ~ClickLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // CLICKLABEL_H
