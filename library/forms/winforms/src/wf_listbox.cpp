/* 
 * Copyright (c) 2009, 2013, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#include "stdafx.h"

#include "wf_base.h"
#include "wf_view.h"
#include "wf_listbox.h"

using namespace System::Windows::Forms;

using namespace MySQL;
using namespace MySQL::Forms;

//----------------- MformsListBox ------------------------------------------------------------------

ref class MformsListBox : ListBox
{
public:
  virtual void OnSelectedIndexChanged(System::EventArgs ^args) override
  {
    __super::OnSelectedIndexChanged(args);

    mforms::ListBox *backend = ListBoxWrapper::GetBackend<mforms::ListBox>(this);
    if (backend != NULL)
      backend->selection_changed();
  }

};

//----------------- ListBoxWrapper -----------------------------------------------------------------

ListBoxWrapper::ListBoxWrapper(mforms::ListBox *backend)
  : ViewWrapper(backend)
{
}

//--------------------------------------------------------------------------------------------------

bool ListBoxWrapper::create(mforms::ListBox *backend, bool multi_select)
{
  ListBoxWrapper *wrapper = new ListBoxWrapper(backend);

  MformsListBox ^listbox = ListBoxWrapper::Create<MformsListBox>(backend, wrapper);
  listbox->Size = Drawing::Size(100, 100);
  if (multi_select)
    listbox->SelectionMode = SelectionMode::MultiExtended;
  return true;
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::clear(mforms::ListBox *backend)
{
  ListBoxWrapper::GetManagedObject<ListBox>(backend)->Items->Clear();
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::set_heading(mforms::ListBox *backend, const std::string &text)
{
  // TODO: what's the heading of a listbox?
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::add_items(mforms::ListBox *backend, const std::list<std::string> &items)
{
  ListBox ^listbox = ListBoxWrapper::GetManagedObject<ListBox>(backend);
  listbox->BeginUpdate();
  try
  {
    for each(std::string entry in items)
      listbox->Items->Add(CppStringToNative(entry));
  }
  finally
  {
    listbox->EndUpdate();
  }
}

//--------------------------------------------------------------------------------------------------

int ListBoxWrapper::add_item(mforms::ListBox *backend, const std::string &item)
{
  return ListBoxWrapper::GetManagedObject<ListBox>(backend)->Items->Add(CppStringToNative(item));
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::remove_indices(mforms::ListBox *backend, const std::vector<int> &indices)
{
  ListBox ^listbox = ListBoxWrapper::GetManagedObject<ListBox>(backend);
  listbox->BeginUpdate();
  try
  {
    for (std::vector<int>::const_reverse_iterator iterator = indices.rbegin(); iterator != indices.rend();
      ++iterator)
    {
      listbox->Items->RemoveAt(*iterator);
    }
  }
  finally
  {
    listbox->EndUpdate();
  }
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::remove_index(mforms::ListBox *backend, int index)
{
  return ListBoxWrapper::GetManagedObject<ListBox>(backend)->Items->RemoveAt(index);
}

//--------------------------------------------------------------------------------------------------

std::string ListBoxWrapper::get_text(mforms::ListBox *backend)
{
  ListBox ^listbox = ListBoxWrapper::GetManagedObject<ListBox>(backend);
  if (listbox->SelectedIndex < 0)
    return "";

  return NativeToCppString(listbox->SelectedItem->ToString());

}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::set_index(mforms::ListBox *backend, int index)
{
  ListBoxWrapper::GetManagedObject<ListBox>(backend)->SelectedIndex = index;
}

//--------------------------------------------------------------------------------------------------

int ListBoxWrapper::get_index(mforms::ListBox *backend)
{
  return ListBoxWrapper::GetManagedObject<ListBox>(backend)->SelectedIndex;
}

//--------------------------------------------------------------------------------------------------

std::vector<int> ListBoxWrapper::get_selected_indices(mforms::ListBox *backend)
{
  std::vector<int> result;
  ListBox ^listbox = ListBoxWrapper::GetManagedObject<ListBox>(backend);
  for each (int index in listbox->SelectedIndices)
    result.push_back(index);
  return result;
}

//--------------------------------------------------------------------------------------------------

void ListBoxWrapper::init()
{
  mforms::ControlFactory *f = mforms::ControlFactory::get_instance();

  f->_listbox_impl.create = &ListBoxWrapper::create;
  f->_listbox_impl.clear = &ListBoxWrapper::clear;
  f->_listbox_impl.set_heading = &ListBoxWrapper::set_heading;
  f->_listbox_impl.add_items = &ListBoxWrapper::add_items;
  f->_listbox_impl.add_item = &ListBoxWrapper::add_item;
  f->_listbox_impl.get_text = &ListBoxWrapper::get_text;
  f->_listbox_impl.set_index = &ListBoxWrapper::set_index;
  f->_listbox_impl.get_index = &ListBoxWrapper::get_index;
  f->_listbox_impl.get_selected_indices = &ListBoxWrapper::get_selected_indices;
}

//--------------------------------------------------------------------------------------------------
