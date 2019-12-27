#ifndef IP_SHADOWS_H
#define IP_SHADOWS_H

#include <QWidget>
#include <QList>
#include "src/item/abstractitembase.h"
#include "src/item/itembase.h"
#include "src/item/itemrect.h"
#include "src/item/itemoval.h"
#include "src/item/itemtext.h"
#include "src/item/shadow.h"
#include "../components/propertyshadow.h"

namespace Ui {
class ipShadows;
}

class ipShadows : public QWidget
{
    Q_OBJECT

public:
    explicit ipShadows(QWidget *parent = nullptr);
    ~ipShadows();

    void setActiveItem(AbstractItemBase *item);

private:
    Ui::ipShadows *ui;

    ItemBase *m_item;
    QList<PropertyShadow*>*m_propertyItemList;

    void loadProperties();
    void resetItems();
    void unloadItems();
    void loadShadows();
    void addShadow(PropertyShadow *propertyItem);
    void removeShadow(PropertyShadow *propertyItem);

signals:
    void sendCollapse(bool);

public slots:
    void newShadow();

private slots:
    void updateItem();
};

#endif // IP_SHADOWS_H
