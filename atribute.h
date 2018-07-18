#ifndef ATRIBUTE_H
#define ATRIBUTE_H

class attribute {
private:
  std::string name;
  int data_type;
public:
  attribute ():
    name(""),
    data_type(-1){};

  std::string get_name(){ return name;};
  void set_name(std::string _name) {
    name=_name;
  }
  int get_data_type(){ return data_type;};
  void set_data_type(int _type) {
    data_type=_type;
  }

  bool operator ==(attribute &a){
    return name==a.name;
  }

  friend std::ostream& operator<<(std::ostream &out,const attribute &a){
    out<<a.name;
    return out;
  }
  //virtual ~attribute ();
};

#endif
