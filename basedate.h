#ifndef BASE_DATE_H
#define BASE_DATE_H

#include "table.h"
#include <list>
#include <string>

class database {
public:
  std::string namebd;
  std::list<table > list_table;
public:
  database (){};
  database (std::string &_name);
  void add_table(dictionary &d);
  bool find_table(table &r,table *&p);
  void show_table(std::ostream &out);
  void insert_tupla(std::string &name,std::vector<Value> &v);

  void quit();
};

void database::quit() {
  list_table.~list();
  // std::string carp="rmdir "+namebd;
  std::cout << "quiting..." << '\n';
  // system(carp.c_str());
}

database::database(std::string &_name){
  this->namebd=_name;
  // std::string carp="mkdir "+_name;
  // system(carp.c_str());
}

void database::add_table(dictionary &d){
  table t(d);
  list_table.push_back(t);
}

bool database::find_table(table &r,table *&p){
  auto it=list_table.begin();
  for (;it!=list_table.end();++it) {
    if ((*it)==r) {
      p=&(*it);
      return true;
    }
  }
  return false;
}

void database::insert_tupla(std::string &name,std::vector<Value> &value) {
  dictionary d(name);
  table t(d);

  table *p;
  if (find_table(t,p)) {
    if (p->date_table.getsize() == value.size()) {
      p->set_value(value);
    }else{
      std::cout << "errortuplas" << '\n';
    }
  }
}

void database::show_table(std::ostream &out) {
  for (auto it=list_table.begin();it!=list_table.end();++it) {
    out<<(*it)<<"\n";
  }
}

#endif
