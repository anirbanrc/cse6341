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

#ifndef SE_H
#define SE_H

#include <string>

class SE
{
    int type;
    int int_val;
    std::string name;
    const SE* left_child;
    const SE* right_child;

public:
    SE();
    SE(int, int, std::string, const SE*, const SE*);
    virtual ~SE();
    virtual SE& operator=(const SE& other);
    virtual bool operator==(const SE& other) const;

    void set_const_atoms();
    
    void set_type(int);
    void set_val(int);
    void set_name(const std::string);
    void set_left_child(SE* const);
    void set_right_child(SE* const);
    
    int get_type() const;
    int get_val() const;
    std::string get_name() const;
    const SE* get_left_child() const;
    const SE* get_right_child() const;
    
    static const int S_EXP_INT;
    static const int S_EXP_IDN;
    static const int S_EXP_BIN;
    
    static const int ATOM_MAX_LEN;
    
    static SE* ATOM_T;
    static SE* ATOM_NIL;
    
    static const std::string P_T;
    static const std::string P_NIL;
    static const std::string P_CAR;
    static const std::string P_CDR;
    static const std::string P_CONS;
    static const std::string P_ATOM;
    static const std::string P_EQ;
    static const std::string P_NULL;
    static const std::string P_INT;
    static const std::string P_PLUS;
    static const std::string P_MINUS;
    static const std::string P_TIMES;
    static const std::string P_QUOTIENT;
    static const std::string P_REMAINDER;
    static const std::string P_LESS;
    static const std::string P_GREATER;
    static const std::string P_COND;
    static const std::string P_QUOTE;
    static const std::string P_DEFUN;
    
    static const SE* car(const SE*);
    static const SE* cdr(const SE*);
    static const SE* cons(const SE*, const SE*);
    static const SE* atom(const SE*);
    static const SE* eq(const SE*, const SE*);
    static const SE* null(const SE*);
    static const SE* _int(const SE*);
    static const SE* plus(const SE*, const SE*);
    static const SE* minus(const SE*, const SE*);
    static const SE* times(const SE*, const SE*);
    static const SE* quotient(const SE*, const SE*);
    static const SE* remainder(const SE*, const SE*);
    static const SE* less(const SE*, const SE*);
    static const SE* greater(const SE*, const SE*);
};

#endif // SE_H
