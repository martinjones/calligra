/*
 *  Copyright (c) 2011 Dmitry Kazakov <dimula73@gmail.com>
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

#ifndef __KIS_SIMPLE_STROKE_STRATEGY_TEST_H
#define __KIS_SIMPLE_STROKE_STRATEGY_TEST_H

#include <QtTest/QtTest>

class KisSimpleStrokeStrategyTest : public QObject
{
    Q_OBJECT

private slots:
    void testFinish();
    void testCancel();
};

#endif /* __KIS_SIMPLE_STROKE_STRATEGY_TEST_H */
