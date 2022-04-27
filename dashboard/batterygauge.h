#ifndef BATTERYGAUGE_H
#define BATTERYGAUGE_H

#include <QObject>
#include <QQuickPaintedItem>

class Batterygauge : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qreal BatterygaugeSize READ getBatterygaugeSize WRITE setBatterygaugeSize NOTIFY BatterygaugeSizeChanged)
    Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal alignAngle READ getAlignAngle WRITE setAlignAngle NOTIFY alignAngleChanged)
    Q_PROPERTY(qreal lowestRange READ getLowestRange WRITE setLowestRange NOTIFY lowestRangeChanged)
    Q_PROPERTY(qreal highestRange READ getHighestRange WRITE setHighestRange NOTIFY highestRangeChanged)
    Q_PROPERTY(qreal batteryLevel READ getBatteryLevel WRITE setBatteryLevel NOTIFY batteryLevelChanged)
    Q_PROPERTY(int arcWidth READ getArcWidth WRITE setArcWidth NOTIFY arcWidthChanged)
    Q_PROPERTY(QColor outerColor READ getOuterColor WRITE setOuterColor NOTIFY outerColorChanged)
    Q_PROPERTY(QColor innerColor READ getInnerColor WRITE setInnerColor NOTIFY innerColorChanged)
    Q_PROPERTY(QColor innerColor READ getBatteryLevelColor WRITE setBatteryLevelColor NOTIFY batteryLevelColorChanged)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:
    Batterygauge(QQuickItem *parent = 0);
    virtual void paint(QPainter *painter);

    qreal   getBatterygaugeSize();
    qreal   getStartAngle();
    qreal   getAlignAngle();
    qreal   getLowestRange();
    qreal   getHighestRange();
    qreal   getBatteryLevel();
    int     getArcWidth();
    QColor  getOuterColor();
    QColor  getInnerColor();
    QColor  getBatteryLevelColor();
    QColor  getTextColor();
    QColor  getBackgroundColor();

    void    setBatterygaugeSize(qreal size);
    void    setStartAngle(qreal startAngle);
    void    setAlignAngle(qreal angle);
    void    setLowestRange(qreal losbwestRange);
    void    setHighestRange(qreal highestRange);
    void    setBatteryLevel(qreal batteryLevel);
    void    setArcWidth(int arcWidth);
    void    setOuterColor(QColor outerColor);
    void    setInnerColor(QColor innerColor);
    void    setBatteryLevelColor(QColor batteryLevelColor);
    void    setTextColor(QColor textColor);
    void    setBackgroundColor(QColor backgroundColor);

signals:
    void    BatterygaugeSizeChanged();
    void    startAngleChanged();
    void    alignAngleChanged();
    void    lowestRangeChanged();
    void    highestRangeChanged();
    void    batteryLevelChanged();
    void    arcWidthChanged();
    void    outerColorChanged();
    void    innerColorChanged();
    void    batteryLevelColorChanged();
    void    textColorChanged();
    void    backgroundColorChanged();

private:
    qreal   m_BatterygaugeSize;
    qreal   m_StartAngle;
    qreal   m_AlignAngle;
    qreal   m_LowestRange;
    qreal   m_HighestRange;
    qreal   m_Batterylevel;
    int     m_ArcWidth;
    QColor  m_OuterColor;
    QColor  m_InnerColor;
    QColor  m_BatteryLevelColor;
    QColor  m_TextColor;
    QColor  m_BackgroundColor;

};

#endif // BATTERYGAUGE_H
