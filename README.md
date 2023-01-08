# StockLandMatchingEngine(SLME)
This program is an 'Order Matching System' developed by `amirmasp` as a seperate module that will be integrated to the [StockLand Exchange Application](https://github.com/amirmasp/StockLandFinal) .




## StockLand Exchange

Assume Also other market makers (firms) send their orders to StockLand  Exchange and expect it to keep track of their orders and execute them properly.

Here in our simulation app we shows how a matching engine at an exchange(StockLand) works.

## Instruction:
Given a set of messages from multiple firms in sequential order, SLME keeps track of orders and matches them properly. After proceessing all messages, outputs the number of live orders(new orders that were not cancelled or filled), the number of fills, and total balance of each firm that sent at least one new order.

## Fields:
* OrderType: Char in {N, M, C}

   Represents whether a line is for a New Order, Modify Order, Cancel Order.

* FirmId: Int (4 digit number)

   Represents aunique id for each participating firm.
* Sybmol: Char[6]

   Represents names of equities(i.e. TSLA, NIO).

* Side: Char in {B, S}

   Represents whether an order is on the Buy or Sell side.

* Price: Float32   

## Type of Messages:
* New Order

   Format: N <FirmId> <Symbol> <Side> <Price>

   What it does: Places an order for symbol, side, and price for firm <FirmId>



