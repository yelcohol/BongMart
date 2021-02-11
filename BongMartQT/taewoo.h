#ifndef TAEWOO_H
#define TAEWOO_H

#include <QDialog>

namespace Ui {
class Taewoo;
}

class Taewoo : public QDialog
{
    Q_OBJECT

public:
    explicit Taewoo(QWidget *parent = nullptr);
    ~Taewoo();

private slots:
    void on_pushButton_clicked();

    void on_OK_Cancel_accepted();

private:
    Ui::Taewoo *ui;
};

#endif // TAEWOO_H
