#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Product.h"
using namespace std;

//prototypes
int numFiles(string fileName);
void readFiles(string fileName, Product *products, int recordCount);
void displayFile(Product *products, int recordCount);
int findPlu(Product *products, int recordCount, string plu);
void menuDisplay();

int numFiles(string fileName)
{
    ifstream inputFile(fileName); //open file
    string line; //vari to hold line
    //set count vari
    int count = 0;

    if(inputFile)
    { //parse through entire file
        while(getline(inputFile,line))
        {
            count++;
        }
        inputFile.close(); // Always close the file
        return count;
    }
    else
    {
        return -1; //will stop program
    }

}

void readFiles(string fileName, Product *products, int recordCount)
{
    //open file
    ifstream inputFile(fileName);
    //varis to store
    string plu;
     string name;
     int type;
     double price;
    int inventory;
    //loop to set products varis
    for (int i =0;i < recordCount;i++)
    {
        inputFile >> plu >> name >> type >> price >> inventory;

        products[i].setProductAttributes(plu,name,type,price,inventory);

    }
    inputFile.close();
}

void displayFile(Product *products, int recordCount)
{
    //make varis to store
    string plu;
    string name;
    int type;
    double price;
    int inventory;
    //loop using number of records to set varis

    for(int i = 0;i < recordCount;i++)
    {
        plu = products[i].getPLU();
        name = products[i].getName();
        type = products[i].getType();
        price = products[i].getPrice();
        inventory = products[i].getInventory();

        //start to print out setw(5) for price
        cout << "PLU: " << plu << ", " << left << setw(17) << name << ", type: " << type << ", unit price: " << right << setw(5) << price << ", inventory: " << inventory << endl;
    }
}

void menuDisplay()
{
    //display menu
    cout << "\nMenu\n";
    cout << "----\n";
    cout << "1->Add to inventory           , 2->Subtract from inventory\n";
    cout << "3->Print info for all products, 4->Exit\n";


}

int findPlu(Product *products, int recordCount, string plu)
{
    for (int i =0;i < recordCount;i++) //parse through plus to find
    {
        if(products[i].getPLU() == plu)
        {
            return i; //return index
        }
    }
    return -1; //means none found
}

int main()
{
    //prompt user for record name
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;

    int ecCount = -1; //extra credit vari to keep count of trans
    int ecIndex[100] = {0}; //will keep an array of trans indexs
    string ecType[100]; //parallel array to ecIndex that will keep the types
    int ecAmounts[100] = {0}; //store inv
    
    //open file in numFiles() and do input vali while counting number of records
    int recordCount = numFiles(fileName);
    
    if (recordCount == -1)
    {
        cout << "Error, file did not open";
        return 0;
    }
    else
    {
        cout << "There are " << recordCount  << " records in the file" << endl;
    }

    //create array of Product objects
    Product *products = new Product[recordCount];

    //read in data from file and assign using the mutator function 
    readFiles(fileName, products, recordCount);

    //display product
    cout << "\nContent of object array\n";
    cout << "-----------------------\n";
    displayFile(products, recordCount);

    

    //varis for menu
    string plu = "";
    int index = 0;

    
    //infinite while loop for menu 
    while(true && index !=-999) //exit case
    {
        //display menu and store choice
        menuDisplay();
        int menuChoice;
        cin >> menuChoice;
        switch (menuChoice)
    {
    
    case 1: //add
        {
            cout << "Enter the PLU: "; //prompt and store plu
            cin >> plu;
            index = findPlu(products, recordCount, plu);
            if(index == -1)
            {
                cout << "PLU not found\n";
                break;

            }
            else
            {
                int amount;
                cout << "Enter amount to add: ";
                cin >> amount;
                if (amount > 0)
                {
                products[index].setInventory(products[index].getInventory() + amount);
                ecCount++; //increment count for trans
                ecIndex[ecCount] = index;
                ecType[ecCount] = "Add to inventory";
                ecAmounts[ecCount] = amount; // Store the amount
                }
                else
                cout << "Amount must be > 0\n";
            }
            break;
        }
    case 2: //subtract
        {
            cout << "Enter the PLU: "; //prompt and store plu
            cin >> plu;
            index = findPlu(products, recordCount, plu);
            if(index == -1)
            {
                cout << "PLU not found\n";
                break;

            }
            else
            {
                int amount;
                cout << "Enter amount to subtract: ";
                cin >> amount;
                if (amount > 0)
                {
                products[index].setInventory(products[index].getInventory() - amount);
                ecCount++;
                ecIndex[ecCount] = index;
                ecType[ecCount] = "Subtract from inventory";
                ecAmounts[ecCount] = amount; // Store the amount
                }
                else
                cout << "Amount must be > 0\n";

                if(products[index].getInventory() < 0)
                {
                    ecAmounts[ecCount] = products[index].getInventory() + amount; // Store the amount when subtratcion results in negative numbers
                    products[index].setInventory(0); //if negative inventory, set to 0
                    
                }
            }
            break;
        }
    case 3: //print info
        {
                cout << "Current inventory\n";
                cout << "-----------------\n";
                displayFile(products, recordCount);
            break;
        }
    case 4:
        {
            index = -999;

            //extra credit 
            cout << "\nHistory of transactions\n-----------------------\n";
            
            // Calculate starting point to avoid negative indices
            int start = max(0, ecCount - 4);  // Change from ecCount - 5 to ecCount - 4
            
            for(int i = ecCount; i >= start; i--)
            { 
                if (i >= 0) {  //make sure we dont leave array bounds
                    cout << "Transaction #: " << i + 1 << ", PLU: " << products[ecIndex[i]].getPLU()  << ", type: " << ecType[i]  << ", amount: " << ecAmounts[i] << endl;
                }
            }
            break;
        }
    default:
        {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    } // End of while loop
    
    delete[] products; // Free allocated memory
    return 0; // Add explicit return
} // End of main

