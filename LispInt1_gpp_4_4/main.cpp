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

#include <iostream>
#include <cstdlib>
#include <signal.h>

extern void get_and_print_s_exps();
extern void delete_s_exps();

void exit_handler(int exit_code)
{
  delete_s_exps();
  std::cout << "\n>Caught signal "<<exit_code<<". Heap allocations cleared. Press Enter to exit.."<<std::endl;
  char ch;
  std::cin.get(ch);
  exit(exit_code);
}

int main(int argc, char **argv) {
  
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = exit_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);
  
  while(1)
    get_and_print_s_exps();
    
  return 0;
}
