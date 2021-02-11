#ifndef NOSTOCK_H
#define NOSTOCK_H

#include <QDialog>

namespace Ui {
class nostock;
}

class nostock : public QDialog
{
    Q_OBJECT

public:
    explicit nostock(QWidget *parent = nullptr);
    ~nostock();

private:
    Ui::nostock *ui;
};

#endif // NOSTOCK_H
