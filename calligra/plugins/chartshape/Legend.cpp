/* This file is part of the KDE project

   Copyright 2007 Johannes Simon <johannes.simon@gmail.com>
   Copyright 2010 Inge Wallin    <inge@lysator.liu.se>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

// Own
#include "Legend.h"

// Qt
#include <QString>
#include <QSizeF>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QFont>
#include <QImage>

// Calligra
#include <KoXmlReader.h>
#include <KoXmlWriter.h>
#include <KoShapeLoadingContext.h>
#include <KoShapeSavingContext.h>
#include <KoOdfLoadingContext.h>
#include <KoOdfStylesReader.h>
#include <KoXmlNS.h>
#include <KoGenStyles.h>
#include <KoUnit.h>
#include <KoColorBackground.h>
#include <KoShapeStroke.h>

// KDChart
#include <KDChartChart>
#include <KDChartBarDiagram>
#include <KDChartAbstractDiagram>
#include <KDChartFrameAttributes>
#include <KDChartBackgroundAttributes>
#include <KDChartLegend>
#include "KDChartConvertions.h"

// Kchart
#include "PlotArea.h"
#include "ScreenConversions.h"
#include "ChartLayout.h"
#include "OdfLoadingHelper.h"

using namespace KChart;

class Legend::Private {
public:
    Private();
    ~Private();

    ChartShape *shape;

    // Properties of the Legend
    QString title;
    bool showFrame;
    QPen framePen;
    QBrush backgroundBrush;
    LegendExpansion expansion;
    Position position;
    QFont font;
    QFont titleFont;
    QColor fontColor;
    Qt::Alignment alignment;
    KoShapeStroke *lineBorder;

    // The connection to KDChart
    KDChart::Legend *kdLegend;

    QImage image;

    mutable bool pixmapRepaintRequested;
    QSizeF lastSize;
    QPointF lastZoomLevel;
};


Legend::Private::Private()
{
    lineBorder = new KoShapeStroke(0.5, Qt::black);
    showFrame = false;
    framePen = QPen();
    framePen.setWidth(0);
    backgroundBrush = QBrush();
    expansion = HighLegendExpansion;
    alignment = Qt::AlignRight;
    pixmapRepaintRequested = true;
    position = EndPosition;
}

Legend::Private::~Private()
{
    delete lineBorder;
}


Legend::Legend(ChartShape *parent)
    : QObject(parent)
    , d(new Private())
{
    Q_ASSERT(parent);

    setShapeId(ChartShapeId);

    d->shape = parent;

    d->kdLegend = new KDChart::Legend();
    d->kdLegend->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    setTitleFontSize(10);
    setTitle(QString());
    setFontSize(8);

    update();

    parent->addShape(this);

    connect (d->kdLegend, SIGNAL(propertiesChanged()),
             this,        SLOT(slotKdLegendChanged()));
    connect (parent, SIGNAL(chartTypeChanged(ChartType)),
             this,   SLOT(slotChartTypeChanged(ChartType)));
}

Legend::~Legend()
{
    delete d->kdLegend;
    delete d;
}


QString Legend::title() const
{
    return d->title;
}

void Legend::setTitle(const QString &title)
{
    d->title = title;
    d->kdLegend->setTitleText(title);
    d->pixmapRepaintRequested = true;

    emit updateConfigWidget();
}

bool Legend::showFrame() const
{
    return d->showFrame;
}

void Legend::setShowFrame(bool show)
{
    d->showFrame = show;
    setStroke(show ? d->lineBorder : 0);

    emit updateConfigWidget();
}

QPen Legend::framePen() const
{
    return d->framePen;
}

void Legend::setFramePen(const QPen &pen)
{
    d->framePen = pen;

    // KDChart
    KDChart::FrameAttributes attributes = d->kdLegend->frameAttributes();
    attributes.setPen(pen);
    d->kdLegend->setFrameAttributes(attributes);

    d->pixmapRepaintRequested = true;
}

QColor Legend::frameColor() const
{
    return d->framePen.color();
}

void Legend::setFrameColor(const QColor &color)
{
    d->framePen.setColor(color);

    // KDChart
    KDChart::FrameAttributes attributes = d->kdLegend->frameAttributes();
    attributes.setVisible(true);
    QPen pen = attributes.pen();
    pen.setColor(color);
    attributes.setPen(pen);
    d->kdLegend->setFrameAttributes(attributes);

    d->pixmapRepaintRequested = true;
}

QBrush Legend::backgroundBrush() const
{
    return d->backgroundBrush;
}

void Legend::setBackgroundBrush(const QBrush &brush)
{
    d->backgroundBrush = brush;

    // KDChart
    KDChart::BackgroundAttributes attributes = d->kdLegend->backgroundAttributes();
    attributes.setVisible(true);
    attributes.setBrush(brush);
    d->kdLegend->setBackgroundAttributes(attributes);

    d->pixmapRepaintRequested = true;
}

QColor Legend::backgroundColor() const
{
    return d->backgroundBrush.color();
}

void Legend::setBackgroundColor(const QColor &color)
{
    d->backgroundBrush.setColor(color);

    // KDChart
    KDChart::BackgroundAttributes attributes = d->kdLegend->backgroundAttributes();
    attributes.setVisible(true);
    QBrush brush = attributes.brush();
    brush.setColor(color);
    attributes.setBrush(brush);
    d->kdLegend->setBackgroundAttributes(attributes);

    d->pixmapRepaintRequested = true;
}

QFont Legend::font() const
{
    return d->font;
}

void Legend::setFont(const QFont &font)
{
    d->font = font;

    // KDChart
    KDChart::TextAttributes attributes = d->kdLegend->textAttributes();
    attributes.setFont(font);
    d->kdLegend->setTextAttributes(attributes);

    d->pixmapRepaintRequested = true;
    emit updateConfigWidget();
}

qreal Legend::fontSize() const
{
    return d->font.pointSizeF();
}

void Legend::setFontSize(qreal size)
{
    d->font.setPointSizeF(size);

    // KDChart
    KDChart::TextAttributes attributes = d->kdLegend->textAttributes();
    KDChart::Measure m = attributes.fontSize();
    m.setValue(size);
    attributes.setFontSize(m);
    d->kdLegend->setTextAttributes(attributes);

    d->pixmapRepaintRequested = true;
    emit updateConfigWidget();
}

void Legend::setFontColor(const QColor &color)
{
    KDChart::TextAttributes attributes = d->kdLegend->textAttributes();
    QPen pen = attributes.pen();
    pen.setColor(color);
    attributes.setPen(pen);
    d->kdLegend->setTextAttributes(attributes);

    d->pixmapRepaintRequested = true;
}

QColor Legend::fontColor() const
{
    KDChart::TextAttributes attributes = d->kdLegend->textAttributes();
    QPen pen = attributes.pen();
    return pen.color();
}

QFont Legend::titleFont() const
{
    return d->titleFont;
}

void Legend::setTitleFont(const QFont &font)
{
    d->titleFont = font;

    // KDChart
    KDChart::TextAttributes attributes = d->kdLegend->titleTextAttributes();
    attributes.setFont(font);
    d->kdLegend->setTitleTextAttributes(attributes);

    d->pixmapRepaintRequested = true;
}

qreal Legend::titleFontSize() const
{
    return d->titleFont.pointSizeF();
}

void Legend::setTitleFontSize(qreal size)
{
    d->titleFont.setPointSizeF(size);

    // KDChart
    KDChart::TextAttributes attributes = d->kdLegend->titleTextAttributes();
    attributes.setFontSize(KDChart::Measure(size, KDChartEnums::MeasureCalculationModeAbsolute));
    d->kdLegend->setTitleTextAttributes(attributes);

    d->pixmapRepaintRequested = true;
}

LegendExpansion Legend::expansion() const
{
    return d->expansion;
}

void Legend::setExpansion(LegendExpansion expansion)
{
    d->expansion = expansion;
    d->kdLegend->setOrientation(LegendExpansionToQtOrientation(expansion));
    d->pixmapRepaintRequested = true;

    emit updateConfigWidget();
}

Qt::Alignment Legend::alignment() const
{
    return d->alignment;
}

void Legend::setAlignment(Qt::Alignment alignment)
{
    d->alignment = alignment;
}

Position Legend::legendPosition() const
{
    return d->position;
}

void Legend::setLegendPosition(Position position)
{
    d->position = position;
    d->pixmapRepaintRequested = true;

    d->shape->layout()->setPosition(this, position);
}

void Legend::setSize(const QSizeF &newSize)
{
    QSize newSizePx = ScreenConversions::scaleFromPtToPx(newSize);
    d->kdLegend->resize(newSizePx);
    d->kdLegend->resizeLayout(newSizePx);
    KoShape::setSize(newSize);
}


void Legend::paintPixmap(QPainter &painter, const KoViewConverter &converter)
{
    // Adjust the size of the painting area to the current zoom level
    const QSize paintRectSize = converter.documentToView(d->lastSize).toSize();
    d->image = QImage(paintRectSize, QImage::Format_ARGB32);

    QPainter pixmapPainter(&d->image);
    pixmapPainter.setRenderHints(painter.renderHints());
    pixmapPainter.setRenderHint(QPainter::Antialiasing, false);

    // Scale the painter's coordinate system to fit the current zoom level.
    applyConversion(pixmapPainter, converter);
    d->kdLegend->paint(&pixmapPainter);
}

void Legend::paint(QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &paintContext)
{
    //painter.save();

    // First of all, scale the painter's coordinate system to fit the current zoom level
    applyConversion(painter, converter);

    // Calculate the clipping rect
    QRectF paintRect = QRectF(QPointF(0, 0), size());
    //clipRect.intersect(paintRect);
    painter.setClipRect(paintRect, Qt::IntersectClip);

    // Get the current zoom level
    QPointF zoomLevel;
    converter.zoom(&zoomLevel.rx(), &zoomLevel.ry());

    // Only repaint the pixmap if it is scheduled, the zoom level changed or the shape was resized
    /*if (   d->pixmapRepaintRequested
         || d->lastZoomLevel != zoomLevel
         || d->lastSize      != size()) {
        // TODO: What if two zoom levels are constantly being requested?
        // At the moment, this *is* the case, due to the fact
        // that the shape is also rendered in the page overview
        // in KPresenter
        // Every time the window is hidden and shown again, a repaint is
        // requested --> laggy performance, especially when quickly
        // switching through windows
        d->pixmapRepaintRequested = false;
        d->lastZoomLevel = zoomLevel;
        d->lastSize      = size();

        paintPixmap(painter, converter);
    }*/

    // Paint the background
    if (background()) {
        QPainterPath p;
        p.addRect(paintRect);
        background()->paint(painter, converter, paintContext, p);
    }

    // KDChart thinks in pixels, Calligra in pt
    ScreenConversions::scaleFromPtToPx(painter);

    d->kdLegend->paint(&painter);

    //painter.restore();
    // Paint the cached pixmap
    //painter.drawImage(0, 0, d->image);
}


// ----------------------------------------------------------------
//                     loading and saving


bool Legend::loadOdf(const KoXmlElement &legendElement,
                     KoShapeLoadingContext &context)
{
    KoStyleStack &styleStack = context.odfLoadingContext().styleStack();
    styleStack.clear();
    
    // FIXME: If the style isn't present we shouldn't care about it at all
    // and move everything related to the legend style in this if clause
    if (legendElement.hasAttributeNS(KoXmlNS::chart, "style-name")) {
        context.odfLoadingContext().fillStyleStack(legendElement, KoXmlNS::chart, "style-name", "chart");
        styleStack.setTypeProperties("graphic");
    }

    if (!legendElement.isNull()) {
        int attributesToLoad = OdfAllAttributes;
        QString lp = legendElement.attributeNS(KoXmlNS::chart, "legend-position", QString());
        if (!lp.isEmpty()) {
            attributesToLoad ^= OdfPosition;
        }

        // FIXME according to odf if legend-position is provided the x
        // and y value should not be used.
        //
        // FIXME also width and height are not supported at this place
        if (legendElement.hasAttributeNS(KoXmlNS::svg, "x") ||
            legendElement.hasAttributeNS(KoXmlNS::svg, "y") ||
            legendElement.hasAttributeNS(KoXmlNS::svg, "width") ||
            legendElement.hasAttributeNS(KoXmlNS::svg, "height"))
        {
            d->shape->layout()->setPosition(this, FloatingPosition);
        }

        loadOdfAttributes(legendElement, context, attributesToLoad);

        QString lalign = legendElement.attributeNS(KoXmlNS::chart, "legend-align", QString());

        if (legendElement.hasAttributeNS(KoXmlNS::style, "legend-expansion")) {
            QString lexpansion = legendElement.attributeNS(KoXmlNS::style, "legend-expansion", QString());
            if (lexpansion == "wide")
                setExpansion(WideLegendExpansion);
            else if (lexpansion == "high")
                setExpansion(HighLegendExpansion);
            else
                setExpansion(BalancedLegendExpansion);
        }

        if (lalign == "start") {
            setAlignment(Qt::AlignLeft);
        }
        else if (lalign == "end") {
            setAlignment(Qt::AlignRight);
        }
        else {
            setAlignment(Qt::AlignCenter);
        }

        if (lp == "start") {
            setLegendPosition(StartPosition);
        }
        else if (lp == "top") {
            setLegendPosition(TopPosition);
        }
        else if (lp == "bottom") {
            setLegendPosition(BottomPosition);
        }
        else if (lp == "top-start") {
            setLegendPosition(TopStartPosition);
        }
        else if (lp == "bottom-start") {
            setLegendPosition(BottomStartPosition);
        }
        else if (lp == "top-end") {
            setLegendPosition(TopEndPosition);
        }
        else if (lp == "bottom-end") {
            setLegendPosition(BottomEndPosition);
        }
        else {
            setLegendPosition(EndPosition);
        }

        if (legendElement.hasAttributeNS(KoXmlNS::office, "title")) {
            setTitle(legendElement.attributeNS(KoXmlNS::office, "title", QString()));
        }

        styleStack.setTypeProperties("text");

        if (styleStack.hasProperty(KoXmlNS::fo, "font-family")) {
            QString fontFamily = styleStack.property(KoXmlNS::fo, "font-family");
            QFont font = d->font;
            font.setFamily(fontFamily);
            setFont(font);
        }
        if (styleStack.hasProperty(KoXmlNS::fo, "font-size")) {
            qreal fontSize = KoUnit::parseValue(styleStack.property(KoXmlNS::fo, "font-size"));
            setFontSize(fontSize);
        }
        if (styleStack.hasProperty(KoXmlNS::fo, "font-color")) {
            QColor color = styleStack.property(KoXmlNS::fo, "font-color");
            if (color.isValid()) {
                setFontColor(color);
            }
        }
    }
    else {
        // No legend element, use default legend.
        // FIXME: North??  Isn't that a bit strange as default? /IW
        setLegendPosition(TopPosition);
        setAlignment(Qt::AlignCenter);
    }

    d->pixmapRepaintRequested = true;

    return true;
}

void Legend::saveOdf(KoShapeSavingContext &context) const
{
    KoXmlWriter &bodyWriter = context.xmlWriter();

    bodyWriter.startElement("chart:legend");
    saveOdfAttributes(context, OdfPosition);

    // Legend specific attributes
    QString lp = PositionToString(d->position);
    if (!lp.isEmpty()) {
        bodyWriter.addAttribute("chart:legend-position", lp);
    }
    QString lalign;  // FIXME: This string is always empty.  What gives?
    if (!lalign.isEmpty()) {
        bodyWriter.addAttribute("chart:legend-align", lalign);
    }

    // Legend style FIXME: Check if more styling then just the font goes here.
    KoGenStyle style(KoGenStyle::ChartAutoStyle, "chart", 0);
    saveOdfFont(style, d->font, d->fontColor);
    bodyWriter.addAttribute("chart:style-name", saveStyle(style, context));

    QString  lexpansion;
    switch (expansion()) {
    case WideLegendExpansion:      lexpansion = "wide";      break;
    case HighLegendExpansion:      lexpansion = "high";      break;
    case BalancedLegendExpansion:  lexpansion = "balanced";  break;
    };
    bodyWriter.addAttribute("style:legend-expansion", lexpansion);

    if (!title().isEmpty())
        bodyWriter.addAttribute("office:title", title());

    bodyWriter.endElement(); // chart:legend
}

KDChart::Legend *Legend::kdLegend() const
{
    // There has to be a valid KDChart instance of this legend
    Q_ASSERT(d->kdLegend);
    return d->kdLegend;
}

void Legend::rebuild()
{
    d->kdLegend->forceRebuild();
    update();
}

void Legend::update() const
{
    d->pixmapRepaintRequested = true;
    KoShape::update();
}

void Legend::slotKdLegendChanged()
{
    // FIXME: Update legend properly by implementing all *DataChanged() slots
    // in KDChartModel. Right now, only yDataChanged() is implemented.
    //d->kdLegend->forceRebuild();
    QSize size = d->kdLegend->sizeHint();
    setSize(ScreenConversions::scaleFromPxToPt(size));
    update();
}

void Legend::slotChartTypeChanged(ChartType chartType)
{
    // TODO: Once we support markers, this switch will have to be
    // more clever.
    switch (chartType) {
    case LineChartType:
    case ScatterChartType:
        d->kdLegend->setLegendStyle(KDChart::Legend::MarkersAndLines);
        break;
    default:
        d->kdLegend->setLegendStyle(KDChart::Legend::MarkersOnly);
        break;
    }
}
