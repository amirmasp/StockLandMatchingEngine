#include "MatchingEngine.hpp"

using namespace std;

int main() {

    MatchingEngine me;
    uint16_t N = 0;

    cin >> N;
    
    char orderType;
    uint16_t firmId;
    string symbol;
    char side;
    float price;

    for (size_t i = 0; i < N; i++)
    {
        std::cin >> orderType >> firmId >> symbol;  
        
        switch (orderType)
        {
            case 'N':
                std::cin >> side >> price;
                me.onNewOrder(firmId, symbol, side, price);
            break;
            case 'M':
                std::cin >> price;               
                me.onModify(firmId, symbol, price);
            break;
            case 'C':
                me.onCancel(firmId, symbol);
            break;
            default:
            break;
        }
    }

    me.print();
    return 0;     
}
