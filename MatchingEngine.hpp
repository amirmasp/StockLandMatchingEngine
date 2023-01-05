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
    ~Order();
    char side;
    std::string symbol;
    float price;
    unsigned int priority;
};

class MatchingEngine{
    public:
    // use of these functions are not required
    void onNewOrder(uint16_t, std::string, char, float);
    void onModify(uint16_t, std::string, float); 
    void onCancel(uint16_t, std::string);
    void print();

    private:
    // <Number of live Orders> is the vector size in data_
    std::unordered_map<uint16_t, std::vector<Order*>*> data_;
    // updateTable records <Number of fills>  and  <Amount paid out to Firm>
    std::map<uint16_t, std::pair<unsigned int, float>> updateTable;
    void executeOrder(int, std::string, std::pair<float, int>, char, float=0);
    void eraseFilledOrders(int, int, std::string);
    void matchingOrders(Order*, int);    
};

#endif






