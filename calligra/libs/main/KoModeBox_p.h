/*
 * Copyright (c) 2005 Boudewijn Rempt <boud@valdyas.org>
 * Copyright (c) 2005-2008 Thomas Zander <zander@kde.org>
 * Copyright (c) 2009 Peter Simonsson <peter.simonsson@gmail.com>
 * Copyright (c) 2010 Cyrille Berger <cberger@cberger.net>
 * Copyright (c) 2011 C. Boemann <cbo@boemann.dk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#ifndef KO_MODEBOX_H
#define KO_MODEBOX_H

#include <KoCanvasObserverBase.h>

#include <QList>
#include <QMap>
#include <QHash>
#include <QDockWidget>

#include <KoToolManager.h>

class QToolButton;
class KoCanvasControllerWidget;
class KoCanvasController;
class KoCanvasBase;
class KoShapeLayer;

/**
 * KoModeBox is housed in a dock widget that presents tools as headings in a QToolBox
 * according to type and priority.
 *
 * The ModeBox is a container for tool buttons which are themselves
 * divided into sections.
 *
 * Adding buttons using addButton() will allow you to show those buttons.  You should connect
 * the button to your handling method yourself.
 *
 * @see KoToolManager
 */
class KoModeBox : public QWidget {
    Q_OBJECT
public:
    /// constructor
    explicit KoModeBox(KoCanvasControllerWidget *canvas, const QString &applicationName);
    ~KoModeBox();

    /**
     * Add a button to the modebox.
     * The buttons should all be added before the first showing since adding will not really add
     * them to the UI until setup() is called.
     *
     * @param button the new button.  Please make sure you connect to the button yourself.
     * @param section the section in which this button will be shown.  Each section will be its own
     *        widget.
     * @param priority the priority in the section. Lowest value means it will be shown first.
     * @param buttonGroupId if passed this will allow you to use setActiveTool() to trigger
     *      this button
     * @see setup()
     */
    void addButton(const KoToolButton &button);

    /**
     * Should been called when the docker position has changed.
     * Organise widgets and icons and orientation of the tabs.
     *
     * @param area the new location area
     */
    void locationChanged(Qt::DockWidgetArea area);
public slots:
    /**
     * Using the buttongroup id passed in addButton() you can set the new active tool.
     * If the id does not resolve to a visible heading, this call is ignored.
     * @param canvas the currently active canvas.
     * @param id an id to identify the tool/heading to activate.
     */
    void setActiveTool(KoCanvasController *canvas, int id);

    /**
     * Show only the dynamic buttons that have a code from parameter codes.
     * The modebox allows buttons to be optionally registered with a visibilityCode. This code
     * can be passed here and all buttons that have that code are shown. All buttons that
     * have another visibility code registered are hidden.
     * @param canvas the currently active canvas.
     * @param codes a list of all the codes to show.
     */
    void updateShownTools(const KoCanvasController *canvas, const QList<QString> &codes);

    void setOptionWidgets(const QList<QWidget *> &optionWidgetList);

    /// set the canvas this docker should listen to for changes.
    void setCanvas(KoCanvasBase *canvas);
    void unsetCanvas();

private slots:
    void setCurrentLayer(const KoCanvasController *canvas, const KoShapeLayer* newLayer);

    /// add a tool post-initialization. The tool will also be activated.
    void toolAdded(const KoToolButton &button, KoCanvasController *canvas);

    /// slot for when a new item have been selected in the QToolBox
    void toolSelected(int index);

    /// slot for context menu of the tabbar
    void slotContextMenuRequested(const QPoint &pos);

    /// switch icon mode
    void switchIconMode(int);

    /// switch tabs side
    void switchTabsSide(int);

public:
    static QString applicationName;

private:
    enum IconMode {
        IconAndText,
        IconOnly
    };

    enum VerticalTabsSide {
        TopSide,
        BottomSide
    };

    enum HorizontalTabsSide {
        LeftSide,
        RightSide
    };

    QIcon createTextIcon(const KoToolButton button);
    QIcon createSimpleIcon(const KoToolButton button);
    void addItem(const KoToolButton button);

private:
    class Private;
    Private * const d;
};

#endif // _KO_TOOLBOX_H_
