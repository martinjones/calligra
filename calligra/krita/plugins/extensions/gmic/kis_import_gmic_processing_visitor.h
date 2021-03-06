/*
 *  Copyright (c) 2013 Dmitry Kazakov <dimula73@gmail.com>
 *  Copyright (c) 2013 Lukáš Tvrdý <lukast.dev@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef __KIS_IMPORT_GMIC_PROCESSING_VISITOR_H
#define __KIS_IMPORT_GMIC_PROCESSING_VISITOR_H

#include <processing/kis_simple_processing_visitor.h>
#include <QList>

#include <QSharedPointer>

#include <gmic.h>

#include <kis_node.h>
class KisUndoAdapter;

class KisImportGmicProcessingVisitor : public KisSimpleProcessingVisitor
{
public:
    KisImportGmicProcessingVisitor(const QList<KisNodeSP> &nodes,
                                   QSharedPointer<gmic_list<float> > images);

protected:
    void visitNodeWithPaintDevice(KisNode *node, KisUndoAdapter *undoAdapter);
    void visitExternalLayer(KisExternalLayer *layer, KisUndoAdapter *undoAdapter);

private:
    QList<KisNodeSP> m_nodes;
    QSharedPointer<gmic_list<float> > m_images;
};

#endif /* __KIS_IMPORT_GMIC_PROCESSING_VISITOR_H */
