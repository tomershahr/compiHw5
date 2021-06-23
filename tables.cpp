#include <string>
#include <vector>
#include <iostream>
#include "hw3_output.hpp"
#include "bp.hpp"
enum scope_type{regular_scope,while_scope,switch_scope};
using namespace std;
using namespace output;


class Entry{
public:
    string name;
    string type;
    int offset;
    vector<string> args_types;
    bool is_func;
    string loc;

    Entry(){}
    Entry(string _name,string _type,int _offset, string loc="") : name(_name), type(_type), offset(_offset), args_types(vector<string>()),  is_func(false), loc(loc){} //for varible

    Entry(string _name,string _type, vector<string> args): name(_name), type(_type), offset(0), args_types(args), is_func(true){} //for func
    Entry& operator=(const Entry& e){

        this->name = e.name;
        this->type = e.type;
        this->offset = e.offset;
        this->args_types = e.args_types;
        this->is_func = e.is_func;

        return *this;
    }


};

/*
class FuncEntry: public Entry{
public:
    vector<string> args_types;
    FuncEntry(string name,string type, vector<string> a_types)
            :Entry(name,type,0),args_types(a_types){this->is_func= true;}
};
*/

typedef vector<Entry> Table;

class SymbolTables{
    int curr_func_offset;
    vector<Table> tables;
    vector<int> offsets;
    int while_number;
    int switch_number;
    vector <string> while_lbls;
    vector<vector<pair<int,BranchLabelIndex>>> while_breaks;

public:
    SymbolTables(): curr_func_offset(0),while_number(0),switch_number(0), while_lbls(), while_breaks(){
        Table global;
        global.push_back(Entry("print", "VOID",vector<string>(1, "STRING")));
        global.push_back(Entry("printi", "VOID",vector<string>(1, "INT")));
        tables.push_back(global);
        offsets.push_back(0);


    }

    void insertEntry( string name, string type, string loc){
        int curr = offsets.back();
        tables[tables.size()-1].push_back(Entry(name, type, curr,loc));
        offsets[offsets.size()-1]= curr+1;

    }

    void insertFuncArgEntry( string name, string type){
        tables[tables.size()-1].push_back(Entry(name, type, curr_func_offset--));
    }

    void insertFuncEntry(string name, string type, vector<string> args){
        tables[tables.size()-1].push_back(Entry(name, type, args));
        offsets.push_back(offsets.back());
        tables.push_back(Table());
        curr_func_offset =-1;
    }

    bool findSymbol(string name,Entry* entry=nullptr){
        for(unsigned int j =0;j<tables.size();j++) {
            Table curr = tables[j];
            for (unsigned int i = 0; i < curr.size(); i++) {
                if (curr[i].name.compare(name) == 0){
                    if(entry!=nullptr){
                        *entry = curr[i];
                    }
                    return true;
                }
            }
        }
        return false;
    }

    string getSymbolType(string symbol){
        for(unsigned int j =0;j<tables.size();j++) {
            Table curr = tables[j];
            for (unsigned int i = 0; i < curr.size(); i++) {
                if (curr[i].name.compare(symbol) == 0)
                    return curr[i].type;
            }
        }
        return "";
    }

    vector<string> getFuncArgs(string func){
        for(unsigned int j =0;j<tables.size();j++) {
            Table curr = tables[j];
            for (unsigned int i = 0; i < curr.size(); i++) {
                if (curr[i].name.compare(func) == 0)
                    return curr[i].args_types;
            }
        }
        return vector<string>();
    }
/*
    bool isValidMain(){

        for(unsigned int i= 0; i<tables[0].size();i++){
            if (tables[0][i].name.compare("main"){
                if(!tables[0][i].type.compare("VOID") || !tables[0][i].args_types.empty())
                    return false;
                return true;
            }
        }
        return false;
    }
    */

    void openScope(scope_type scope_type){
        if(scope_type == while_scope)
            while_number++;
        if(scope_type == switch_scope)
            switch_number++;
        tables.push_back(Table());
        offsets.push_back(offsets.back());
    }


    void closeScope(scope_type scope_type){
        if(scope_type == while_scope)
            while_number--;
        if(scope_type == switch_scope)
            switch_number--;
        //endScope();
        Table table = tables.back();
        for(unsigned int i=0; i< table.size(); i++){
            string name = table[i].name;
            string types =  table[i].type;
            if(table[i].is_func){
                vector<string> args = getFuncArgs(name);
                types = makeFunctionType(types, args);
            }
            // printID(name , table[i].offset, types);
        }
        offsets.pop_back();
        tables.pop_back();
    }

    bool insideWhile(){
        if(while_number>0)
            return true;
        return false;
    }

    bool insideSwitch(){
        if(switch_number>0)
            return true;
        return false;
    }

    int currentOffset(){
        return offsets.back()-1;
    }
    ////funcs to continue && break
    void addWhileLbl(string lbl){
        while_lbls.push_back(lbl);
        while_breaks.push_back(vector<pair<int,BranchLabelIndex>>());
    }
    vector<pair<int,BranchLabelIndex>> removeWhileLbl(){
        while_lbls.pop_back();
        vector<pair<int,BranchLabelIndex>> res = while_breaks.back();
        while_breaks.pop_back();
        return res;
    }
    string& getLastWhileLbl(){
        return while_lbls.back();
    }
    void add_break(int loc){
        while_breaks.back().push_back(pair<int,BranchLabelIndex>(loc, FIRST));
    }

};
