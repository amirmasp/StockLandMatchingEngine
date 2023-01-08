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

   Format: N &lt;FirmId&gt; &lt;Symbol&gt; &lt;Side&gt; &lt;Price&gt;

   What it does: Places an order for symbol, side, and price for firm &lt;FirmId&gt;

   Each order is for quantity 1

   Only one new order per symbol for each firm(a firm can not have a buy and a sell order for the one symbol)

   New Orders sent for a symbol where a firm already has an existing order will be ignored

* Modify

   Format: M &lt;FirmId&gt; &lt;Symbol&gt; &lt;Price&gt;
   
   What it does: Changes the price of an existing order placed by firm &lt;FirmId&gt; on symbol &lt;Symbol&gt;

   TODO: Newly modified orders take lower precedence (a modified order will be matched after all other all preexisting orders with the same price and side)

* Cancel

   Format: C &lt;FirmId&gt; &lt;Symbol&gt; 

   What it does: Cancels an existing order place by &lt;FirmId&gt; on symbol &lt;Symbol&gt;

## Matching Rules   

1. Only orders from different firms can be matched against each other except StockLand itself

2. The highest Buy order will be matched against the lowest Sell order if the buy price is >= the sell price

3. The firm on the buy side is charged the price listed on the sell order being matched and firm on the sell side is paid the amount listed on the sell order

## Input format:

N (where 1 <= N <= 10000)
Followed by N messages


## Output format:
For each firm that sent at least one New Order, SLME prints a list in increasing order according to FirmId:

&lt;FirmId&gt; &lt;Number of live Orders&gt; &lt;Number of Fills&gt; &lt;Amount paid out to Firm&gt;
   



