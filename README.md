# Event-based Simulation of Simplified DLT (Distributed Ledger Technology)
This project implements an event-based simulation of an extremely simplified Distributed Ledger Technology (DLT). The simulation involves players (customers A, B, C, D, miners E1, and E2) participating in transactions that are recorded in a blockchain-like structure. The main goal is to evaluate the performance of the DLT system under various conditions.

The simulation follows the following pseudo-code for C++ Implementation:

## Initiate System Definitions and Status:

Customers A, B, C, D, and miners E1, E2 are defined.
A linked list (blockchain) maintained by miners contains the ledger.
Each list item is a block containing at most 4 valid transactions (one per customer).
Customers have initial balances of D Dollars and B Bitcoins.
Each customer maintains its own current ledger, open for miners' inspection.
Transactions T0 (customer u buys x Bitcoins from customer z for y Dollars) and T1 (null transaction) are defined.
A limit is set on the number of events, and transactions are generated using a C++ uniform PRNG.

## Generate Events:
Random time increments are chosen for the next event.
Events for each customer are generated and queued in an Event Queue (Q).
Only one transaction request per customer per timed event is allowed.
Transaction requests are recorded in a .csv event file.

## Infinite Loop on Events:
Each miner reads the next set of events for the next time unit from the event-queue.
For each request, the miners check the validity (sufficient funds) and add valid requests to a current tentative block.
Transaction requests are recorded in a .csv requests-file.
Miners compete using Proof of Elapsed Time (PoET) to add valid blocks to the blockchain.
The winning miner adds its block to the chain.
Chain status (only the "delta") is recorded in a .csv chain-file.
The system checks for the termination condition (empty event file).

## Evaluate Statistics:
The average number of transaction attempts and successful chain constructions per miner per time unit are evaluated.
