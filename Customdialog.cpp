#include "Customdialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>

CustomDialog::CustomDialog(const QStringList& items)
{
    this->setWindowTitle("Restore");
    setLayout(new QHBoxLayout());

    QLabel* text = new QLabel("choose a file: ");
    layout()->addWidget(text);

    box = new QComboBox;
    box->addItems(items);
    layout()->addWidget(box);

    QPushButton* ok = new QPushButton("ok");
    layout()->addWidget(ok);
    connect(ok, &QPushButton::clicked, this, [this]()
    {
        accept();
    });
}
