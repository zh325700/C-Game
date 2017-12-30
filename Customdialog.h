#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QComboBox>


class CustomDialog : public QDialog
{
public:
    CustomDialog(const QStringList& items);
    QComboBox* comboBox() { return box; }

private:
    QComboBox* box;
};

#endif // CUSTOMDIALOG_H
