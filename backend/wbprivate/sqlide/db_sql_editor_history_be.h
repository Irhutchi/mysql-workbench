/* 
 * Copyright (c) 2008, 2011, Oracle and/or its affiliates. All rights reserved.
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

#ifndef _DB_SQL_EDITOR_HISTORY_BE_H_
#define _DB_SQL_EDITOR_HISTORY_BE_H_


#include "workbench/wb_backend_public_interface.h"
#include "sqlide/var_grid_model_be.h"
#include <boost/shared_ptr.hpp>
#include <time.h>
#include "mforms/menu.h"

class MYSQLWBBACKEND_PUBLIC_FUNC DbSqlEditorHistory
{
public:
  typedef boost::shared_ptr<DbSqlEditorHistory> Ref;
  static Ref create(bec::GRTManager *grtm) { return Ref(new DbSqlEditorHistory(grtm)); }
  virtual ~DbSqlEditorHistory();
protected:
  DbSqlEditorHistory(bec::GRTManager *grtm);
  bec::GRTManager *_grtm;

public:
  void reset();
  void add_entry(const std::list<std::string> &statements);
  int current_entry() { return _current_entry_index; }
  void current_entry(int index);
  std::string restore_sql_from_history(int entry_index, std::list<int> &detail_indexes);
protected:
  int _current_entry_index;

public:
  void load();

public:
  class EntriesModel;
  class DetailsModel;

public:
  class DetailsModel : public VarGridModel
  {
  public:
    friend class DbSqlEditorHistory;
    typedef boost::shared_ptr<DetailsModel> Ref;
    static Ref create(bec::GRTManager *grtm) { return Ref(new DetailsModel(grtm)); }
  protected:
    DetailsModel(bec::GRTManager *grtm);

  public:
    void add_entries(const std::list<std::string> &statements);
    virtual void refresh() { refresh_ui(); }
    mforms::Menu* get_context_menu() { return &_context_menu; }

    virtual void reset();

    void save();
    void load(const std::string &storage_file_path);
  protected:
    int _last_loaded_row; // required to skip duplication of existing entries when dumping contents

  public:
    std::tm datestamp() const { return _datestamp; }
    void datestamp(const std::tm &val) { _datestamp= val; }
  protected:
    std::string storage_file_path() const;
    std::tm _datestamp; // raw datestamp for locale independent storage file name


  private:
    grt::StringRef _last_timestamp;
    grt::StringRef _last_statement;
    mforms::Menu   _context_menu;
  };

public:
  class EntriesModel : public VarGridModel
  {
  private:
    bool _ui_usage;
  public:
    friend class DbSqlEditorHistory;
    
    typedef boost::shared_ptr<EntriesModel> Ref;
    static Ref create(DbSqlEditorHistory *owner, bec::GRTManager *grtm) { return Ref(new EntriesModel(owner, grtm)); }
  protected:
    EntriesModel(DbSqlEditorHistory *owner, bec::GRTManager *grtm);

    DbSqlEditorHistory *_owner;

    void add_statements(const std::list<std::string> &statements);
  public:
    bool insert_entry(const std::tm &t);
    void delete_all_entries();
    void delete_entries(const std::vector<int> &rows);
    void set_ui_usage(bool value) { _ui_usage = value; }
    bool get_ui_usage() { return _ui_usage; }

    std::string entry_path(int index);
    std::tm entry_date(int index);

    virtual void reset();
    void load();

    virtual bool activate_popup_item_for_nodes(const std::string &action, const std::vector<bec::NodeId> &orig_nodes);
    virtual bec::MenuItemList get_popup_items_for_nodes(const std::vector<bec::NodeId> &nodes);
  };

public:
  EntriesModel::Ref entries_model() { return _entries_model; }
  DetailsModel::Ref details_model() { return _details_model; }
  DetailsModel::Ref write_only_details_model(){return _write_only_details_model;}
protected:
  EntriesModel::Ref _entries_model;
  DetailsModel::Ref _details_model;
  DetailsModel::Ref _write_only_details_model;
};


#endif /* _DB_SQL_EDITOR_HISTORY_BE_H_ */
