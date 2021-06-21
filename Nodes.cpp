//
// Created by tomer on 5/21/2021.
//

#ifndef HW3_NODES_HPP
#define HW3_NODES_HPP
#define YYSTYPE Node*
#include <string>
#include <vector>
#include <iostream>
using namespace std;




//--------------------------------classes--------------------------//
class Node{
public:
    string reg;
    Node():reg(""){};
};

class Num : public Node{
public:
    int value;
    Num(string val): Node(), value(stoi(val)){}

};

 class Statement : public Node{
 public:
     vector<pair<int,BranchLabelIndex>> next_list;
     Statement(): Node(), next_list(){}
 };

class BinOp : public Node{
public:
    string op;
    BinOp(string val):Node(), op(val){}
};


class Id : public Node{
public:
    string name;
    Id(string in_name) : Node(), name(in_name){}
};


class Type : public Node{
public:
    string type;
    vector<pair<int, BranchLabelIndex>> true_list;
    vector<pair<int, BranchLabelIndex>> false_list;
    Type(string in_type):Node(), type(in_type),true_list(),false_list(){}
    //Type(string in_type):Node(), type(in_type),true_list(true_list){}

};




class String : public Type{
public:
    string value;
    String(string value):Type("STRING"), value(value){}
};



class Marker : public Node{
public:
    string quad;
    Marker(string quad):Node(),quad(quad){}
};

/*
class Binop : public Node{
public:
    char* operation;
    Binop(char* operation): Node(), operation(operation){}
};*/


class Relop : public Node{
public:
    string relop_op;
    Relop(string relop_op): Node(), relop_op(relop_op){}
};

class  Arguments: public Node{

public:
    vector<string> types;
    vector<string> names;

    Arguments(Node* n_type,Node* n_id): Node(),types(),names(){
        Type* type = (Type*)n_type;
        Id* id = (Id*)n_id;
        types.push_back(type->type);
        names.push_back(id->name);
    }

    Arguments* merge(Node * node){
        Arguments* a2 = (Arguments*)node;
        this->types.insert(this->types.end(), a2->types.begin(), a2->types.end());
        this->names.insert(this->names.end(), a2->names.begin(), a2->names.end());
        return this;
    }
};

class ExpList: public Node{
public:
    vector<string> types;

    ExpList(Node* type): Node(), types(){
        string name = ((Type*)type)->type;
        types.push_back(name);
    }

    ExpList* merge(Node* node){
        ExpList* a2 = (ExpList*) node;
        this->types.insert(this->types.end(), a2->types.begin(), a2->types.end());
        return this;
    }
};

#endif //HW3_NODES_HPP
