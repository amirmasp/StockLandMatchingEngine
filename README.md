# StockLandMatchingEngine(SLME)
This program is an 'Order Matching System' developed by `amirmasp` as a seperate module that will be integrated to the [StockLand Exchange Application](https://github.com/amirmasp/StockLandFinal) .

Note: Suppose also other market makers (firms) send their orders to StockLand Exchange and expect us to keep track of their orders and execute them properly.


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

## Compile & Run:
`g++ main.cpp MatchingEngine.cpp -o main` 
`./main`

### Example Input:
`7`  
`N 5172 APPL B 1500.50`  
`N 5172 CME S 500.5`  
`N 6445 APPL S 1500.51`  
`N 5172 VIRT B 100.35`  
`N 6466 APPL S 1500.49`  
`M 6445 APPL  1500.48`  
`C 6445 APPL`  

### Corresponding Output:
`5172 2 1 -1500.50`  
`6445 0 0 0`  
`6466 0 1 1500.49`

### Reasoning

Firm 5172 places two orders, one buy and one sell for APPL and CME respectively.
Firm 6445 places a sell order for APPL, which does not execute since its sell price is higher than the existing buy order for APPL.
Firm 5172 places a buy order for VIRT.
Firm 6466 places a sell order for APPL with a price less than the existing APPL buy order. The 6466 APPL sell order is matched with the 5172 APPL buy order, and both orders are removed (no longer live).
Firm 6445 modifies their existing APPL order -- nothing happens as there is no buy order for the symbol.
Firm 6445 cancels their existing APPL order.


   



