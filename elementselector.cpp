#include "elementselector.h"

ElementSelector::ElementSelector(QWidget *parent) : QWidget(parent)
{
    QPushButton *shotButton = new QPushButton("Shot");
    QPushButton *assetButton = new QPushButton("Asset");
    QPushButton *backButton = new QPushButton("<-Back");

    shotButton->setFixedSize(300,300);
    assetButton->setFixedSize(300,300);
//    shotButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    assetButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(assetButton,0,0);
    layout->addWidget(shotButton,0,1);
    layout->addWidget(backButton,1,0,1,2);

    setLayout(layout);

    connect(backButton,SIGNAL(clicked(bool)),this,SLOT(backButtonClick()));
    connect(assetButton,SIGNAL(clicked(bool)),this,SLOT(assetSeleteButtonClick()));
    connect(shotButton,SIGNAL(clicked(bool)),this,SLOT(shotSeleteButtonClick()));

}
ElementSelector::~ElementSelector()
{
    qDebug() << "Destroy window";
}

void ElementSelector::backButtonClick()
{
    emit goToProjectSelector();
}

void ElementSelector::assetSeleteButtonClick()
{
   emit goToAssetSelector();
}

void ElementSelector::shotSeleteButtonClick()
{
    emit goToShotSelector();
}
