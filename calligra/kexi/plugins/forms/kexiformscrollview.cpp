/* This file is part of the KDE project
   Copyright (C) 2004 Cedric Pasteur <cedric.pasteur@free.fr>
   Copyright (C) 2004-2012 Jarosław Staniek <staniek@kde.org>

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

#include "kexiformscrollview.h"
//#include "kexiformview.h"

#include <formeditor/form.h>
//2.0 #include <formeditor/formmanager.h>
#include <formeditor/objecttree.h>
#include <formeditor/commands.h>
#include <widget/utils/kexirecordmarker.h>
#include <kexi_global.h>

#include <QMenu>
#include <kdebug.h>

class KexiFormScrollView::Private
{
public:
    Private()
      : currentLocalSortColumn(-1) /* no column */
      , localSortingOrder(-1) /* no sorting */
      , previousRecord(0)
    {
    }
    KFormDesigner::Form *form;
    int currentLocalSortColumn, localSortingOrder;
    //! Used in selectCellInternal() to avoid fetching the same record twice
    KexiDB::RecordData *previousRecord;
};

KexiFormScrollView::KexiFormScrollView(QWidget *parent, bool preview)
        : KexiScrollView(parent, preview)
        , KexiRecordNavigatorHandler()
        , KexiSharedActionClient()
        , KexiDataAwareObjectInterface()
        , KexiFormDataProvider()
        , KexiFormEventHandler()
        , d(new Private)
{
    m_navPanel = recordNavigator(); //copy this pointer from KexiScrollView
    if (preview) {
        setRecordNavigatorVisible(true);
//tmp
//  recordNavigator()->setEditingIndicatorEnabled(true);
//  recordNavigator()->showEditingIndicator(true);
    }

    connect(this, SIGNAL(resizingStarted()), this, SLOT(slotResizingStarted()));

    m_contextMenu = new QMenu(this);
    m_contextMenu->setObjectName("m_contextMenu");

// setFocusPolicy(NoFocus);
}

KexiFormScrollView::~KexiFormScrollView()
{
    if (m_owner)
        delete m_data;
    m_data = 0;
    delete d;
}

void
KexiFormScrollView::show()
{
    KexiScrollView::show();

#if 0 //moved to KexiFormView, OK?
    //now get resize mode settings for entire form
    if (isPreviewing()) {
        KexiFormView* fv = dynamic_cast<KexiFormView*>(parent());
        int resizeMode = fv ? fv->resizeMode() : KexiFormView::ResizeAuto;
        if (resizeMode == KexiFormView::ResizeAuto)
            setResizePolicy(AutoOneFit);
    }
#endif
}

void
KexiFormScrollView::slotResizingStarted()
{
    if (d->form)
        setSnapToGrid(d->form->isSnapWidgetsToGridEnabled(), d->form->gridSize());
    else
        setSnapToGrid(false);
}

int KexiFormScrollView::rowsPerPage() const
{
    //! @todo
    return 10;
}

void KexiFormScrollView::selectCellInternal()
{
    //m_currentItem is already set by KexiDataAwareObjectInterface::setCursorPosition()
    if (m_currentItem) {
        if (m_currentItem != d->previousRecord) {
            fillDataItems(*m_currentItem, cursorAtNewRow());
            d->previousRecord = m_currentItem;
            QWidget *w = 0;
            if (m_curCol >= 0 && m_curCol < dbFormWidget()->orderedDataAwareWidgets()->count()) {
                w = dbFormWidget()->orderedDataAwareWidgets()->at(m_curCol);
            }
            if (w) {
                w->setFocus(); // re-focus, as we could have lost focus, e.g. when navigator button was clicked
                // select all
                KexiFormDataItemInterface *iface = dynamic_cast<KexiFormDataItemInterface*>(w);
//! @todo add option for not selecting the field
                if (iface) {
                    iface->selectAllOnFocusIfNeeded();
                }
            }
        }
    } else {
        d->previousRecord = 0;
    }
}

void KexiFormScrollView::ensureCellVisible(int row, int col/*=-1*/)
{
    Q_UNUSED(row);
    Q_UNUSED(col);
    //! @todo
// if (m_currentItem)
    //fillDataItems(*m_currentItem);

// if (d->form->tabStops()->first() && d->form->tabStops()->first()->widget())
//  d->form->tabStops()->first()->widget()->setFocus();
}

void KexiFormScrollView::moveToRecordRequested(uint r)
{
    //! @todo
    selectRow(r);
}

void KexiFormScrollView::moveToLastRecordRequested()
{
    //! @todo
    selectLastRow();
}

void KexiFormScrollView::moveToPreviousRecordRequested()
{
    //! @todo
    selectPrevRow();
}

void KexiFormScrollView::moveToNextRecordRequested()
{
    //! @todo
    selectNextRow();
}

void KexiFormScrollView::moveToFirstRecordRequested()
{
    //! @todo
    selectFirstRow();
}

void KexiFormScrollView::clearColumnsInternal(bool repaint)
{
    Q_UNUSED(repaint);
    //! @todo
}

void KexiFormScrollView::addHeaderColumn(const QString& caption, const QString& description,
        const QIcon& icon, int width)
{
    Q_UNUSED(caption);
    Q_UNUSED(description);
    Q_UNUSED(icon);
    Q_UNUSED(width);

    //! @todo
}

int KexiFormScrollView::currentLocalSortingOrder() const
{
    //! @todo
    return d->localSortingOrder;
}

int KexiFormScrollView::currentLocalSortColumn() const
{
    return d->currentLocalSortColumn;
}

void KexiFormScrollView::setLocalSortingOrder(int col, int order)
{
    //! @todo
    d->currentLocalSortColumn = col;
    d->localSortingOrder = order;
}

void KexiFormScrollView::sortColumnInternal(int col, int order)
{
    Q_UNUSED(col);
    Q_UNUSED(order);
    //! @todo
}

void KexiFormScrollView::updateGUIAfterSorting()
{
    //! @todo
}

void KexiFormScrollView::createEditor(int row, int col, const QString& addText,
                                      bool removeOld)
{
    Q_UNUSED(row);
    Q_UNUSED(addText);
    Q_UNUSED(removeOld);

    if (isReadOnly()) {
        kWarning() << "DATA IS READ ONLY!";
        return;
    }
    if (column(col)->isReadOnly()) {
        kWarning() << "COL IS READ ONLY!";
        return;
    }

    //! @todo
    const bool startRowEdit = !rowEditing(); //remember if we're starting record edit

    if (!rowEditing()) {
        //we're starting record editing session
        m_data->clearRowEditBuffer();

        setRowEditing(true);
        //indicate on the vheader that we are editing:
        if (m_verticalHeader)
            m_verticalHeader->setEditRow(m_curRow);
        if (isInsertingEnabled() && m_currentItem == m_insertItem) {
            //we should know that we are in state "new record editing"
            m_newRowEditing = true;
            //'insert' record editing: show another row after that:
            m_data->append(m_insertItem);
            //new empty insert item
            m_insertItem = m_data->createItem();
//   updateContents();
            if (m_verticalHeader)
                m_verticalHeader->addLabel();
//   m_verticalHeaderAlreadyAdded = true;
            updateWidgetContentsSize();
            //refr. current and next row
//   updateContents(columnPos(0), rowPos(row), viewport()->width(), m_rowHeight*2);
//js: warning this breaks behaviour (cursor is skipping, etc.): qApp->processEvents(500);
//   ensureVisible(columnPos(m_curCol), rowPos(row+1)+m_rowHeight-1, columnWidth(m_curCol), m_rowHeight);

//   m_verticalHeader->setOffset(contentsY());
        }
    }

    m_editor = editor(col); //m_dataItems.at(col);
    if (!m_editor)
        return;

    if (startRowEdit) {
        recordNavigator()->showEditingIndicator(true);
//  recordNavigator()->updateButtons(); //refresh 'next btn'

        emit rowEditStarted(m_curRow);
    }
}

KexiDataItemInterface *KexiFormScrollView::editor(int col, bool ignoreMissingEditor)
{
    Q_UNUSED(ignoreMissingEditor);

    if (!m_data || col < 0 || col >= columns())
        return 0;

    return dynamic_cast<KexiFormDataItemInterface*>(dbFormWidget()->orderedDataAwareWidgets()->at(col));
// KexiFormDataItemInterface *item = m_dataItems.at(col);
    //return item;

    /*
      KexiDB::TableViewColumn *tvcol = m_data->column(col);
    // int t = tvcol->fielm_type();

      //find the editor for this column
      KexiDataItemInterface *editor = m_editors[ tvcol ];
      if (editor)
        return editor;

      //not found: create
    // editor = KexiCellEditorFactory::createEditor(*m_data->column(col)->field, this);
      editor = KexiCellEditorFactory::createEditor(*m_data->column(col), this);
      if (!editor) {//create error!
        if (!ignoreMissingEditor) {
          //js TODO: show error???
          cancelRowEdit();
        }
        return 0;
      }
      editor->hide();
      connect(editor,SIGNAL(editRequested()),this,SLOT(slotEditRequested()));
      connect(editor,SIGNAL(cancelRequested()),this,SLOT(cancelEditor()));
      connect(editor,SIGNAL(acceptRequested()),this,SLOT(acceptEditor()));

      editor->resize(columnWidth(col)-1, rowHeight()-1);
      editor->installEventFilter(this);
      if (editor->widget())
        editor->widget()->installEventFilter(this);
      //store
      m_editors.insert( tvcol, editor );
      return editor;*/
}

void KexiFormScrollView::editorShowFocus(int row, int col)
{
    Q_UNUSED(row);
    Q_UNUSED(col);
    //! @todo
// if (m_currentItem)
//  m_provider->fillDataItems(*m_currentItem);
}

void KexiFormScrollView::updateCell(int row, int col)
{
    Q_UNUSED(row);
    Q_UNUSED(col);
    //! @todo
}

void KexiFormScrollView::updateCurrentCell()
{
}

void KexiFormScrollView::updateRow(int row)
{
    Q_UNUSED(row)
    //! @todo
}

void KexiFormScrollView::updateWidgetContents()
{
    //! @todo
}

void KexiFormScrollView::updateWidgetContentsSize()
{
    //! @todo
}

void KexiFormScrollView::updateWidgetScrollBars()
{
    //! @todo
}

void KexiFormScrollView::slotRowRepaintRequested(KexiDB::RecordData& record)
{
    Q_UNUSED(record);
    //! @todo
}

/*void KexiFormScrollView::slotAboutToDeleteRow(KexiTableItem& item,
  KexiDB::ResultInfo* result, bool repaint)
{
  //! @todo
}*/

/*void KexiFormScrollView::slotRowDeleted()
{
  //! @todo
}*/

void KexiFormScrollView::slotRowInserted(KexiDB::RecordData* record, bool repaint)
{
    Q_UNUSED(record);
    Q_UNUSED(repaint);
    //! @todo
}

void KexiFormScrollView::slotRowInserted(KexiDB::RecordData* record, uint row, bool repaint)
{
    Q_UNUSED(record);
    Q_UNUSED(row);
    Q_UNUSED(repaint);
    //! @todo
}

void KexiFormScrollView::slotRowsDeleted(const QList<int> &)
{
    //! @todo
}

KexiDBForm* KexiFormScrollView::dbFormWidget() const
{
    return dynamic_cast<KexiDBForm*>(widget());
}

int KexiFormScrollView::columns() const
{
    return dbFormWidget()->orderedDataAwareWidgets()->count(); //m_dataItems.count();
}

/*uint KexiFormScrollView::fieldNumberForColumn(int col)
{
  KexiFormDataItemInterface *item = dynamic_cast<KexiFormDataItemInterface*>(dbFormWidget()->orderedDataAwareWidgets()->at( col ));
  if (!item)
    return -1;
  KexiFormDataItemInterfaceToIntMap::ConstIterator it(m_fieldNumbersForDataItems.find( item ));
  return it!=m_fieldNumbersForDataItems.constEnd() ? it.data() : -1;
}*/


void KexiFormScrollView::setForm(KFormDesigner::Form *form)
{
    d->form = form;
}



bool KexiFormScrollView::columnEditable(int col)
{
    kDebug() << "col=" << col;
    foreach(KexiFormDataItemInterface *dataItemIface, m_dataItems) {
        kDebug() << (dynamic_cast<QWidget*>(dataItemIface)
                     ? dynamic_cast<QWidget*>(dataItemIface)->objectName() : "")
            << " " << dataItemIface->dataSource();
    }
    kDebug() << "-- focus widgets --";
    foreach(QWidget* widget, *dbFormWidget()->orderedFocusWidgets()) {
        kDebug() << widget->objectName();
    }
    kDebug() << "-- data-aware widgets --";
    foreach(QWidget *widget, *dbFormWidget()->orderedDataAwareWidgets()) {
        kDebug() << widget->objectName();
    }

    //int index = dbFormWidget()->indexForDataItem( item );
// KexiFormDataItemInterface *item1 = dynamic_cast<KexiFormDataItemInterface*>(dbFormWidget()->orderedFocusWidgets()->at( col ));
    KexiFormDataItemInterface *item
    = dynamic_cast<KexiFormDataItemInterface*>(dbFormWidget()->orderedDataAwareWidgets()->at(col));

    if (!item || item->isReadOnly())
        return false;

// KexiFormDataItemInterfaceToIntMap::ConstIterator it(m_fieldNumbersForDataItems.find( item ));
// return KexiDataAwareObjectInterface::columnEditable( it!=m_fieldNumbersForDataItems.constEnd() ? it.data() : -1 );
    return KexiDataAwareObjectInterface::columnEditable(col);
}

void KexiFormScrollView::valueChanged(KexiDataItemInterface* item)
{
    if (!item)
        return;
    //only signal start editing when no record editing was started already
    kDebug() << "** editedItem="
        << (dbFormWidget()->editedItem ? dbFormWidget()->editedItem->value().toString() : QString())
        << ", "
        << (item ? item->value().toString() : QString());
    if (dbFormWidget()->editedItem != item) {
        kDebug() << "**>>> dbFormWidget()->editedItem = dynamic_cast<KexiFormDataItemInterface*>(item)";
        dbFormWidget()->editedItem = dynamic_cast<KexiFormDataItemInterface*>(item);
        startEditCurrentCell();
    }
    fillDuplicatedDataItems(dynamic_cast<KexiFormDataItemInterface*>(item), item->value());

    //value changed: clear 'default value' mode (e.g. a blue italic text)
    dynamic_cast<KexiFormDataItemInterface*>(item)->setDisplayDefaultValue(dynamic_cast<QWidget*>(item), false);
}

bool KexiFormScrollView::cursorAtNewRow() const
{
    return isInsertingEnabled() && (m_currentItem == m_insertItem || m_newRowEditing);
}

void KexiFormScrollView::lengthExceeded(KexiDataItemInterface *item, bool lengthExceeded)
{
    showLengthExceededMessage(item, lengthExceeded);
}

void KexiFormScrollView::updateLengthExceededMessage(KexiDataItemInterface *item)
{
    showUpdateForLengthExceededMessage(item);
}

void KexiFormScrollView::initDataContents()
{
    KexiDataAwareObjectInterface::initDataContents();

    if (isPreviewing()) {
//! @todo here we can react if user wanted to show the navigator
        setRecordNavigatorVisible(m_data);
        recordNavigator()->setEnabled(m_data);
        if (m_data) {
            recordNavigator()->setEditingIndicatorEnabled(!isReadOnly());
            recordNavigator()->showEditingIndicator(false);
        }

        dbFormWidget()->updateReadOnlyFlags();
    }
}

KexiDB::TableViewColumn* KexiFormScrollView::column(int col)
{
    const int id = fieldNumberForColumn(col);
    return (id >= 0) ? m_data->column(id) : 0;
}

bool KexiFormScrollView::shouldDisplayDefaultValueForItem(KexiFormDataItemInterface* itemIface) const
{
    return cursorAtNewRow()
           && !itemIface->columnInfo()->field->defaultValue().isNull()
//??  && (m_editor ? m_editor->value()==itemIface->columnInfo()->fielm_defaultValue() : true)
           && !itemIface->columnInfo()->field->isAutoIncrement(); // default value defined
}

bool KexiFormScrollView::cancelEditor()
{
    if (!dynamic_cast<KexiFormDataItemInterface*>(m_editor))
        return false;

    if (m_errorMessagePopup)
        m_errorMessagePopup->close();

    KexiFormDataItemInterface *itemIface = dynamic_cast<KexiFormDataItemInterface*>(m_editor);
    itemIface->undoChanges();

    const bool displayDefaultValue = shouldDisplayDefaultValueForItem(itemIface);
    // now disable/enable "display default value" if needed (do it after setValue(), before setValue() turns it off)
    if (itemIface->hasDisplayedDefaultValue() != displayDefaultValue)
        itemIface->setDisplayDefaultValue(dynamic_cast<QWidget*>(itemIface), displayDefaultValue);

    fillDuplicatedDataItems(itemIface, m_editor->value());

    // this will clear editor pointer and close message popup (if present)
    return KexiDataAwareObjectInterface::cancelEditor();
}

void KexiFormScrollView::updateAfterCancelRowEdit()
{
    foreach(KexiFormDataItemInterface *dataItemIface, m_dataItems) {
        if (dynamic_cast<QWidget*>(dataItemIface)) {
            kDebug()
                << dynamic_cast<QWidget*>(dataItemIface)->metaObject()->className() << " "
                << dynamic_cast<QWidget*>(dataItemIface)->objectName();
        }
        const bool displayDefaultValue = shouldDisplayDefaultValueForItem(dataItemIface);
        dataItemIface->undoChanges();
        if (dataItemIface->hasDisplayedDefaultValue() != displayDefaultValue)
            dataItemIface->setDisplayDefaultValue(
                dynamic_cast<QWidget*>(dataItemIface), displayDefaultValue);
    }
    recordNavigator()->showEditingIndicator(false);
    dbFormWidget()->editedItem = 0;
}

void KexiFormScrollView::updateAfterAcceptRowEdit()
{
    if (!m_currentItem)
        return;
    recordNavigator()->showEditingIndicator(false);
    dbFormWidget()->editedItem = 0;
    //update visible data because there could be auto-filled (eg. autonumber) fields
    fillDataItems(*m_currentItem, cursorAtNewRow());
    d->previousRecord = m_currentItem;
}

int KexiFormScrollView::fieldNumberForColumn(int col)
{
    KexiFormDataItemInterface *item = dynamic_cast<KexiFormDataItemInterface*>(
                                            dbFormWidget()->orderedDataAwareWidgets()->at(col));
    if (!item)
        return -1;
    KexiFormDataItemInterfaceToIntMap::ConstIterator it(m_fieldNumbersForDataItems.find(item));
    return it != m_fieldNumbersForDataItems.constEnd() ? (int)it.value() : -1;
}


void KexiFormScrollView::beforeSwitchView()
{
    m_editor = 0;
}

void KexiFormScrollView::refreshContentsSize()
{
    KexiScrollView::refreshContentsSize();
    //only clear cmd history when KexiScrollView::refreshContentsSizeLater() has been called
    if (!isPreviewing() && sender() == delayedResizeTimer()) {
        if (d->form)
            d->form->clearUndoStack();
    }
}

void KexiFormScrollView::handleDataWidgetAction(const QString& actionName)
{
    QWidget *w = focusWidget();
    KexiFormDataItemInterface *item = 0;
    while (w) {
        item = dynamic_cast<KexiFormDataItemInterface*>(w);
        if (item)
            break;
        w = w->parentWidget();
    }
    if (item)
        item->handleAction(actionName);
}

void KexiFormScrollView::copySelection()
{
    handleDataWidgetAction("edit_copy");
}

void KexiFormScrollView::cutSelection()
{
    handleDataWidgetAction("edit_cut");
}

void KexiFormScrollView::paste()
{
    handleDataWidgetAction("edit_paste");
}

int KexiFormScrollView::lastVisibleRow() const
{
//! @todo unimplemented for now, this will be used for continuous forms
    return -1;
}

#include "kexiformscrollview.moc"
