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

//Notes:-
//-> lone +/- read as 0; so (x + y) will become (x 0 y)
//-> max atom length = 10; will read first 10 chars if longer, 9 chars if starts with +/-; error during parsing: extra chars read as another atom, but no separator=>error
//-> t/nil will be handled as static T/NIL atoms
//-> lowercase allowed, converted to uppercase while parsing
//-> mention how exiting is done

#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include "se.h"
#include "io_return.h"

extern void delete_trees(std::vector<SE*>);

inline bool is_atom_start(char ch)
{
  return (isalnum(ch) || ch == '+' || ch == '-');
}

void stack_ops(std::stack<char>* left_braces, char ch, bool* ptr_done)
{
  if (ch=='(') {left_braces->push(ch);}
  else if (ch==')') {left_braces->pop(); if (left_braces->empty()) {*ptr_done = true;}}
  else if (is_atom_start(ch)) if (left_braces->empty()) *ptr_done = true;
}

std::string get_stdin_s_exp()
{
  std::string input_exp="";
  std::string temp;
  std::stack<char> left_braces; std::stack<char>* ptr_left_braces = &left_braces;
  bool done=false, *ptr_done = &done;
  do //TODO: slow;
  {
    std::getline(std::cin, temp);
    input_exp.append(temp); input_exp.push_back(' ');
    for (std::string::iterator iter=temp.begin(); iter != temp.end(); ++iter)
      stack_ops(ptr_left_braces, *iter, ptr_done);
  } while (!done);
  
  std::cout <<">Input Exp="<<input_exp<<std::endl;
  
  return input_exp;
}

//TODO: cout<=>cout
io_return* make_s_exp(std::string input_str, int input_ind)
{
  static const int C_NONE = 0;
  static const int C_LEFT = 1;
  static const int C_RIGHT = 2;

  static const int S_NONE = 0;
  static const int S_DOT = 1;
  static const int S_LIST = 2;

  int cur_se_type = S_NONE;
  int child = C_NONE;
  
  SE* node = NULL;
  SE* cur_node = NULL;
  SE* new_atom = NULL;
  SE* new_node = NULL;
  
  char cur_char;
  char ch_temp;
  int i=0;
  
  char name_chars[SE::ATOM_MAX_LEN+1];
  int atom_value=0;
  
  while (1)
  {
    cur_char = input_str[input_ind];
    if (cur_char == '(')
    {
      if (input_ind > 0)
      {
	ch_temp = input_str[input_ind-1];
	if (ch_temp != '(' && !isspace(ch_temp) && ch_temp != '.')
	{
	  std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Inadmissible character and/or extra atom. Parsing stopped. Output will be bad."<<std::endl;
	  return new io_return(node, input_ind);
	}
      }
      node = new SE(SE::S_EXP_BIN, -1, "bin", NULL, NULL);
      cur_node = node;
      child = C_LEFT;
      cur_se_type = S_NONE;
    }
    
    else if (isalnum(cur_char) || cur_char == '+' || cur_char == '-')
    {
      if (input_ind > 0)
      {
	ch_temp = input_str[input_ind-1];
	if (ch_temp != '(' && ch_temp != ')' && !isspace(ch_temp) && ch_temp != '.')
	{
	  std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Inadmissible character and/or extra atom. Parsing stopped. Output will be bad."<<std::endl;
	  return new io_return(node, input_ind);
	}
      }
      if (child == C_NONE && cur_se_type == S_DOT)
      {
	std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Extra atom. Parsing stopped. Output will be bad."<<std::endl;
	  return new io_return(node, input_ind);
      }  
      new_atom = new SE(SE::S_EXP_INT, -1, "", NULL, NULL);
      if (isalpha(cur_char))
      {
	new_atom->set_type(SE::S_EXP_IDN);
	for (i=0; i<SE::ATOM_MAX_LEN; i++)
	{
	  if (isalnum(input_str[input_ind]))
	    name_chars[i] = toupper(input_str[input_ind++]);
	  else
	    break;
	}
	name_chars[i] = '\0';
	std::string name(name_chars);
	if (name.compare(SE::ATOM_T->get_name()) == 0)
	{
	  delete new_atom;
	  new_atom = SE::ATOM_T;
	}
	else if (name.compare(SE::ATOM_NIL->get_name()) == 0)
	{
	  delete new_atom;
	  new_atom = SE::ATOM_NIL;
	}
	else
	{
	  new_atom->set_name(name);
	}
      }
      else if (isdigit(cur_char))
      {
	new_atom->set_type(SE::S_EXP_INT);
	for (i=0; i<SE::ATOM_MAX_LEN; i++)
	  if (isdigit(input_str[input_ind]))
	    atom_value = atom_value*10 + input_str[input_ind++] - 48;
	  else
	    break;
	new_atom->set_val(atom_value);
      }
      else if (cur_char == '+')
      {
	input_ind++;
	for (i=0; i<SE::ATOM_MAX_LEN - 1; i++)
	  if (isdigit(input_str[input_ind]))
	    atom_value = atom_value*10 + input_str[input_ind++] - 48;
	  else
	    break;
	
	new_atom->set_type(SE::S_EXP_INT);
	new_atom->set_val(atom_value);
      }
      else if (cur_char == '-')
      {
	input_ind++;
	for (i=0; i<SE::ATOM_MAX_LEN - 1; i++)
	  if (isdigit(input_str[input_ind]))
	    atom_value = atom_value*10 - input_str[input_ind++] + 48;
	  else
	    break;
	
	new_atom->set_type(SE::S_EXP_INT);
	new_atom->set_val(atom_value);
      }
      input_ind--;
      atom_value = 0;
      
      if (node == NULL)
	return new io_return(new_atom, input_ind);
      else if (child == C_LEFT)
      {
	cur_node->set_left_child(new_atom);
	child = C_RIGHT;
      }
      else if (child == C_RIGHT)
      {
	cur_node->set_right_child(new_atom);
	child = C_NONE;
      }
    }
    
    else if (cur_char == ')')
    {
      ch_temp = input_str[input_ind+1];
      if (!isspace(ch_temp) && ch_temp != ')' && ch_temp != '.')
      {
	std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Inadmissible character. Parsing stopped. Output will be bad."<<std::endl;
	  return new io_return(node, input_ind);
      }
      if (cur_se_type == S_DOT)
      {
	if (child == C_NONE)
	  return new io_return(node, input_ind);
	else
	{
	  std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Possibly premature s-expn closure. Parsing stopped. Output will be bad."<<std::endl;
	  return new io_return(node, input_ind);
	}
      }
      else
      {
	if (child == C_LEFT)
	{
	  //cout << "Parsing error at index="<<input_ind<<". Program logic bugg."<<endl;
	  //return NULL;
	  //empty list
	  delete cur_node;
	  node = SE::ATOM_NIL;
	}
	else
	  cur_node->set_right_child(SE::ATOM_NIL);
	return new io_return(node, input_ind);
      }
    }
    
    else if (isspace(cur_char))
    {
      while (isspace(input_str[input_ind]))
	input_ind++;
      if (input_str[input_ind] != ')')
      {
	if (cur_se_type != S_DOT && child == C_LEFT)
	{
	  if (input_str[input_ind] == '.')
	  {
	    std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Invalid dot notation. Parsing stopped. Output will be bad."<<std::endl;
	  return new io_return(node, input_ind);
	  }
	}
	else if (child == C_RIGHT)
	{
	  if (input_str[input_ind] == '.')
	  {
	    if (cur_se_type == S_LIST)
	    {
	       std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Dot/list notation conflict. Parsing stopped. Output will be bad."<<std::endl;
	       return new io_return(node, input_ind);
	    }
	  }
	  //if (input_str[input_ind] == '.')
	  //  cur_se_type = S_DOT;
	  else if (cur_se_type != S_DOT)
	  {
	    cur_se_type = S_LIST;
	    new_node = new SE(SE::S_EXP_BIN, -1, "bini", NULL, NULL);
	    cur_node->set_right_child(new_node);
	    child = C_LEFT;
	    cur_node = new_node;
	  }
	}	
      }
      
      input_ind--;
    }
    
    else if (cur_char == '.')
    {
      if (cur_se_type == S_LIST)
      {
	std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Dot/list notation conflict. Parsing stopped. Output will be bad."<<std::endl;
	  return new io_return(node, input_ind);
      }
      else if (cur_se_type == S_DOT)
      {
	std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Double dot detected. Parsing stopped. Output will be bad."<<std::endl;
	  return new io_return(node, input_ind);
      }
      cur_se_type = S_DOT;
    } 
    
    else
    {
      std::cout << ">ERROR: Parsing error at index="<<input_ind<<": Invalid character. Parsing stopped. Output will be bad."<<std::endl;
	  return new io_return(node, input_ind);
    }
    
    if (input_str[input_ind+1] == '(' && child != C_NONE)
    {
      io_return* returned_obj = make_s_exp(input_str, input_ind+1);
      if (child == C_LEFT)
      {
	cur_node->set_left_child(returned_obj->get_node());
	child = C_RIGHT;
      }
      else if (child == C_RIGHT)
      {
	cur_node->set_right_child(returned_obj->get_node());
	child = C_NONE; 
      }
      input_ind = returned_obj->get_input_ind();
      delete returned_obj;
    }
    
    input_ind++;
  }
}

void print_dotted_s_exp(const SE* tree)
{
  if (tree == NULL)
    return;
  if (tree->get_type() == SE::S_EXP_INT)
    std::cout << tree->get_val();
  else if (tree->get_type() == SE::S_EXP_IDN)
    std::cout << tree->get_name();
  else if (tree->get_type() == SE::S_EXP_BIN)
  {
    std::cout << '(';
    print_dotted_s_exp(tree->get_left_child());
    std::cout <<" . ";
    print_dotted_s_exp(tree->get_right_child());
    std::cout << ')';
  }
}

std::vector<SE*> trees;

void get_and_print_s_exps()
{
  SE* tree = NULL;
  std::cout << "\n\n>Input s-expression:-" << std::endl;
  io_return* object = make_s_exp(get_stdin_s_exp(), 0);
  tree = object->get_node();
  delete object;
  std::cout << '>';
  print_dotted_s_exp(tree);
  trees.push_back(tree);
}

void delete_s_exps()
{
  delete_trees(trees);
}
