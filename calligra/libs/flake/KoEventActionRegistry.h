/* This file is part of the KDE project
   Copyright (C) 2008 Thorsten Zachmann <zachmann@kde.org>

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
 * Boston, MA 02110-1301, USA.
*/

#ifndef KOEVENTACTIONREGISTRY_H
#define KOEVENTACTIONREGISTRY_H

#include <QList>
#include <QSet>

#include "flake_export.h"
#include "KoXmlReaderForward.h"
class KoEventAction;
class KoEventActionFactoryBase;
class KoShapeLoadingContext;

/**
 * This singletion keeps a register of all available KoEventActionFactoryBase objects.
 *
 * It creates the event actions when loaded from odf.
 */
class FLAKE_EXPORT KoEventActionRegistry
{
public:
    class Singleton;

    ~KoEventActionRegistry();

    /**
     * Return an instance of the KoEventActionRegistry
     */
    static KoEventActionRegistry *instance();

    /**
     * Create action events for the elements given
     */
    QSet<KoEventAction*> createEventActionsFromOdf(const KoXmlElement &element, KoShapeLoadingContext &context) const;

    /**
     * Add presentation event action.
     */
    void addPresentationEventAction(KoEventActionFactoryBase *factory);

    /**
     * Add script event action.
     */
    void addScriptEventAction(KoEventActionFactoryBase *factory);

    /**
     * Get presentation event actions.
     */
    QList<KoEventActionFactoryBase *> presentationEventActions();

    /**
     * Get script event actions.
     */
    QList<KoEventActionFactoryBase *> scriptEventActions();

private:
    KoEventActionRegistry();
    KoEventActionRegistry(const KoEventActionRegistry &);
    KoEventActionRegistry operator=(const KoEventActionRegistry &);

    void init();

    class Private;
    Private *d;
};

#endif /* KOEVENTACTIONREGISTRY_H */
