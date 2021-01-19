#ifndef ELEMENTSELECTOR_H
#define ELEMENTSELECTOR_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>

class ElementSelector : public QWidget
{
    Q_OBJECT
public:
    explicit ElementSelector(QWidget *parent = nullptr);
    ~ElementSelector();

signals:
    void goToProjectSelector();
    void goToAssetSelector();
    void goToShotSelector();

private slots:
    void backButtonClick();
    void assetSeleteButtonClick();
    void shotSeleteButtonClick();
};

#endif // ELEMENTSELECTOR_H
