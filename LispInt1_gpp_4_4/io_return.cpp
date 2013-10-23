/*
    Author: Anirban Roychowdhury
    Copyright (C) 2013  Anirban Roychowdhury <roychowdhury.7@osu.edu>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "io_return.h"

io_return::io_return()
{
}

io_return::io_return(SE* node, int ind)
{
  this->node = node;
  this->input_ind = ind;
}

io_return::~io_return()
{
}

io_return& io_return::operator=(const io_return& other)
{
    return *this;
}

bool io_return::operator==(const io_return& other) const
{
///TODO: return ...;
}

SE* io_return::get_node()
{
  return node;
}

int io_return::get_input_ind()
{
  return input_ind;
}

void io_return::set_node(SE* const node)
{
  this->node=node;
}

void io_return::set_input_ind(int ind)
{
  input_ind = ind;
}




