
#    Author: Anirban Roychowdhury
#    Copyright (C) 2013  Anirban Roychowdhury <roychowdhury.7@osu.edu>
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

lispint : main.o io_return.o tree_utils.o se.o lispio.o
	g++ -Wall -o lispint main.o io_return.o tree_utils.o se.o lispio.o
main.o : main.cpp se.h
	g++ -Wall -c main.cpp
io_return.o : io_return.cpp io_return.h
	g++ -Wall -c io_return.cpp
lispio.o : lispio.cpp se.h io_return.h
	g++ -Wall -c lispio.cpp
se.o : se.cpp se.h
	g++ -Wall -c se.cpp
tree_utils.o : tree_utils.cpp se.h
	g++ -Wall -c tree_utils.cpp
clean : 
	rm lispint main.o io_return.o tree_utils.o se.o lispio.o
