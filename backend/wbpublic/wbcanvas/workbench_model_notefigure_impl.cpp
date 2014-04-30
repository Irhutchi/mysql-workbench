/* 
 * Copyright (c) 2007, 2012, Oracle and/or its affiliates. All rights reserved.
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
#include "workbench_model_notefigure_impl.h"

#include "model_layer_impl.h"
#include "model_diagram_impl.h"

using namespace base;

workbench_model_NoteFigure::ImplData::ImplData(workbench_model_NoteFigure *self)
  : super(self), _figure(0)
{
  _resizable= true;
}


void workbench_model_NoteFigure::ImplData::set_text(const std::string &text)
{
  self()->_text= text;
  
  if (_figure)
  {
    _figure->set_text(text);
    
    Size min_size= _figure->get_min_size();
    Size size= _figure->get_size();
    if (min_size.width > size.width)
      size.width= min_size.width;
    if (min_size.height > size.height)
      size.height= min_size.height;
    if (size != _figure->get_size())
    {
      if (*self()->_manualSizing)
        get_canvas_item()->set_fixed_size(size);
      else
        get_canvas_item()->resize_to(size);
      
      figure_bounds_changed(_figure->get_bounds());
    }
  }
}


void workbench_model_NoteFigure::ImplData::unrealize()
{
  notify_will_unrealize();
  
  super::unrealize();
  
  delete _figure;
  _figure= 0;
}



bool workbench_model_NoteFigure::ImplData::realize()
{
  if (_figure) return true;
  if (!is_realizable()) return false;
  
  if (!is_main_thread())
  {
    run_later(boost::bind(&ImplData::realize, this));
    return true;
  }

  if (!_figure)
  {
    mdc::CanvasView *view= self()->owner()->get_data()->get_canvas_view();
    mdc::AreaGroup *agroup;
  
    view->lock();
    
    wbfig::Note *note= _figure= new wbfig::Note(view->get_current_layer(), self()->owner()->get_data(), self());
    note->set_text(self()->_text);

    agroup= self()->layer()->get_data()->get_area_group();
    
    view->get_current_layer()->add_item(_figure, agroup);
    
    _figure->set_color(Color::parse(*self()->_color));

    finish_realize();
    
    view->unlock();

    self()->owner()->get_data()->notify_object_realize(self());
  }
  return true;
}
