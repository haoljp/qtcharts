#include "charttheme_p.h"
#include "qchart.h"
#include "qchartaxis.h"


//series
#include "barchartseries.h"
#include "stackedbarchartseries.h"
#include "percentbarchartseries.h"
#include "qlinechartseries.h"
#include "qscatterseries.h"
#include "qpieseries.h"
#include "qpieslice.h"

//items
#include "axisitem_p.h"
#include "bargroup.h"
#include "stackedbargroup.h"
#include "linechartitem_p.h"
#include "percentbargroup.h"
#include "scatterpresenter_p.h"
#include "piepresenter.h"

//themes
#include "chartthemevanilla_p.h"
#include "chartthemeicy_p.h"
#include "chartthemegrayscale_p.h"
#include "chartthemescientific_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

/* TODO
    case QChart::ChartThemeUnnamed1:
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xff3fa9f5)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xff7AC943)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF931E)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF1D25)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF7BAC)), 2));

        m_gradientStartColor = QColor(QRgb(0xfff3dc9e));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
*/

ChartTheme::ChartTheme(QChart::ChartTheme id)
{
    m_id = id;
    m_seriesColor.append(QRgb(0xff000000));
    m_seriesColor.append(QRgb(0xff707070));
    m_gradientStartColor = QColor(QRgb(0xffffffff));
    m_gradientEndColor = QColor(QRgb(0xffafafaf));
}


ChartTheme* ChartTheme::createTheme(QChart::ChartTheme theme)
{
    switch(theme) {
        case QChart::ChartThemeDefault:
            return new ChartTheme();
        case QChart::ChartThemeVanilla:
            return new ChartThemeVanilla();
        case QChart::ChartThemeIcy:
            return new ChartThemeIcy();
        case QChart::ChartThemeGrayscale:
            return new ChartThemeGrayscale();
        case QChart::ChartThemeScientific:
            return new ChartThemeScientific();
    }
}

void ChartTheme::decorate(QChart* chart)
{
    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, m_gradientStartColor);
    backgroundGradient.setColorAt(1.0, m_gradientEndColor);
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setChartBackgroundBrush(backgroundGradient);
}
//TODO helper to by removed later
void ChartTheme::decorate(ChartItem* item, QChartSeries* series,int count)
{
    switch(series->type())
    {
        case QChartSeries::SeriesTypeLine: {
            QLineChartSeries* s = static_cast<QLineChartSeries*>(series);
            LineChartItem* i = static_cast<LineChartItem*>(item);
            decorate(i,s,count);
            break;
        }
        case QChartSeries::SeriesTypeBar: {
            BarChartSeries* b = static_cast<BarChartSeries*>(series);
            BarGroup* i = static_cast<BarGroup*>(item);
            decorate(i,b,count);
            break;
        }
        case QChartSeries::SeriesTypeStackedBar: {
            StackedBarChartSeries* s = static_cast<StackedBarChartSeries*>(series);
            StackedBarGroup* i = static_cast<StackedBarGroup*>(item);
            decorate(i,s,count);
            break;
        }
        case QChartSeries::SeriesTypePercentBar: {
            PercentBarChartSeries* s = static_cast<PercentBarChartSeries*>(series);
            PercentBarGroup* i = static_cast<PercentBarGroup*>(item);
            decorate(i,s,count);
            break;
        }
        case QChartSeries::SeriesTypeScatter: {
            QScatterSeries* s = qobject_cast<QScatterSeries*>(series);
            Q_ASSERT(s);
            ScatterPresenter* i = static_cast<ScatterPresenter*>(item);
            Q_ASSERT(i);
            decorate(i, s, count);
            break;
        }
        case QChartSeries::SeriesTypePie: {
            QPieSeries* s = static_cast<QPieSeries*>(series);
            PiePresenter* i = static_cast<PiePresenter*>(item);
            decorate(i,s,count);
            break;
        }
        default:
        qDebug()<<"Wrong item to be decorated by theme";
        break;
    }

}

void ChartTheme::decorate(LineChartItem* item, QLineChartSeries* series,int count)
{
    QPen pen;
    if(pen != series->pen()){
        item->setPen(series->pen());
        return;
    }
    pen.setColor(m_seriesColor.at(count%m_seriesColor.size()));
    pen.setWidthF(2);
    item->setPen(pen);
}

void ChartTheme::decorate(BarGroup* item, BarChartSeries* series,int count)
{
    // TODO: better way to descide series color and remove hard coded colors.
    item->resetBrushes();
    for (int i=0; i<m_seriesColor.count(); i++) {
        QBrush brush(m_seriesColor.at(i));
        item->addBrush(brush);
    }
    item->addBrush(QBrush(QColor(255,0,0,128)));
    item->addBrush(QBrush(QColor(255,255,0,128)));
    item->addBrush(QBrush(QColor(0,255,0,128)));
    item->addBrush(QBrush(QColor(0,0,255,128)));
    item->addBrush(QBrush(QColor(255,128,0,128)));
}

void ChartTheme::decorate(StackedBarGroup* item, StackedBarChartSeries* series,int count)
{
    // TODO: better way to descide series color and remove hard coded colors.
    item->resetBrushes();
    for (int i=0; i<m_seriesColor.count(); i++) {
        QBrush brush(m_seriesColor.at(i));
        item->addBrush(brush);
    }
    item->addBrush(QBrush(QColor(255,0,0,128)));
    item->addBrush(QBrush(QColor(255,255,0,128)));
    item->addBrush(QBrush(QColor(0,255,0,128)));
    item->addBrush(QBrush(QColor(0,0,255,128)));
    item->addBrush(QBrush(QColor(255,128,0,128)));
}

void ChartTheme::decorate(PercentBarGroup* item, PercentBarChartSeries* series,int count)
{
    // TODO: better way to descide series color and remove hard coded colors.
    item->resetBrushes();
    for (int i=0; i<m_seriesColor.count(); i++) {
        QBrush brush(m_seriesColor.at(i));
        item->addBrush(brush);
    }
    item->addBrush(QBrush(QColor(255,0,0,128)));
    item->addBrush(QBrush(QColor(255,255,0,128)));
    item->addBrush(QBrush(QColor(0,255,0,128)));
    item->addBrush(QBrush(QColor(0,0,255,128)));
    item->addBrush(QBrush(QColor(255,128,0,128)));
}

void ChartTheme::decorate(ScatterPresenter* presenter, QScatterSeries* series, int count)
{
    Q_ASSERT(presenter);
    Q_ASSERT(series);

    QColor color = m_seriesColor.at(count % m_seriesColor.size());
    // TODO: define alpha in the theme? or in the series?
    color.setAlpha(120);

    QBrush brush(color, Qt::SolidPattern);
    presenter->m_markerBrush = brush;

    QPen pen(brush, 1);
    pen.setColor(color);
    presenter->m_markerPen = pen;
}

void ChartTheme::decorate(PiePresenter* item, QPieSeries* series, int /*count*/)
{
    // create a list of slice colors based on current theme
    int i = 0;
    QList<QColor> colors;
    while (colors.count() < series->count()) {

        // get base color
        QColor c = m_seriesColor[i++];
        i = i % m_seriesColor.count();

        // -1 means achromatic color -> cannot manipulate lightness
        // TODO: find a better way to randomize lightness
        if (c.toHsv().hue() == -1)
            qWarning() << "ChartTheme::decorate() warning: achromatic theme color";

        // randomize lightness
        qreal f = 50 + (qrand() % 100); // 50 is 50% darker, 100 is the same, 150 is 50% lighter
        c = c.lighter(f);

        // find duplicates
        bool isUnique = true;
        foreach (QColor color, colors) {
            if (c == color)
                isUnique = false;
        }

        // add to array if unique
        //if (isUnique)
            colors << c;
    }

    // finally update colors
    foreach (QPieSlice* s, series->slices()) {
        s->setPen(QPen(Qt::black)); // TODO: get from theme
        s->setBrush(colors.takeFirst());
    }
}


void ChartTheme::decorate(QChartAxis& axis,AxisItem* item)
{
    //TODO: dummy defults for now

    axis.setLabelsBrush(Qt::black);
    axis.setLabelsPen(Qt::NoPen);
    axis.setShadesPen(Qt::NoPen);
    axis.setShadesOpacity(0.5);
    item->handleAxisChanged(axis);
}

QTCOMMERCIALCHART_END_NAMESPACE
