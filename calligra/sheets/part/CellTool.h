/* This file is part of the KDE project
   Copyright 2007 Stefan Nikolaus <stefan.nikolaus@kdemail.net>

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

#ifndef CALLIGRA_SHEETS_CELL_TOOL
#define CALLIGRA_SHEETS_CELL_TOOL

#include <sheets/ui/CellToolBase.h>

#include <sheets/calligra_sheets_export.h>

namespace Calligra
{
namespace Sheets
{

/**
 * The tool to change cell ranges.
 */
class CALLIGRA_SHEETS_COMMON_EXPORT CellTool : public CellToolBase
{
    Q_OBJECT

public:
    explicit CellTool(KoCanvasBase* canvas);
    ~CellTool();

    virtual void paint(QPainter &painter, const KoViewConverter &converter);

public Q_SLOTS:
    virtual void activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes);

protected:
    virtual Selection* selection();
    virtual QPointF offset() const;
    virtual QSizeF size() const;
    virtual QPointF canvasOffset() const;
    virtual int maxCol() const;
    virtual int maxRow() const;
    virtual SheetView* sheetView(const Sheet* sheet) const;

protected Q_SLOTS:
    // -- misc actions --
    void definePrintRange();

private:
    Q_DISABLE_COPY(CellTool)

    class Private;
    Private * const d;
};

} // namespace Sheets
} // namespace Calligra

#endif // CALLIGRA_SHEETS_CELL_TOOL
