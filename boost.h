#ifndef BOOST_H
#define BOOST_H

#include <string.h>
#include <string>
#include "diccionario.h"
#include "commons.h"
#include "basedate.h"

void parsedatatype(std::vector<std::string> &sqlvector,attribute &atr,unsigned int &pos);

void help() {
  std::cout << "MiniDB 1.0.0" << std::endl;
  std::cout << "Implemented SQL types:" << std::endl;
  std::cout << "#QUIT#" << std::endl;
  std::cout << "#HELP#" << std::endl;
  std::cout << "#EXEC#" << std::endl;
  std::cout << "#CREATE DATABASE#" << std::endl;
  std::cout << "#SHOW DATABASES#" << std::endl;
  std::cout << "#USE#" << std::endl;
  std::cout << "#DROP DATABASE#" << std::endl;
  std::cout << "#CREATE TABLE#" << std::endl;
  std::cout << "#SHOW TABLES#" << std::endl;
  std::cout << "#DROP TABLES#" << std::endl;
  std::cout << "#CREATE INDEX#" << std::endl;
  std::cout << "#DROP INDEX#" << std::endl;
  std::cout << "#SELECT#" << std::endl;
  std::cout << "#INSERT#" << std::endl;
  std::cout << "#DELETE#" << std::endl;
  std::cout << "#UPDATE#" << std::endl;
}

std::vector<std::string> split(std::string &str,std::string sep){
  char* cstr=const_cast<char*>(str.c_str());
  char* current;
	std::vector<std::string> arr;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		arr.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
	return arr;
}

void parsedatabase(std::string &name,std::vector<std::string> &sqlvector) {
  if (sqlvector.size() <= 2) {
    std::cout << "error" << '\n';
  }
  else{
    name=sqlvector[2];
  }
}

void parsetable(dictionary &d,std::vector<std::string> &sqlvector) {
  bool is_attr = true;
  unsigned int pos=2;
  if (sqlvector.size()<=pos) {
    std::cout << "error" << '\n';
  }
  else{
    int pk;
    std::vector<attribute> _atr;
    std::string name=sqlvector[pos];
    pos++;
    if (sqlvector[pos] != "(") {
      std::cout << "error" << '\n';
    }
    pos++;

    bool has_pk=false;

    while (is_attr) {
      is_attr = false;
      if (sqlvector[pos] == "primarykey") {
        pos++;
        if (has_pk) {
          std::cout << "error" << '\n';
        }
        if (sqlvector[pos] != "(") {
          std::cout << "error" << '\n';
        }
        pos++;
        for (unsigned int i=0;i < _atr.size(); ++i) {
          if (_atr[i].get_name()==sqlvector[pos]) {
            pk=i;
            break;
          }
        }
        pos++;
        if (sqlvector[pos] != ")") {
          std::cout << "error" << '\n';
        }
        has_pk=true;
      } else{
        attribute atr;
        atr.set_name(sqlvector[pos]);
        pos++;
        parsedatatype(sqlvector,atr,pos);

        _atr.push_back(atr);

        if (sqlvector[pos] != ")") {
          is_attr=true;
        }
      }
      dictionary d1(name,_atr,pk);
      d=d1;
    }
  }
}

void parsedatatype(std::vector<std::string> &sqlvector,attribute &atr,unsigned int &pos) {
  if (sqlvector[pos] == "int") {
    atr.set_data_type(T_INT);
    pos++;
    if (sqlvector[pos]==",") {
      pos++;
    }
  } else if(sqlvector[pos] == "float"){
    atr.set_data_type(T_FLOAT);
    pos++;
    if (sqlvector[pos]==",") {
      pos++;
    }
  } else if(sqlvector[pos]=="char"){
    atr.set_data_type(T_CHAR);
    pos++;
    if (sqlvector[pos] == "(") {
      pos++;
    }
    pos++;
    if (sqlvector[pos] == ")") {
      pos++;
    }
    if (sqlvector[pos] == ",") {
      pos++;
    }
  } else{
    std::cout << "error" << '\n';
  }
}

void parseinsert(std::string &name,std::vector<Value> &val,std::vector<std::string> &sqlvector) {
  unsigned int pos = 1;
  bool is_atr=true;
  if (sqlvector[pos] != "into") {
    std::cout << "errorinsert" << '\n';
    return;
  }
  pos++;
  name=sqlvector[pos];
  pos++;
  if (sqlvector[pos] != "values") {
    std::cout << "errorvalues" << '\n';
    return;
  }
  pos++;
  if (sqlvector[pos] != "(") {
    std::cout << "errorsintax" << '\n';
    return;
  }

  pos++;
  while (is_atr) {
    is_atr=false;
    Value sqlvalue;
    std::string value = sqlvector[pos];
    if (value.at(0) == '\'' || value.at(0) == '\"') {
      value.assign(value,1,value.length() - 2);
      sqlvalue.data_type = 2;
    }else{
      if (value.find(".") != std::string::npos) {
        sqlvalue.data_type = 1;
      }
      else{
        sqlvalue.data_type = 0;
      }
    }
    sqlvalue.value = value;
    pos++;
    val.push_back(sqlvalue);
    if (sqlvector[pos] != ")") {
      is_atr = true;
    }
    pos++;
  }


}

#endif
