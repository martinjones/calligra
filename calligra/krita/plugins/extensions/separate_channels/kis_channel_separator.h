/*
 * This file is part of the KDE project
 *
 * Copyright (c) Michael Thaler <michael.thaler@physik.tu-muenchen.de>
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

#ifndef _KIS_CHANNEL_SEPARATOR_H_
#define _KIS_CHANNEL_SEPARATOR_H_

class KoUpdater;
class KisView2;

enum enumSepAlphaOptions {
    COPY_ALPHA_TO_SEPARATIONS = 0,
    DISCARD_ALPHA = 1,
    CREATE_ALPHA_SEPARATION = 2
};


enum enumSepSource {
    CURRENT_LAYER = 0,
    ALL_LAYERS = 1,
    VISIBLE_LAYERS = 2
};

enum enumSepOutput {
    TO_LAYERS = 0,
    TO_IMAGES = 1
};

class KisChannelSeparator
{

public:

    KisChannelSeparator(KisView2 * view);
    virtual ~KisChannelSeparator() {}

    void separate(KoUpdater * progress, enumSepAlphaOptions alphaOps, enumSepSource sourceOps, enumSepOutput outputOps, bool downscale, bool toColor);

private:

    KisView2 * m_view;

};

#endif
