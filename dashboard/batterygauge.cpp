#include <QPainter>
#include "batterygauge.h"

Batterygauge::Batterygauge(QQuickItem *parent)
    :QQuickPaintedItem(parent),
      m_BatterygaugeSize(350), // touch screen is 800 x 480
      m_StartAngle(50),
      m_AlignAngle(260), // it should be 360 - m_StartAngle*3 for good looking
      m_LowestRange(0),
      m_HighestRange(87),
      m_BackgroundColor(Qt::transparent),
      m_Batterylevel(0),
      m_ArcWidth(15),
      m_OuterColor(QColor(12,16,247)),
      m_InnerColor(QColor(51,88,255,80)),
      m_TextColor(QColor(0,0,0)),
      m_BatteryLevelColor(QColor(128,255,0))

{

}

void Batterygauge::paint(QPainter *painter)
{

    QRectF rect = this->boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);

    double startAngle;
    double spanAngle;

    startAngle = m_StartAngle - 40;
    spanAngle = 0 - m_AlignAngle;

    //all arc
    painter->save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_OuterColor);
    painter->setPen(pen);
   // painter->drawRect(rect);
    painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, spanAngle * 16);
    painter->restore();

    //inner pie
    int pieSize = m_BatterygaugeSize/8.5;
    painter->save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_OuterColor);
    painter->setBrush(m_OuterColor);
    painter->setPen(pen);

    painter->drawArc(rect.adjusted(pieSize, pieSize, -pieSize, -pieSize), startAngle * 16, spanAngle * 16);
    painter->restore();

    //text which shows the value
    painter->save();
    QFont font("Halvetica",52,QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_BatterygaugeSize/30, m_BatterygaugeSize/30, -m_BatterygaugeSize/30, -m_BatterygaugeSize/4), Qt::AlignCenter  ,QString::number(m_Batterylevel));
    painter->drawText(rect.adjusted(m_BatterygaugeSize , m_BatterygaugeSize + 25, -m_BatterygaugeSize, -m_BatterygaugeSize + 25), Qt::AlignCenter ,"Ah");

    painter->restore();

    //current active progress
    painter->save();
    int size = m_BatterygaugeSize/12;
    pen.setWidth(m_ArcWidth * 1);
    pen.setColor(m_BatteryLevelColor);
    qreal valueToAngle = ((m_Batterylevel - m_LowestRange)/(m_HighestRange - m_LowestRange)) * spanAngle;
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(size, size, -size, -size), startAngle * 16, valueToAngle * 16);
    painter->restore();

}


qreal Batterygauge::getBatterygaugeSize()
{
    return m_BatterygaugeSize;
}

qreal Batterygauge::getStartAngle()
{
    return m_StartAngle;
}


qreal Batterygauge::getAlignAngle()
{
    return m_AlignAngle;
}


qreal Batterygauge::getLowestRange()
{
    return m_LowestRange;
}

qreal Batterygauge::getHighestRange()
{
    return m_HighestRange;
}

qreal Batterygauge::getBatteryLevel()
{
    return m_Batterylevel;
}

int Batterygauge::getArcWidth()
{
    return m_ArcWidth;
}

QColor Batterygauge::getOuterColor()
{
    return m_OuterColor;
}

QColor Batterygauge::getInnerColor()
{
    return m_InnerColor;
}

QColor Batterygauge::getBatteryLevelColor()
{
    return m_BatteryLevelColor;
}

QColor Batterygauge::getTextColor()
{
    return m_TextColor;
}

QColor Batterygauge::getBackgroundColor()
{
    return m_BackgroundColor;
}



void Batterygauge::setBatterygaugeSize(qreal size)
{
    if(m_BatterygaugeSize == size)
        return;
    m_BatterygaugeSize = size;

    emit BatterygaugeSizeChanged();
}

void Batterygauge::setStartAngle(qreal startAngle)
{
    if(m_StartAngle == startAngle)
        return;

    m_StartAngle = startAngle;

    emit startAngleChanged();
}

void Batterygauge::setAlignAngle(qreal angle)
{
    if(m_StartAngle == angle)
        return;

    m_StartAngle = angle;

    emit alignAngleChanged();
}

void Batterygauge::setLowestRange(qreal lowestRange)
{
    if(m_LowestRange == lowestRange)
        return;

    m_LowestRange = lowestRange;

    emit lowestRangeChanged();
}

void Batterygauge::setHighestRange(qreal highestRange)
{
    if(m_HighestRange == highestRange)
        return;

    m_HighestRange = highestRange;

    emit highestRangeChanged();
}

void Batterygauge::setBatteryLevel(qreal batteryLevel)
{
    if(m_Batterylevel == batteryLevel)
        return;

    m_Batterylevel = batteryLevel;
    update();
    emit batteryLevelChanged();
}

void Batterygauge::setArcWidth(int arcWidth)
{
    if(m_ArcWidth == arcWidth)
        return;

    m_ArcWidth = arcWidth;

    emit arcWidthChanged();
}

void Batterygauge::setOuterColor(QColor outerColor)
{
    if(m_OuterColor == outerColor)
        return;

    m_OuterColor = outerColor;

    emit outerColorChanged();
}

void Batterygauge::setInnerColor(QColor innerColor)
{
    if(m_InnerColor == innerColor)
        return;

    m_InnerColor = innerColor;

    emit innerColorChanged();
}

void Batterygauge::setBatteryLevelColor(QColor batteryLevelColor)
{
    if(m_InnerColor == batteryLevelColor)
        return;

    m_BatteryLevelColor = batteryLevelColor;

    emit batteryLevelColorChanged();
}


void Batterygauge::setTextColor(QColor textColor)
{
    if(m_TextColor == textColor)
        return;

    m_TextColor = textColor;

    emit textColorChanged();
}

void Batterygauge::setBackgroundColor(QColor backgroundColor)
{
    if(m_BackgroundColor == backgroundColor)
        return;

    m_BackgroundColor = backgroundColor;

    emit backgroundColorChanged();
}
