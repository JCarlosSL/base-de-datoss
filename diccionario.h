#ifndef DICCIONARY_H
#define DICCIONARY_H
#include <vector>
#include "atribute.h"

class dictionary {
private:
  std::string name;
  std::vector<attribute> attributes;
  int pk;
  int _size;
public:
  dictionary (){};
  dictionary (std::string &_name){
    this->name=_name;
  };
  dictionary (std::string &_name,std::vector<attribute> &atr, int &p_k){
      this->name=_name;
      this->attributes=atr;
      this->pk=p_k;
      this->_size=atr.size();
  };
  int getsize(){ return this->_size;};
  bool operator > (const dictionary &r){
    return name==r.name;
  }
  bool operator == (const dictionary &r){
    return name==r.name;
  }
  friend std::ostream& operator<<(std::ostream &out,const dictionary &r){
      out<<r.name<<"\n";
      for (int i=0;i<r.attributes.size();++i) {
        out<<"-"<<r.attributes[i]<<"-";
      }
      out<<"\n";
      out<<r.pk;
      return out;
  }
  //virtual ~dictionary ();
};

#endif
