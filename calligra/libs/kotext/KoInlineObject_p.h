/* This file is part of the KDE project
 * Copyright (C) 2006-2009 Thomas Zander <zander@kde.org>
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

#ifndef KOINLINEOBJECT_P_H
#define KOINLINEOBJECT_P_H

#include <QDebug>
class KoTextInlineRdf;

class KoInlineObjectPrivate
{
public:
    KoInlineObjectPrivate()
            : manager(0),
            id(-1),
            propertyChangeListener(0),
            rdf(0) {
    }
    virtual ~KoInlineObjectPrivate();

    KoInlineTextObjectManager *manager;
    int id;
    bool propertyChangeListener;
    KoTextInlineRdf *rdf; //< An inline object might have RDF, we own it.

    virtual QDebug printDebug(QDebug dbg) const;
};

#endif
