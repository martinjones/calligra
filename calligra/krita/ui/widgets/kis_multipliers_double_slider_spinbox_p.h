/* This file is part of the KDE project
 * Copyright (c) 2010 Cyrille Berger <cberger@cberger.net>
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
#ifndef kis_multipliers_double_slider_spinbox_p_h
#define kis_multipliers_double_slider_spinbox_p_h

#include "kis_multipliers_double_slider_spinbox.h"

#include "ui_wdgmultipliersdoublesliderspinbox.h"

#include "kis_debug.h"

struct KisMultipliersDoubleSliderSpinBox::Private {
    qreal currentMultiplier();
    /// Update the range of the slider depending on the currentMultiplier
    void updateRange();
    
    Ui::WdgMultipliersDoubleSliderSpinBox form;
    qreal min, max;
    int decimals;
};

#endif
