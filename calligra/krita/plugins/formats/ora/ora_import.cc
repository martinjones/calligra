/*
 *  Copyright (c) 2007 Cyrille Berger <cberger@cberger.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "ora_import.h"

#include <kpluginfactory.h>

#include <KoFilterChain.h>

#include <kis_doc2.h>
#include <kis_image.h>

#include "ora_converter.h"

K_PLUGIN_FACTORY_WITH_JSON(ImportFactory, "krita_ora_import.json", registerPlugin<OraImport>();)
//K_EXPORT_PLUGIN(ImportFactory("calligrafilters"))

OraImport::OraImport(QObject *parent, const QVariantList &) : KoFilter(parent)
{
}

OraImport::~OraImport()
{
}

KoFilter::ConversionStatus OraImport::convert(const QByteArray&, const QByteArray& to)
{
    dbgFile << "Importing using ORAImport!";

    if (to != "application/x-krita")
        return KoFilter::BadMimeType;

    KisDoc2 * doc = dynamic_cast<KisDoc2*>(m_chain->outputDocument());

    if (!doc)
        return KoFilter::NoDocumentCreated;

    QString filename = m_chain -> inputFile();

    doc->prepareForImport();

    if (!filename.isEmpty()) {

        KUrl url(filename);

        if (url.isEmpty())
            return KoFilter::FileNotFound;

        OraConverter ib(doc);


        switch (ib.buildImage(url)) {
        case KisImageBuilder_RESULT_UNSUPPORTED:
            return KoFilter::NotImplemented;
            break;
        case KisImageBuilder_RESULT_INVALID_ARG:
            return KoFilter::BadMimeType;
            break;
        case KisImageBuilder_RESULT_NO_URI:
        case KisImageBuilder_RESULT_NOT_LOCAL:
            return KoFilter::FileNotFound;
            break;
        case KisImageBuilder_RESULT_BAD_FETCH:
        case KisImageBuilder_RESULT_EMPTY:
            return KoFilter::ParsingError;
            break;
        case KisImageBuilder_RESULT_FAILURE:
            return KoFilter::InternalError;
            break;
        case KisImageBuilder_RESULT_OK:
            doc->setCurrentImage(ib.image());
            if (ib.activeNodes().size() > 0) {
                doc->setPreActivatedNode(ib.activeNodes()[0]);
            }
            return KoFilter::OK;
        default:
            break;
        }

    }
    return KoFilter::StorageCreationError;
}

#include <ora_import.moc>

