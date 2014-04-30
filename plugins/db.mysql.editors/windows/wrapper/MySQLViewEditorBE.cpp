/* 
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
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
#include "grts/structs.workbench.physical.h"

#include "MySQLViewEditorBE.h"

using namespace MySQL::Grt::Db;

//--------------------------------------------------------------------------------------------------

void MySQL::Grt::Db::MySQLViewEditorBE::load_view_sql()
{
  get_unmanaged_object()->load_view_sql();
}

//--------------------------------------------------------------------------------------------------

void MySQL::Grt::Db::MySQLViewEditorBE::commit_changes()
{
  get_unmanaged_object()->commit_changes();
}

//--------------------------------------------------------------------------------------------------

