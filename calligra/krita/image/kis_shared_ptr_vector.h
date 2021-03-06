/*
 *  Copyright (c) 2004 Adrian Page <adrian@pagenet.plus.com>
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

#ifndef KIS_SHARED_PTR_VECTOR_H
#define KIS_SHARED_PTR_VECTOR_H

#include <QVector>

#include <kis_shared_ptr.h>

/**
 * QValueVector does not always destroy an element when it is erased.
 * If the items it is holding are KisSharedPtr, this can result in hidden
 * references to objects that cannot be accounted for. This class
 * sets the KisSharedPtr to 0 on erase, which dereferences the object as
 * expected.
 */
template <class T>
class KisSharedPtrVector : public QVector< KisSharedPtr<T> >
{

    typedef QVector< KisSharedPtr<T> > SharedPtrVector;

public:
    KisSharedPtrVector() {}

    void pop_back() {
        if (!SharedPtrVector::empty()) {
            SharedPtrVector::back() = 0;
            SharedPtrVector::pop_back();
        }
    }

    typename SharedPtrVector::iterator erase(typename SharedPtrVector::iterator it) {
        *it = 0;
        return SharedPtrVector::erase(it);
    }

    typename SharedPtrVector::iterator erase(typename SharedPtrVector::iterator first, typename SharedPtrVector::iterator last) {
        qFill(first, last, 0);
        return SharedPtrVector::erase(first, last);
    }

    bool contains(KisSharedPtr<T> ptr) const {
        for (int i = 0, n = SharedPtrVector::count(); i < n; ++i)
            if (SharedPtrVector::at(i) == ptr)
                return true;
        return false;
    }
};

#endif // KIS_SHARED_PTR_VECTOR_H

