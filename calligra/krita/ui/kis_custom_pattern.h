/*
 *  Copyright (c) 2006 Bart Coppens <kde@bartcoppens.be>
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

#ifndef KIS_CUSTOM_PATTERN_H_
#define KIS_CUSTOM_PATTERN_H_

#include <QObject>
#include <QShowEvent>

#include <KoResourceServerAdapter.h>

#include "ui_wdgcustompattern.h"

class KisPattern;
class KoResource;
class KisView2;

class KisWdgCustomPattern : public QWidget, public Ui::KisWdgCustomPattern
{
    Q_OBJECT

public:
    KisWdgCustomPattern(QWidget *parent, const char *name) : QWidget(parent) {
        setObjectName(name); setupUi(this);
    }
};

class KisCustomPattern : public KisWdgCustomPattern
{
    Q_OBJECT
public:
    KisCustomPattern(QWidget *parent, const char* name, const QString& caption, KisView2* view);
    virtual ~KisCustomPattern();

signals:
    void activatedResource(KoResource *);
    void addPattern(KisPattern*);

private slots:
    void slotAddPredefined();
    void slotUsePattern();
    void slotUpdateCurrentPattern();

private:
    void createPattern();
    KisView2* m_view;
    KisPattern* m_pattern;
    KoResourceServerAdapter<KisPattern>* m_rServerAdapter;
};


#endif // KIS_CUSTOM_PATTERN_H_
