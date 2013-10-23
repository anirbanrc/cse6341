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

#include "se.h"
#include <map>
#include <iostream>
#include <vector>

void carefully_delete_tree(const SE* tree, std::map<std::string, int>* atom_counts)
{
  if (tree == NULL)
    return;
  if (tree->get_type() == SE::S_EXP_BIN)
  {
    carefully_delete_tree(tree->get_left_child(), atom_counts);
    carefully_delete_tree(tree->get_right_child(), atom_counts);
    delete tree;
  }
  else if (tree->get_type() == SE::S_EXP_IDN)
  {
    atom_counts->operator[](tree->get_name())--;
    if (atom_counts->operator[](tree->get_name()) < 1)
      delete tree;
  }
  else
    delete tree;
}

void find_atom_counts(const SE* tree, std::map<std::string, int>* atom_counts)
{
  if (tree == NULL)
    return;
  if (tree->get_type() == SE::S_EXP_BIN)
  {
    find_atom_counts(tree->get_left_child(), atom_counts);
    find_atom_counts(tree->get_right_child(), atom_counts);
  }
  else if (tree->get_type() == SE::S_EXP_IDN)
  {
    if (atom_counts->count(tree->get_name()) < 1)
      atom_counts->operator[](tree->get_name()) = 1;
    else
      atom_counts->operator[](tree->get_name())++;
  }
  return;
}

void delete_trees(std::vector<SE*> trees)
{
  std::map<std::string, int>* atom_counts = new std::map<std::string, int>;
  std::string atom_t_name = SE::ATOM_T->get_name();
  std::string atom_nil_name = SE::ATOM_NIL->get_name();
  
  for(std::vector<SE*>::iterator iter = trees.begin(); iter != trees.end(); ++iter)
    find_atom_counts(*iter, atom_counts);
  
  for(std::vector<SE*>::iterator iter = trees.begin(); iter != trees.end(); ++iter)
    carefully_delete_tree(*iter, atom_counts);
  
  if (atom_counts->find(atom_t_name) == atom_counts->end())
    delete SE::ATOM_T;
  
  if (atom_counts->find(atom_nil_name) == atom_counts->end())
    delete SE::ATOM_NIL;
  
  delete atom_counts;
}
