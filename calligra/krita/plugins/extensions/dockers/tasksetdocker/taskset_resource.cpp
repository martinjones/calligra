/*
 *  Copyright (c) 2011 Sven Langkamp <sven.langkamp@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "taskset_resource.h"

#include <QFile>
#include <QDomDocument>
#include <QTextStream>

#define TASKSET_VERSION 1

TasksetResource::TasksetResource(const QString& filename): KoResource(filename)
{
}

TasksetResource::~TasksetResource()
{
}

bool TasksetResource::save()
{
    if (filename().isEmpty())
         return false;

    QFile file(filename());
    file.open(QIODevice::WriteOnly);
 
    QDomDocument doc;
    QDomElement root = doc.createElement("Taskset");
    root.setAttribute("name", name() );
    root.setAttribute("version", TASKSET_VERSION);
    foreach(const QString& action, m_actions) {
        QDomElement element = doc.createElement("action");
        element.appendChild(doc.createTextNode(action));
        root.appendChild(element);
    }
    doc.appendChild(root);
     
    QTextStream textStream(&file);
    doc.save(textStream, 4);
    file.close();
    return true;
}

bool TasksetResource::load()
{    if (filename().isEmpty())
         return false;
 
    QFile file(filename());

    QDomDocument doc;
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!doc.setContent(&file)) {
        file.close();
        return false;
    }
    file.close();

    QDomElement element = doc.documentElement();
    setName(element.attribute("name"));
     
    QDomNode node = element.firstChild();   
    while (!node.isNull()) {
        QDomElement child = node.toElement();
        if (!child.isNull() && child.tagName() == "action") {
                m_actions.append(child.text());
        }
        node = node.nextSibling();
    }
    setValid(true);
    return true;
}

QImage TasksetResource::image() const
{
    return KoResource::image();
}

QString TasksetResource::defaultFileExtension() const
{
    return QString(".kts");
}

void TasksetResource::setActionList(const QStringList actions)
{
    m_actions = actions;
}

QStringList TasksetResource::actionList()
{
    return m_actions;
}


