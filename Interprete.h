#ifndef INTERPRETE_H
#define INTERPRETE_H
#include "basedate.h"
#include <iostream>
#include <fstream>
#include "boost.h"
#include <regex>
#include <iterator>

class interprete {
private:
  database *api;
  std::string statement;
  std::vector<std::string> sqlvector;
  int sql_type;
public:
  interprete ();
  void ExecSQL(std::string );
  void FormatSQL();
  void TellSQLType();
  void run();
  //virtual ~interprete ();
};

interprete::interprete(){}

void interprete::FormatSQL(){
  std::regex reg("[\r\n\t]");

  statement=std::regex_replace(statement,reg," ");
  //std::cout << statement << '\n';
  reg = ";.*$";
  statement=std::regex_replace(statement,reg,"");
  reg = "(^ +)|( +$)";
	statement=regex_replace(statement,reg,"");
  reg = " +";
  statement=regex_replace(statement,reg," ");
  reg = " ?(\\(|\\)|,|=|(<>)|<|>) ?";
	statement = regex_replace(statement, reg, " $1 ");
	reg = "< *>";
	statement = regex_replace(statement, reg, "<>");
  reg = "< *=";
	statement = regex_replace(statement, reg, "<=");
  reg = "> *=";
	statement = regex_replace(statement, reg, ">=");
  std::cout << statement << '\n';
  sqlvector=split(statement," ");
}
void interprete::TellSQLType(){
  if (sqlvector.size() == 0) {
    sql_type=-1;
    std::cout << "SQL TYPE: #EMPTY#" << '\n';
    return;
  }

  if (sqlvector[0] == "quit") {
    sql_type=10;
    std::cout << "SQL TYPE: #quit#" << '\n';
  }
  else if(sqlvector[0] == "help"){
    sql_type=20;
    std::cout << "SQL TYPE: #help#" << '\n';
  }
  else if(sqlvector[0] == "create"){
    if (sqlvector[1] == "database") {
      sql_type=30;
      std::cout << "SQL TYPE: #CREATE DATABASE#" << '\n';
    }
    else if (sqlvector[1] == "table") {
      sql_type=31;
      std::cout << "SQL TYPE: #CREATE TABLE#" << '\n';
    }
    else if (sqlvector[1] == "index") {
      sql_type=32;
      std::cout << "SQL TYPE: #CREATE INDEX#" << '\n';
    }
    else {
      sql_type=-1;
    }
  }
  else if(sqlvector[0] == "show"){
    if (sqlvector[1] == "databases") {
      sql_type=40;
      std::cout << "SQL TYPE: #SHOW DATABASES#" << '\n';
    }
    else if (sqlvector[1] == "tables") {
      sql_type=41;
      std::cout << "SQL TYPE: #SHOW TABLES#" << '\n';
    }
    else{
      sql_type=-1;
    }
  }
  else if (sqlvector[0] == "drop") {
		if (sqlvector[1] == "database") {
      sql_type=50;
			std::cout << "SQL TYPE: #DROP DATABASE#" << '\n';
		}
    else if (sqlvector[1] == "table") {
      sql_type=51;
      std::cout << "SQL TYPE: #DROP TABLE#" << '\n';
		}
    else if (sqlvector[1] == "index") {
      sql_type=52;
      std::cout << "SQL TYPE: #DROP INDEX#" << '\n';
		}
    else{
      sql_type=-1;
    }
	}
  else if (sqlvector[0] == "use") {
    sql_type=60;
		std::cout << "SQL TYPE: #USE#" << '\n';
	}
  else if (sqlvector[0] == "insert") {
    sql_type=70;
    std::cout << "SQL TYPE: #INSERT#" << '\n';
  }
  else if (sqlvector[0] == "exec") {
    sql_type=80;
    std::cout << "SQL TYPE: #EXEC#" << '\n';
  }
  else if (sqlvector[0] == "select") {
    sql_type=90;
    std::cout << "SQL TYPE: #SELECT#" << '\n';
  }
  else if (sqlvector[0] == "delete") {
    sql_type=100;
    std::cout << "SQL TYPE: #DELETE#" << '\n';
  }
  else if (sqlvector[0] == "update") {
    sql_type=110;
    std::cout << "SQL TYPE: #UPDATE#" << '\n';
  }
  else {
    sql_type=-1;
    std::cout << "SQL TYPE: #UNKNOWN#" << '\n';
	}
}

void interprete::run() {
  switch (sql_type) {
    case 10:{
      api->quit();
      exit(0);
    }
    case 20:{
      help();
    }
    case 30:{
      std::string name;
      parsedatabase(name,sqlvector);
      api=new database(name);
      break;
    }
    case 31:{
      dictionary dic;
      parsetable(dic,sqlvector);
      api->add_table(dic);
      break;
    }
    //case32
    //case40
    case 41:{
      api->show_table(std::cout);
      break;
    }
    //case50
    //case51
    //case52
    //case60
    case 70: {
      std::vector<Value> val;
      std::string name;
      parseinsert(name,val,sqlvector);
      api->insert_tupla(name,val);
    }
  }
}

void interprete::ExecSQL(std::string itp){
  statement=itp;
  FormatSQL();
  TellSQLType();

  run();
}


#endif
