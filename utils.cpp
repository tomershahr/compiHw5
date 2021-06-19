//
// Created by Chen on 18/06/2021.
//

#include <string>
#include <iostream>
using namespace std;



class Info {
    int reg_index =0;
    int label_index =0;
    Info(){}

public:
    static Info& instance(){
        static Info inst;//only instance
        return inst;
    }

    string newReg(){
        return "%reg"+ to_string(reg_index++);
    }

    string newLabel(){
        return "label_"+to_string(label_index++);
    }



};