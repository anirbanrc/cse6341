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
#include <iostream>

const int SE::S_EXP_INT = 0;
const int SE::S_EXP_IDN = 1;
const int SE::S_EXP_BIN = 2;
    
const int SE::ATOM_MAX_LEN = 10;
    
const std::string SE::P_T = "T";
const std::string SE::P_NIL = "NIL";
const std::string SE::P_CAR = "CAR";
const std::string SE::P_CDR = "CDR";
const std::string SE::P_CONS = "CONS";
const std::string SE::P_ATOM = "ATOM";
const std::string SE::P_EQ = "EQ";
const std::string SE::P_NULL = "NULL";
const std::string SE::P_INT = "INT";
const std::string SE::P_PLUS = "PLUS";
const std::string SE::P_MINUS = "MINUS";
const std::string SE::P_TIMES = "TIMES";
const std::string SE::P_QUOTIENT = "QUOTIENT";
const std::string SE::P_REMAINDER = "REMAINDER";
const std::string SE::P_LESS = "LESS";
const std::string SE::P_GREATER = "GREATER";
const std::string SE::P_COND = "COND";
const std::string SE::P_QUOTE = "QUOTE";
const std::string SE::P_DEFUN = "DEFUN";

SE* SE::ATOM_T = new SE(SE::S_EXP_IDN, -1, SE::P_T, NULL, NULL);
SE* SE::ATOM_NIL = new SE(SE::S_EXP_IDN, -1, SE::P_NIL, NULL, NULL);

SE::SE()
{
}

SE::SE(int type, int val, std::string name, const SE* l_child, const SE* r_child)
{
  this->type = type;
  this->int_val = val;
  this->name = name;
  left_child = l_child;
  right_child = r_child;
}

SE::~SE()
{
}

SE& SE::operator=(const SE& other)
{
    return *this;
}

bool SE::operator==(const SE& other) const
{
///TODO: return ...;
}

int SE::get_type() const
{
  return type;
}

int SE::get_val() const
{
  return int_val;
}

std::string SE::get_name() const
{
  return name;
}

const SE* SE::get_left_child() const
{
  return left_child;
}

const SE* SE::get_right_child() const
{
  return right_child;
}

void SE::set_type(int type)
{
  this->type = type;
}

void SE::set_val(int val)
{
  int_val = val;
}

void SE::set_name(const std::string name)
{
  this->name = name;
}

void SE::set_left_child(SE* const lchild)
{
  left_child = lchild;
}

void SE::set_right_child(SE* const rchild)
{
  right_child = rchild;
}

const SE* SE::car(const SE* s_exp)
{
  if (s_exp->get_type() != SE::S_EXP_BIN)
    return NULL;
  else
    return s_exp->get_left_child();
}

const SE* SE::cdr(const SE* s_exp)
{
  if (s_exp->get_type() != SE::S_EXP_BIN)
    return NULL;
  else
    return s_exp->get_right_child();
}

const SE* SE::cons(const SE* atom, const SE* s_exp)
{
  if (atom->get_type() == SE::S_EXP_BIN || s_exp->get_type() != SE::S_EXP_BIN)
    return NULL;
  else
    return new SE(SE::S_EXP_BIN, -1, "bin", atom, s_exp);
}

const SE* SE::atom(const SE* s_exp)
{
  if (s_exp->get_type() != SE::S_EXP_BIN)
    return SE::ATOM_T;
  else
    return SE::ATOM_NIL;
}

const SE* SE::eq(const SE* atom_one, const SE* atom_two)
{
  if (atom_one->get_type() == SE::S_EXP_BIN || atom_two->get_type() == SE::S_EXP_BIN)
    return NULL;
  else if (atom_one->get_type() == SE::S_EXP_INT && atom_two->get_type() == SE::S_EXP_INT)
  {
    if (atom_one->get_val() == atom_two->get_val())
      return SE::ATOM_T;
    else
      return SE::ATOM_NIL;
  }
  else if (atom_one->get_type() == SE::S_EXP_IDN && atom_two->get_type() == SE::S_EXP_IDN)
  {
    if (atom_one->get_name().compare(atom_two->get_name()) == 0)
      return SE::ATOM_T;
    else
      return SE::ATOM_NIL;
  }
  else
    return NULL;
}

const SE* SE::null(const SE* s_exp)
{
  return SE::eq(s_exp, SE::ATOM_NIL);
}

const SE* SE::_int(const SE* s_exp)
{
  if (s_exp->get_type() == SE::S_EXP_INT)
    return SE::ATOM_T;
  else
    return SE::ATOM_NIL;
}

const SE* SE::plus(const SE* s_one, const SE* s_two)
{
  if (s_one->get_type() == SE::S_EXP_INT && s_two->get_type() == SE::S_EXP_INT)
    return new SE(SE::S_EXP_INT, s_one->get_val() + s_two->get_val(), "", NULL, NULL);
  else
    return NULL;
}

const SE* SE::minus(const SE* s_one, const SE* s_two)
{
  if (s_one->get_type() == SE::S_EXP_INT && s_two->get_type() == SE::S_EXP_INT)
    return new SE(SE::S_EXP_INT, s_one->get_val() - s_two->get_val(), "", NULL, NULL);
  else
    return NULL;
}

const SE* SE::times(const SE* s_one, const SE* s_two)
{
  if (s_one->get_type() == SE::S_EXP_INT && s_two->get_type() == SE::S_EXP_INT)
    return new SE(SE::S_EXP_INT, s_one->get_val() * s_two->get_val(), "", NULL, NULL);
  else
    return NULL;
}

const SE* SE::quotient(const SE* s_one, const SE* s_two)
{
  if (s_one->get_type() == SE::S_EXP_INT && s_two->get_type() == SE::S_EXP_INT)
    return new SE(SE::S_EXP_INT, s_one->get_val() / s_two->get_val(), "", NULL, NULL);
  else
    return NULL;
}

const SE* SE::remainder(const SE* s_one, const SE* s_two)
{
  if (s_one->get_type() == SE::S_EXP_INT && s_two->get_type() == SE::S_EXP_INT)
    return new SE(SE::S_EXP_INT, s_one->get_val() % s_two->get_val(), "", NULL, NULL);
  else
    return NULL;
}

const SE* SE::less(const SE* s_one, const SE* s_two)
{
  if (s_one->get_type() == SE::S_EXP_INT && s_two->get_type() == SE::S_EXP_INT)
  {
    if (s_one->get_val() < s_two->get_val())
      return SE::ATOM_T;
    else
      return SE::ATOM_NIL;
  }
  else
    return NULL;
}

const SE* SE::greater(const SE* s_one, const SE* s_two)
{
  if (s_one->get_type() == SE::S_EXP_INT && s_two->get_type() == SE::S_EXP_INT)
  {
    if (s_one->get_val() > s_two->get_val())
      return SE::ATOM_T;
    else
      return SE::ATOM_NIL;
  }
  else
    return NULL;
}



















