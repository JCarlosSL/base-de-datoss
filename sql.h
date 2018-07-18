#ifndef SQL_H
#define SQL_H
#include <sstream>
#include <algorithm>
#include "Interprete.h"

void run(){
  interprete itp;
  std::string query;

  size_t found;
  while (true) {
    std::cout<<"SuperbD> \n";
    std::getline(std::cin,query);
    // if (query.compare(0,4,"exit")==0 || query.compare(0,4,"quit")) {
    //   itp.ExecSQL("quit");
    //   break;
    // }
    itp.ExecSQL(query);
    std::cout << std::endl;
  }
}



#endif
