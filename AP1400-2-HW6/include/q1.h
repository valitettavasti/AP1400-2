#ifndef Q1_H
#define Q1_H

#include<functional>
#include<iostream>

namespace q1
{
    template<typename Callable>
    double gradient(double x, Callable func);

    // 使用函数指针作为参数传入 
    //本来应该定义 double (*func)(double),std::function<double(double)> func等
    //使用callFunction模板函数可以接受任何类型的可调用对象，包括函数、函数指针、std::function对象和Lambda表达式
    template<typename T = double, typename Callable>
    double gradient_descent(double initial_value, double step_value, Callable func=Callable{}){
        while(true)     //多种退出条件,可以是次数,前后两次算出的值的差值,grad(梯度)的值
            {
                auto grad = gradient(initial_value, func);
                initial_value = initial_value - step_value * grad;
                if(grad>-1e-8 && grad<1e-8){
                    break;
                }
            }
        return initial_value;
    }

    //计算该点的数值微分方法
    //中心微商公式: f'(x)=(f(x+h)-f(x-h))/2h
    template<typename Callable>
    double gradient(double x, Callable func){
        double h = 0.01;
        return (func(x + h) - func(x - h)) / (2 * h);
    }
}
#endif //Q1_H