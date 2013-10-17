/*
 * This file is part of the KDE project
 * Copyright (C) 2013 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "CalligraComponentsPlugin.h"

#include <QtQml/QtQml>

#include "Document.h"
#include "View.h"
#include "Global.h"
#include "ViewController.h"
#include "Enums.h"

#include "models/ContentsModel.h"
#include "models/ThumbnailModel.h"

using namespace Calligra::Components;

QObject* singletonFactory(QQmlEngine*, QJSEngine*)
{
    return new Calligra::Components::Global{};
}

void CalligraComponentsPlugin::registerTypes(const char* uri)
{
    Q_ASSERT(uri == QLatin1Literal{"org.kde.calligra"});

    qmlRegisterType<Calligra::Components::Document>(uri, 1, 0, "Document");
    qmlRegisterType<Calligra::Components::View>(uri, 1, 0, "View");
    qmlRegisterType<Calligra::Components::ViewController>(uri, 1, 0, "ViewController");

    qmlRegisterType<Calligra::Components::ContentsModel>(uri, 1, 0, "ContentsModel");
    qmlRegisterType<Calligra::Components::ThumbnailModel>(uri, 1, 0, "ThumbnailModel");

    qmlRegisterUncreatableType<Calligra::Components::DocumentType>(uri, 1, 0, "DocumentType", "Provides the DocumentType enum");
    qmlRegisterUncreatableType<Calligra::Components::DocumentStatus>(uri, 1, 0, "DocumentStatus", "Provides the DocumentStatus enum");

    qmlRegisterSingletonType<Calligra::Components::Global>(uri, 1, 0, "Global", &singletonFactory);
}
