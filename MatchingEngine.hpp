#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <utility>
#include <map>
#include <algorithm>

struct Order {   
    Order(std::string& symbol, char& side, float& price);       
    ~Order() = default;
    char side;
    std::string symbol;
    float price;
    unsigned int priority;
};

class MatchingEngine{
    public:
    void onNewOrder(uint16_t, std::string, char, float);
    void onModify(uint16_t, std::string, float); 
    void onCancel(uint16_t, std::string);
    void print();

    private:
    std::unordered_map<uint16_t, std::vector<Order*>*> data_;
    std::map<uint16_t, std::pair<unsigned int, float>> updateTable;
    void executeOrder(int, std::string, std::pair<float, int>, char, float=0);
    void eraseFilledOrders(int, int, std::string);
    void matchingOrders(Order*, int);    
};

#endif






