#include "MatchingEngine.hpp"

// ***********************************************************************
Order::Order(std::string& symbol, char& side, float& price) {
    this->symbol = symbol;
    this->side = side;
    this->price = price;
    this->priority = 1;
}
// ***********************************************************************

// ***********************************************************************
Order::~Order() {  
    //std::cout <<"Order object deleted\n";
}
// ***********************************************************************

// ***********************************************************************
void MatchingEngine::eraseFilledOrders(int f1, int f2, std::string sym) {
    auto gotF1 = this->data_.find(f1); 
    auto gotF2 = this->data_.find(f2);
       
    for (int i = 0; i < gotF1->second->size(); i++) {
        if (gotF1->second->at(i)->symbol == sym) {  
            auto orPtr =  gotF1->second->at(i);
            // Erase order from firm vector 
            gotF1->second->erase(gotF1->second->begin()+i);  
            // Free up the order memory
            delete orPtr;                                                               
        }        
    }    
    for (int i = 0; i < gotF2->second->size(); i++) {
        if (gotF2->second->at(i)->symbol == sym) {  
            auto orPtr =  gotF2->second->at(i);
            // Erase order from firm vector 
            gotF2->second->erase(gotF2->second->begin()+i);  
            // Free up the order memory
            delete orPtr;                                                                
        }        
    } 
}
// ***********************************************************************

// ***********************************************************************
void MatchingEngine::matchingOrders(Order* order, int firm) {
    std::vector<std::pair<float, int>> prices;
    std::string sym = order->symbol;
    for (auto f: this->data_) {
    // Only orders from different firms can be matched against each other
        if ((int)f.first != firm) { 
            for (auto o: *f.second) {// Iterate into the firm orders                
                if (o->symbol == order->symbol && o->side != order->side) {                    
                    if (order->side == 'B') {                      
                        if (order->price >= o->price) {//be matched                          
                            prices.push_back(std::make_pair(o->price, f.first));                                                      
                        }                       
                    }                    
                    else if (order->side == 'S') {                       
                        if (order->price <= o->price) {                         
                            prices.push_back(std::make_pair(o->price, f.first));                            
                        }                      
                    }
                }
            }           
        }
    }
    std::sort(prices.begin(), prices.end());
    if (prices.size() > 0) {
        if (order->side == 'S') {
            // (seller, symbol, <highest buyer price, buyer>, side)
            MatchingEngine::executeOrder(firm, sym, prices.back(), 'S',order->price);
        }
        else if (order->side == 'B') {
            // (buyer, symbol, <lowest seller price , seller> side)
            MatchingEngine::executeOrder(firm, sym, prices.front(), 'B'); 
        }
    }    
}
// ***********************************************************************

// ***********************************************************************
void MatchingEngine::executeOrder(int firm, std::string symbol,
     std::pair<float, int> p, char side, float sellPrice) {   
    if (side == 'B') {
        auto gotBuyer = this->updateTable.find(firm);
        gotBuyer->second.first++;// Add a filled order
        gotBuyer->second.second -= p.first;
        auto gotSeller = this->updateTable.find(p.second);
        gotSeller->second.first++;
        gotSeller->second.second += p.first;
        this->eraseFilledOrders(firm, p.second, symbol);
    }
    else if (side == 'S') {
        auto gotSeller = this->updateTable.find(firm);
        gotSeller->second.first++;
        gotSeller->second.second += sellPrice;
        auto gotBuyer = this->updateTable.find(p.second);
        gotBuyer->second.first++;
        gotBuyer->second.second -= sellPrice;
        this->eraseFilledOrders(firm, p.second, symbol);
    }      
}
// ***********************************************************************

// Places an order for symbol, side, and price for firm
// ***********************************************************************
void MatchingEngine::onNewOrder(uint16_t firmId, std::string symbol, char side, float price) {
    // Allocate memory for new order
    Order* newOrder = new Order(symbol, side, price);
    auto got = this->data_.find(firmId); // Looking for firm in data_
    if (got == this->data_.end()) { // If firm does not exist in data_
        // Allocate memory for firm
        std::vector<Order*>* valVector = new std::vector<Order*>();
        valVector->push_back(newOrder);
        this->data_.emplace(firmId, valVector);
        this->updateTable.emplace(firmId, std::make_pair(0, 0.0));
    }
    else {// firm exists in data_
        // Only one new order per symbol for each firm
        for (auto order: *got->second) {
            if (order->symbol == symbol) {
                return; // Do not add new order 
            }
        }
        // Add new order to firm vector
        got->second->push_back(newOrder);
    }
    MatchingEngine::matchingOrders(newOrder, (int)firmId);
}
// ***********************************************************************

// Changes the price of an existing order 
// ***********************************************************************
void MatchingEngine::onModify(uint16_t firmId, std::string symbol, float price) {
    // Looking for firm in db
    auto got = this->data_.find(firmId); 
    // If firm does not exist in db ignore the order
    if (got == this->data_.end()) { 
        return;
    }
    else {// firm exists
        for (auto order: *got->second) {
            if (order->symbol == symbol)  {// symbol exists in an order
                order->price = price; // Update price
                order->priority = 0; // Lower precedence 
                MatchingEngine::matchingOrders(order, (int)firmId);
            }
        } 
    }   
}
// ***********************************************************************

// Cancels an existing order
// ***********************************************************************
void MatchingEngine::onCancel(uint16_t firmId, std::string symbol) {
    auto got = this->data_.find(firmId); 
    // If firm does not exist in db ignore the order
    if (got == this->data_.end()) { 
        //std::cout << "Firm not found for cancel order\n";
        return;
    }
    else {// firm exists
        for (int i = 0; i < got->second->size(); i++) {
            if (got->second->at(i)->symbol == symbol) {  
                auto orPtr =  got->second->at(i);
                // Erase order from firm vector 
                got->second->erase(got->second->begin()+i);  
                // Free up the order memory
                delete orPtr;
                                                               
                return;
            }        
        }     
    }
}
// ***********************************************************************

// ***********************************************************************
void MatchingEngine::print() {
    for (auto it: this->updateTable) {
        auto got = this->data_.find(it.first);
        std::cout << got->first << " " << got->second->size()
            << " " << it.second.first << " " << it.second.second << std::endl;              
    }    
}
// *************************************************************************