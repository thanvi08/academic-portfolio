// Name : Thanvitha Kanumathi Reddy
// Student ID: A05147989
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include<queue>

using namespace std;
struct Ledger {
  int CustomerID;
  int Balance;
  int Bitcoins;
  string state;
  int eventtime;
  int SellerCustID;
  bool isSelling = false;
};
list<Ledger> Customer;

Ledger Customers[] = {
    {1, 500, 50}, {2, 500, 50}, {3, 500, 50}, {4, 500, 50}};

int tick = 0;

queue<Ledger> Q;
bool areCustomersInQueue = false;

/*************************************************/


string getFrienndlyCustomerName(int custID) {
  if (custID == 1) {
    return "CustomerA";
  }
  if (custID == 2) {
    return "CustomerB";
  }
  if (custID == 3) {
    return "CustomerC";
  }
  if (custID == 4) {
    return "CustomerD";
  }
}
fstream eventfile;
fstream requestfile;
fstream chainfile;
/**************************************************/
bool isValidTransaction(Ledger gl) {
  if(gl.state=="Buy" && gl.Balance  >= 20) {
    int id2 = (gl.CustomerID + 1)%4;
    if(Customers[id2-1].Bitcoins >= 5) {
      Customers[gl.CustomerID-1].SellerCustID = id2; 
      return true;
    }
  }
  return false;
}


/****************************************************/

/******************************************************/

int main() {
  eventfile.open("01eventfile.csv", ios::out | ios::trunc);
  eventfile << "Tick "
        << ","
        << "Customer ID"
        << ","
        << "State" << endl;

   requestfile.open("02requestfile.csv", ios::out | ios::trunc);
   requestfile << "Tick "
        << ","
        << "Customer ID"
        << ","
        <<"Transaction Status"
        <<","
        << "With" << endl;

  chainfile.open("03chainfile.csv", ios::out | ios::trunc);
   chainfile << "Tick "
        << ","
        << "Customer ID"
        << ","
        << "Miner"
        <<","
        << "With" << endl;

  while (1) {

    tick++;  
    if (Customer.size() == 0) {
      areCustomersInQueue = false;
      Customer.push_front(Customers[0]);
      Customer.push_front(Customers[1]);
      Customer.push_front(Customers[2]);
      Customer.push_front(Customers[3]);

        int P1 = (int)rand() % 10 + 1 + tick;
     // cout<<P1<<endl;
      for (Ledger gl : Customer) {
        Customers[gl.CustomerID - 1].eventtime = P1;
        float P = (float)rand()/RAND_MAX;
        if (P <= 0.25) {
          Customers[gl.CustomerID - 1].state = "Buy";
          } else if (P>0.25 && P<= 1.00){
          Customers[gl.CustomerID- 1].state = "Null Transaction";
          } else {
          cout << "nope" << P <<endl;
          }
          // generate first event file in below formst
           eventfile << Customers[gl.CustomerID - 1].eventtime << "," << Customers[gl.CustomerID - 1].CustomerID << "," << Customers[gl.CustomerID - 1].state <<endl;
        //cout<< Customers[gl.CustomerID - 1].eventtime << "," << Customers[gl.CustomerID - 1].CustomerID << "," << Customers[gl.CustomerID - 1].state <<endl;
        }
    }
    /****************************************************/
    list<Ledger> currentTentativeBlock;
    if (Customer.size() > 0 && ! areCustomersInQueue) {
   
      for (Ledger gl : Customer) {
        //if (Customers[gl.CustomerID - 1].eventtime != tick) {
          // isValidTransaction method sees if the transaction is Buy, then it           // validates the Buy
          if(isValidTransaction(gl)) {
            areCustomersInQueue = true;
            currentTentativeBlock.push_front(gl);
            requestfile << tick << "," << Customers[gl.CustomerID - 1].CustomerID <<" with " <<Customers[gl.CustomerID - 1].SellerCustID << "," << "Valid Transaction" << endl;
      //  cout<< tick << "," << Customers[gl.CustomerID - 1].CustomerID <<" with " <<Customers[gl.CustomerID - 1].SellerCustID << "," << "Valid Transaction" << endl;
            
          } else {
          requestfile << tick << "," << Customers[gl.CustomerID - 1].CustomerID << "," << "Invalid Transaction" << "," << "" << "-->" << tick << endl;
      //  cout<< tick << "," << Customers[gl.CustomerID - 1].CustomerID << "," << "Invalid Transaction" << "," << "" << "-->" << tick << endl;
         // Q.push(Tar)
  
          }
        //} 
      }
      Customer = currentTentativeBlock;
    }

    if(Customer.size() > 0 && areCustomersInQueue) {
      for(Ledger gl : Customer) {
        if (Customers[gl.CustomerID - 1].eventtime == tick) {
          // here is where the miners compete against PoET time
          float E1PoETTime = (float)rand()/RAND_MAX;;
          float E2PoETTime = (float)rand()/RAND_MAX;;
                      // Perform Transaction
            int buyer = gl.CustomerID;
            int seller = gl.SellerCustID;
            Customers[buyer-1].Balance = Customers[buyer-1].Balance-20;
            Customers[buyer-1].Bitcoins = Customers[buyer-1].Bitcoins+5;

            Customers[seller-1].Balance = Customers[seller-1].Balance+20;
            Customers[seller-1].Bitcoins = Customers[seller-1].Bitcoins-5;
          if(E1PoETTime > E2PoETTime) {
            chainfile << Customers[gl.CustomerID - 1].eventtime << "," << Customers[gl.CustomerID - 1].CustomerID << "," << "E1 Miner" << "," << Customers[gl.CustomerID - 1].CustomerID <<" with " <<Customers[gl.CustomerID - 1].SellerCustID <<endl;
       // cout << Customers[gl.CustomerID - 1].eventtime << "," << Customers[gl.CustomerID - 1].CustomerID << "," << "E1 Miner" << "," << Customers[gl.CustomerID - 1].CustomerID <<" with " <<Customers[gl.CustomerID - 1].SellerCustID <<endl;
          } else {
            chainfile << Customers[gl.CustomerID - 1].eventtime << "," << Customers[gl.CustomerID - 1].CustomerID << "," << "E2 Miner" << "," << Customers[gl.CustomerID - 1].CustomerID <<" with " <<Customers[gl.CustomerID - 1].SellerCustID <<endl;
      // cout << Customers[gl.CustomerID - 1].eventtime << "," << Customers[gl.CustomerID - 1].CustomerID << "," << "E2 Miner" << "," << Customers[gl.CustomerID - 1].CustomerID <<" with " <<Customers[gl.CustomerID - 1].SellerCustID <<endl;
          }

          
          areCustomersInQueue = false;
        }
      }
    }
    if(! areCustomersInQueue) {
      list<Ledger> tempEmptyList;
      Customer = tempEmptyList;
    }
    //Transactions(gl, tick);
    if (tick >=2000) 
    {
      break;
    }
  }

  return 0;
}




