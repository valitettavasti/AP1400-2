#ifndef Q2_H
#define Q2_H

#include<vector>
#include<iostream>
#include<fstream>

namespace q2
{
    struct Patient
    {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    inline bool sort_func(Patient p1, Patient p2){
        int a = p1.age * 3 + p1.smokes * 5 + p1.area_q * 2 + p1.alkhol * 4;
        int b = p2.age * 3 + p2.smokes * 5 + p2.area_q * 2 + p2.alkhol * 4;
        return a > b;
    }

    inline void sort(std::vector<Patient>& vec_patient){
        std::sort(vec_patient.begin(), vec_patient.end(), sort_func);
    }

    inline std::vector<Patient> read_file(std::string csv_filename)
    {
        std::ifstream  csv_data(csv_filename, std::ios::in);
        if(!csv_data.is_open()){
            std::cout<<"Error: Opening file fail."<<std::endl;
            exit(1);
        }
        std::vector<Patient> vec{};
        std::string line;
        getline(csv_data,line);
        getline(csv_data,line);  //读取标题行
        std::string word;
        while(getline(csv_data, line)){
            std::istringstream iss(line);
            Patient patient{};
            getline(iss, word, ',');   //名字里面有一些有空格,需要去除空格否则可能报错
            word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
            patient.name = word;
            getline(iss, word, ',');
            word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
            patient.name = patient.name +" "+ word;
            getline(iss, word, ',');
            patient.age = static_cast<size_t>(std::stoull(word));
            getline(iss, word, ',');
            patient.smokes = static_cast<size_t>(std::stoull(word));
            getline(iss, word, ',');
            patient.area_q = static_cast<size_t>(std::stoull(word));
            getline(iss, word, ',');
            patient.alkhol = static_cast<size_t>(std::stoull(word));
            vec.push_back(patient);
        }
        return vec;
    }
}

#endif //Q2_H