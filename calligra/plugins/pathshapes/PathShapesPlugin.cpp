/* This file is part of the KDE project
 * Copyright (C) 2006 Thomas Zander <zander@kde.org>
 * Copyright (C) 2006 Thorsten Zachmann <zachmann@kde.org>
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
#include <KoShapeRegistry.h>
#include <KoShapeFactoryBase.h>

#include "PathShapesPlugin.h"
#include "star/StarShapeFactory.h"
#include "rectangle/RectangleShapeFactory.h"
#include "ellipse/EllipseShapeFactory.h"
#include "spiral/SpiralShapeFactory.h"
#include "enhancedpath/EnhancedPathShapeFactory.h"
#include <kpluginfactory.h>

K_PLUGIN_FACTORY_WITH_JSON(PathShapesPluginFactory, "calligra_shape_paths.json", registerPlugin<PathShapesPlugin>();)
//K_EXPORT_PLUGIN(PathShapesPluginFactory("PathShapes"))

PathShapesPlugin::PathShapesPlugin(QObject *parent, const QVariantList&)
    : QObject(parent)
{
    KoShapeRegistry::instance()->add(new StarShapeFactory());
    KoShapeRegistry::instance()->add(new RectangleShapeFactory());
    KoShapeRegistry::instance()->add(new SpiralShapeFactory());
    KoShapeRegistry::instance()->add(new EnhancedPathShapeFactory());
    KoShapeRegistry::instance()->add(new EllipseShapeFactory());

}

#include <PathShapesPlugin.moc>
