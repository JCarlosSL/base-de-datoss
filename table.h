#ifndef TABLE
#define TABLE
#include "diccionario.h"
#include <vector>

typedef struct {
    int data_type;
    std::string value;
} Value;

class table {
public:
  dictionary date_table;
  std::vector<std::vector<Value> > tuplas;
public:
  table (){};
  table (dictionary &_date_table){
    this->date_table=_date_table;
  };
  void set_value(std::vector<Value> &_val){
    tuplas.push_back(_val);
  };

  bool operator == (const table &r){
    return date_table==r.date_table;
  }
  friend std::ostream& operator<<(std::ostream &out,const table &a){
    out<<a.date_table<<"\n";
    for (int i=0;i<a.tuplas.size();i++) {
      for (int j=0;j<a.tuplas[i].size();j++) {
        out<<a.tuplas[i][j].value<<" - ";
      }
      out<<"\n";
    }
    return out;
  }
  //virtual ~table ();
};


#endif
