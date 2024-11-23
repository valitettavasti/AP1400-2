#ifndef Q3_H
#define Q3_H

#include<queue>
#include<iostream>
#include<fstream>
#include<regex>

namespace q3{
    struct Flight
    {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };

    inline size_t timeToMinutes(const std::string& time)
    {
        std::regex time_regex("(\\d+)h(\\d*)m*"); 
        std::smatch match;
        if (std::regex_match(time, match, time_regex)) {
            int hours = std::stoi(match[1]);
            // 检查是否有分钟部分，如果没有则默认为0
            int minutes =0;
            if(match[2]!=""){
                minutes = std::stoi(match[2]);
            }
            
            return size_t (hours * 60 + minutes);
        } else {
           std::cout << "Unmatched time: " << time << std::endl;
           return 0;
        }
    }

    inline size_t totalConnectionTimes(const std::string& connection_times) {
        std::vector<std::string> res;
        std::string cur = "";
        for (const char ch : connection_times) {
            if (ch != ',')
                cur.push_back(ch);
            else {
                res.push_back(cur);
                cur = "";
            }
        }
        res.push_back(cur);
        size_t total_minutes=0;
        for(auto time:res){
            total_minutes += timeToMinutes(time);
        }
        return total_minutes;
    }

    struct CompareFlight {
        bool operator()(const Flight& f1, const Flight& f2) const {
            int a = f1.duration + f1.connection_times + 3 * f1.price;
            int b = f2.duration + f2.connection_times + 3 * f2.price;
            return a > b;
        }
    };
    
    inline std::priority_queue<Flight,std::vector<Flight>,  CompareFlight> gather_flights(std::string filename){
        std::ifstream data(filename, std::ios::in);
        if(!data.is_open()){
            std::cout<<"Error: Opening file fail."<<std::endl;
            exit(1);
        }
        std::priority_queue<Flight,std::vector<Flight>, CompareFlight> que;
        std::string line;
        std::regex pattern( R"(\d- flight_number:(.+) - duration:(.+) - connections:(\d+) - connection_times:(.+) - price:(\d+))");
        while(getline(data, line)){
            std::smatch match;
            if(std::regex_match(line,match,pattern)){
                Flight flight{};
                flight.flight_number = match[1];
                flight.duration = timeToMinutes(match[2]);
                flight.connections =  static_cast<size_t>(std::stoull(match[3]));
                flight.connection_times = totalConnectionTimes(match[4]);
                flight.price = static_cast<size_t>(std::stoull(match[5]));
                que.push(flight);
            } else {
                std::cout << "Unmatched line: " << line << std::endl; // 输出未匹配的行
            }
        } 
        return que; 
    }
}
#endif //Q3_H