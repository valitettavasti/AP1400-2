#ifndef Q4_H
#define Q4_H

#include <vector>
#include <iostream>

namespace q4{
    struct Vector2D
    {
        double x{};
        double y{};
        Vector2D():x(0), y(0){}
        Vector2D(double xx, double yy){
            x = xx;
            y = yy;
        }
    };

    struct Sensor
    {
        Vector2D pos;
        double accuracy;
        Sensor(Vector2D p, double acc) : pos(p), accuracy(acc) {}
        Sensor(double x, double y, double acc) : pos(Vector2D(x, y)), accuracy(acc) {}
    };

    inline Vector2D kalman_filter(std::vector<Sensor> sensors)
    {
        double sum = 0;
        for(auto sensor:sensors){
            sum += sensor.accuracy;
        }
        std::vector<double> weight;
        for(auto sensor:sensors){
            weight.push_back(sensor.accuracy / sum);
        }
        double X = 0;
        for(int i = 0; i<weight.size(); i++){
            X += weight[i] * sensors[i].pos.x;
        }
        double Y = 0;
        for(int i = 0; i<weight.size(); i++){
            Y += weight[i] * sensors[i].pos.y;
        }
        return Vector2D(X, Y);
    }
    
}
#endif //Q4_H