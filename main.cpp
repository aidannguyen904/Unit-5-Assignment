//A  Restaurant Project Struct style Dr_T Dr. Tyson McMillan 10-2-2019

#include<iostream> //for cin
#include<string> //for strings
#include<vector> //for menu
#include<iomanip> //for 
#include<fstream> //for file writing
#include "Input_Validation_Extended.h"" //for input validation
using namespace std; 
//colors
string Red = "\x1b[31;1m";
string Green = "\x1b[32;1m";
string Yellow = "\x1b[33;1m";
string Cyan = "\x1b[36:1m";
string Reset = "\x1b[0m";
class MenuItem{
private:
  string Name;
  double itemCost; 
  string desc; 
  char addLetter; 
  char removeLetter;
  int count; 
public:
  string getName(){return Name;}
  double getCost(){return itemCost;}
  string getDesc(){return desc;}
  char getAddLetter(){return addLetter;}
  char getRemoveLetter(){return removeLetter;}
  int getCount(){return count;}
  void setName(string n){Name = n;}
  void setCost(double c){itemCost = c;}
  void setDesc(string d){desc = d;}
  void setAddLetter(char a){addLetter = a;}
  void setRemoveLetter(char r){removeLetter = r;}
  void setCount(int c){count = c;}
  void incrementCount(){count++;}
  void decrementCount(){count--;}
};

//function definitions
void populateMenu(vector<MenuItem> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItem Item1; 
  MenuItem Item2;
  MenuItem Item3; 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Green Tea", "Burrito", "Chicken", "Brownie", "Burger", "Pizza", "Cake"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently 
    entireMenu[i].setName(defaultMenuNames[i]); 
    entireMenu[i].setAddLetter(defaultAddLetters[i]); 
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setCost(3.00 + i); //set a random starter cost for each item
    entireMenu[i].setCount(0); //initialze all counts to 0
    entireMenu[i].setDesc("delicious"); //set all default desc to "delicous"
  }


}

void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << "DrT's Effcient Menu" << endl; 
  cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << Cyan << m[i].getAddLetter() << Reset << ")" << setw(10) << m[i].getName() 
    << Green << setw(5) << "$" << m[i].getCost() << Reset << Red << setw(5) << "(" << m[i].getRemoveLetter()
    << ")" << Reset << setw(7) << m[i].getCount() << setw(13) << m[i].getDesc() 
    <<endl; 
  }

}
void printReciept(vector<MenuItem> &m, double s, double t, double tax){
  ofstream file( "receipt.txt" );
  file << "\nTotal: " << s << "$";
  file << "\nTip: " << t << "$";
  file << "\nTax: " << (t * tax) << "$";
  for(int i = 0; i < m.size(); i++){
    file << "\n" << m[i].getName() << ": " << m[i].getCount() << " | Cost: " << m[i].getCost() << " each";
  }
}
void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0';// the user-selected menu item
  double subtotal = 0.0;
  double tip = 0.0;
  double tax = 0.2;
  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option; 

    for(int i=0; i < m.size(); i++)
    {
      if(option == m[i].getAddLetter())
      {
        cout << "\nMenu Item " << m[i].getAddLetter() << " selected."; 
        m[i].incrementCount(); //increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << Yellow << "\n1 UP " << Reset << "on " << Cyan << m[i].getName() << Reset << endl;
        subtotal += m[i].getCost(); //increment the subtotal by the cost of the item 
        showMenu(m); //show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;  
      }
      else if(option == m[i].getRemoveLetter())
      {
        cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected."; 
        if(m[i].getCount() > 0) //subtract if and only if the count is > 0
        {
          m[i].decrementCount(); //decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << Red << m[i].getName() << Reset << endl;
          subtotal -= m[i].getCost(); //decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << Green << subtotal << Reset << endl;  
        }
        else //the the user why you blocked item removal 
        {
            
            cout << Red << "\nItem count must be > 0 to remove: " << Reset << m[i].getName() << endl;
        }
      }
      else if(
                option != m[i].getAddLetter() && 
                option != m[i].getRemoveLetter() &&
                option != 'x' &&
                option != 'X' 
            ) //test for all of my valid inputs
            {
              if(i == 0)
              {
                cout << "\nInvalid input (" << Red << option << Reset << "). Please try again." << endl; 
              }  
            }
    }
  }while(option != 'x' && option != 'X'); 
  cout << "\nThank you for placing your order." << endl; 
  cout << "\nWould you like to leave a tip? (" << Green << "Y" << Reset << "/" << Red << "N" << Reset << "):";
  
  while(true){
  cin >> option;
  if(option == 'y' || option == 'Y'){
    cout << Cyan << "\nTip how much? " << Reset << "(" << Yellow << "20%" << Reset << " is suggested): ";
    tip = validateDouble(tip);
    break;
  } else if (option == 'n' || option == 'N'){
    break;
    } else {
    cout << "\nInvalid input (" << Red << option << Reset << "). Please try again." << endl;
    cout << "\nChoose an option: ";
    }
  }
  cout << "\nThank you for your tip of $" << Green << tip << Reset << endl;

  subtotal += (subtotal * tax) + tip;
  cout << "\nYour total is $" << Green << subtotal << Reset;
  cout << "\nYour tip is $" << Green << tip << Reset;
  cout << "\nYour tax is $" << Green << (subtotal * tax) << Reset;
  cout << "\n";
  for(int i = 0; i < m.size(); i++){
    cout << "\n" << m[i].getName() << ": " << Cyan << m[i].getCount() << Reset << " | Cost: " << Green << m[i].getCost() << "$" << Reset << " each";
  }
  double cash = 0.0;
  while(true){
    cout << "\nHow would you like to pay? (C for Cash or D for Card): ";
    cin >> option;
    if(option == 'c' || option == 'C'){
      cout << "Please enter the amount paid in cash: ";
      cash = validateDouble(cash);
      subtotal -= cash;
      if(subtotal < 0){
        cout << "Your change is $" << Green << subtotal * -1 << Reset;
        cout << "Have a nice day!";
        break;
      } else if(subtotal > 0){
        cout << Red << "Insufficient funds. Please try again." << Reset << endl;
      }
    } else if (option == 'd' || option == 'D'){
      cout << "Card Processed. Have a nice day!";
      break;
    } else {
      cout << "Invalid Input (" << Red << option << Reset << "). Please try again." << endl;
      cout << "Please enter C or D: ";
    }
    
  }
  cout << Cyan << "\nPrinting Reciept..." << Reset;
  printReciept(m, subtotal, tip, tax);
  cout << "\nPrinted, Have a nice day!";
}

int main() 
{
  char choice = ' ';
  while(choice != 'e' && choice != 'E'){
  cout << "\033[2J\033[1;1H";
  vector<MenuItem> wholeMenu; 
  populateMenu(wholeMenu); //put some default values in the menu
  showMenu(wholeMenu); //print the current data of the menu on screen 
  acceptOrder(wholeMenu); 
  cout << "\nPress any character to restart, and E to exit program: ";
  cin >> choice;
  }
  return 0; 
}