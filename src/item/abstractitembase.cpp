#include "abstractitembase.h"
#include <QDebug>
#include <QPainter>
#include <QtWidgets>

AbstractItemBase::AbstractItemBase(const QRectF rect, QGraphicsItem *parent) : QGraphicsObject(parent)
{
    m_itemType = ItemType::Rect;
    m_name = "";
    m_id = -1;
    m_scaleFactor = 1;
    m_renderQuality = false;
    m_boundingRect = rect;
    m_exportFactorList = QList<ExportLevel>();

    QPainterPath path;
    path.addRect(rect);
    setShape(path);

}

AbstractItemBase::AbstractItemBase(const AbstractItemBase &other) : QGraphicsObject(other.parentItem())
{
    m_itemType = other.m_itemType;
    m_name = other.m_name;
    m_id = other.m_id;
    m_scaleFactor = other.m_scaleFactor;
    m_renderQuality = other.m_renderQuality;
    m_boundingRect = other.m_boundingRect;
    m_exportFactorList = other.m_exportFactorList;
    m_shape = other.m_shape;
    m_invaliateCache = other.m_invaliateCache;
    m_rect = other.m_rect;
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void AbstractItemBase::setID(int id)
{
    m_id = id;
}

int AbstractItemBase::ID() const
{
    return m_id;
}

void AbstractItemBase::setName(QString name)
{
    m_name = name;
}

QString AbstractItemBase::name() const
{
    return m_name;
}

void AbstractItemBase::setItemType(ItemType type)
{
    m_itemType = type;
}

ItemType AbstractItemBase::itemType() const
{
    return m_itemType;
}

void AbstractItemBase::setInvalidateCache(bool invalidate)
{
    m_invaliateCache = invalidate;
}

bool AbstractItemBase::invalidateCache() const
{
    return m_invaliateCache;
}

void AbstractItemBase::setScaleFactor(qreal scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

qreal AbstractItemBase::scaleFactor() const
{
    return m_scaleFactor;
}

void AbstractItemBase::setShape(QPainterPath itemShape)
{
    m_shape = itemShape;
    m_rect = m_shape.boundingRect().normalized();
    setInvalidateCache(true);
    setTransformOriginPoint(m_rect.center());
    update();
}

QPainterPath AbstractItemBase::shape() const
{
    return m_shape;
}

QRectF AbstractItemBase::rect() const
{
    return m_rect;
}

void AbstractItemBase::setBoundingRect(QRectF boundingrect)
{
    m_boundingRect = boundingrect;
}

QRectF AbstractItemBase::boundingRect() const
{
    return m_boundingRect;
}

void AbstractItemBase::setHighRenderQuality(bool isHighResolution)
{
    m_renderQuality = isHighResolution;


//    QList<QGraphicsItem*> list = childItems();

//    if(list.count() == 0) return;

//    foreach(QGraphicsItem *child, this->childItems()){

//        qDebug() << "item child" << child;

//        AbstractItemBase *abItem = static_cast<AbstractItemBase*>(child);
//        if(abItem) {
//            //qDebug() << "item child" << abItem->ID();
//            //abItem->setHighRenderQuality(isHighResolution);
//            //abItem->update();
//        }
//    }

}

bool AbstractItemBase::highRenderQuality() const
{
    return m_renderQuality;
}


QPointF AbstractItemBase::anchorTopLeft() const
{
    return this->scenePos();
}

QPointF AbstractItemBase::anchorTop() const
{
    return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y());
}

QPointF AbstractItemBase::anchorTopRight() const
{
    return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y());
}

QPointF AbstractItemBase::anchorRight() const
{
    return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y() + rect().height() / 2);
}

QPointF AbstractItemBase::anchorBottomRight() const
{
    return QPointF(this->scenePos().x() + rect().width(), this->scenePos().y() + rect().height());
}

QPointF AbstractItemBase::anchorBottom() const
{
    return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y() + rect().height());
}

QPointF AbstractItemBase::anchorBottomLeft() const
{
    return QPointF(this->scenePos().x(), this->scenePos().y() + rect().height());
}

QPointF AbstractItemBase::anchorLeft() const
{
    return QPointF(this->scenePos().x(), this->scenePos().y() + rect().height() / 2);
}

QPointF AbstractItemBase::anchorCenter() const
{
    return QPointF(this->scenePos().x() + rect().width() / 2, this->scenePos().y() + rect().height() / 2);
}

/***************************************************
 *
 * Members
 *
 ***************************************************/


void AbstractItemBase::addExportLevel(ExportLevel exportLevel, int index){
    if(index < 0){
        m_exportFactorList.append(exportLevel);
    }else m_exportFactorList.insert(index, exportLevel);
}

void AbstractItemBase::removeExportLevel(int index){
    m_exportFactorList.removeAt(index);
}

void AbstractItemBase::removeExportLevel(ExportLevel exportLevel)
{
    m_exportFactorList.removeOne(exportLevel);
}

void AbstractItemBase::updateExportLevel(ExportLevel exportLevel)
{
    for(int i=0; i < m_exportFactorList.count(); i++){
        ExportLevel m_property = m_exportFactorList.at(i);
        if(m_property.ID() == exportLevel.ID()){
            m_exportFactorList.replace(i,exportLevel);
            return;
        }
    }
}

QList<ExportLevel> AbstractItemBase::exportLevels() const
{
    return m_exportFactorList;
}

ExportLevel AbstractItemBase::exportLevel(int index)
{
    return m_exportFactorList.value(index);
}

QList<AbstractItemBase *> AbstractItemBase::children()
{
    return m_children;
}

