/*
 *  Copyright (c) 2009 Dmitry Kazakov <dimula73@gmail.com>
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
#ifndef KIS_TILE_DATA_H_
#define KIS_TILE_DATA_H_

/**
 * Some methods of KisTileData have a cyclic dependency
 * to the KisTileDataStore, so we've moved the class
 * declaration to a separate file, that will be included
 * by the store.
 */
#include "kis_tile_data_interface.h"


#include "kis_tile_data_store.h"


inline quint8* KisTileData::data() const {
        // WARN: be careful - it can be null when swapped out!
        return m_data;
    }

void KisTileData::setData(const quint8 *data) {
    Q_ASSERT(m_data);
    memcpy(m_data, data, m_pixelSize*WIDTH*HEIGHT);
}

inline quint32 KisTileData::pixelSize() const {
    return m_pixelSize;
}

inline bool KisTileData::acquire() {
    /**
     * We need to ensure the clones in the stack are
     * consistent with the data. When we have a single
     * user, the most probably, the clone has already
     * started stinking.
     * So just clean it up.
     */
    if(m_usersCount.load() == 1) {
        KisTileData *clone = 0;
        while(m_clonesStack.pop(clone)) {
            delete clone;
        }
    }

    bool _ref = ref();
    m_usersCount.ref();
    return _ref;
}

inline bool KisTileData::release() {
    m_usersCount.deref();
    bool _ref = deref();
    return _ref;
}

inline bool KisTileData::ref() const {
    return m_refCount.ref();
}

inline bool KisTileData::deref() {
    bool _ref;

    if (!(_ref = m_refCount.deref())) {
        m_store->freeTileData(this);
        return 0;
    }
    return _ref;
}

inline KisTileData* KisTileData::clone() {
    return m_store->duplicateTileData(this);
}

inline void KisTileData::blockSwapping() {
    m_swapLock.lockForRead();
    if(!m_data) {
        m_swapLock.unlock();
        m_store->ensureTileDataLoaded(this);
    }
    resetAge();
}

inline void KisTileData::unblockSwapping() {
    m_swapLock.unlock();
}

inline KisChunk KisTileData::swapChunk() const {
    return m_swapChunk;
}
inline void KisTileData::setSwapChunk(KisChunk chunk) {
    m_swapChunk = chunk;
}

inline bool KisTileData::mementoed() const {
    return m_mementoFlag;
}
inline void KisTileData::setMementoed(bool value) {
    m_mementoFlag += value ? 1 : -1;
}

inline int KisTileData::age() const {
    return m_age;
}
inline void KisTileData::resetAge() {
    m_age = 0;
}
inline void KisTileData::markOld() {
    m_age++;
}

inline qint32 KisTileData::numUsers() const {
    return m_usersCount.load();
}

#endif /* KIS_TILE_DATA_H_ */

