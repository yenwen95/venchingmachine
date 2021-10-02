#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "vending.hpp"
using namespace std;
using namespace Vending2;

    void user::setID(){ this -> item_ID = item_ID; }

    void user::setName(){ this -> item_name = item_name; }

    void user::setPrice(){ this -> item_price = item_price; }

    //Display the items inside the machine and the menu in file
    //and let user to choose what should add in the shopping list
    void user::display_File_LinkList(){
        node *tempPtr = frontPtr;
        node *traverse = frontPtr;
        string line;
        int num1 = 0;
        int num2 = 0;

        if(traverse == NULL){
            cout<<"The machine is empty..."<<endl;
            cout<<endl;
        }
        else {
            while(traverse != NULL){    //loop on the different link
                tempPtr = traverse;
                while(tempPtr != NULL){ //loop on the same link
                    cout<<tempPtr->nodeItem_ID<<" -> ";
                    tempPtr =  tempPtr -> next;
                    num1 ++;    //count the number of node in each link
                }//end while
                cout<<endl;
                cout<<"There are " << num1 << " of "<< traverse->nodeItem_ID<< " in this link."<<endl;
                cout<<endl;
                num1 = 0;
                traverse = traverse -> diff;
                num2++;  //count the number of different link
            }//end while

            cout<<endl;
            cout<<"There are " << num2 << " types of food in this machine." <<endl;
        }//end else
        cout<<endl;
        cout<<endl;
        //Display file
        cout<< " ~~~~~~~Items in file: ~~~~~~~~ " << endl;
        ifstream iteminFile;
        iteminFile.open ("item.txt");
        while (getline(iteminFile,line)){
            cout << line << endl;
        }
        cout<<endl;
        iteminFile.close();
        system("pause");
    }//end display_File_LinkList()

    //User select an item id, the machine will remove a node, and read the price from the file
    void user::selectBuy(){
        display_File_LinkList();   //display the menu first
        node *traverse;
        node *previous = new node;
        node *tempPtr = frontPtr;
        previous = frontPtr;
        char choices;
        bool success = false;
        ifstream menu;
        string  itemName,temp,line;
        double itemPrice,payment;
        int a;

        cout<<"Enter the item ID that you want to buy: ";
        cin>>item_ID;
        //convert id to string for file
        a = item_ID;
        std::stringstream ss;
        ss << a;
        string itemID = ss.str();

        //if the item is matching with the first node on the first link
        if(item_ID == (frontPtr -> nodeItem_ID)){
            cout<<"Item is  found! This is the first item on the first link."<<endl;
            cout<<"\nDo you really want to buy this item? Enter y or n to continue:  ";
            cin>>choices;
            cout<<endl;
            if(choices == 'y' || choices == 'Y'){
                //open file to check the amount and pay
                menu.open("item.txt",ios::in);
                if(menu.is_open()){
                    while(getline(menu,temp)){
                        menu>>temp;
                        line.append(temp);
                        if(line.find(itemID) != string::npos){
                            menu>>itemName>>itemPrice;
                            cout<<"Item name: "<<itemName<<endl;
                            cout<<"Item price: "<<itemPrice<<endl;
                            break;
                        }
                    }
                }
                else{
                    cout<<"File is unable to open!"<<endl;
                }
                cout<<"Please pay and get your item: ";
                cin>>payment;
                if(payment != itemPrice){
                    cout<<"Payment is not success!"<<endl;
                }
                else{
                    //remove node from machine
                    cout<<"Payment is successfully made."<<endl;
                    success = true;
                    frontPtr = frontPtr -> next;
                    frontPtr -> diff = tempPtr -> diff;
                    free(tempPtr);
                    cout<<"Item is selected to pop out!\n"<<endl;
                }
            }//end choice y

            else if (choices == 'n' || choices == 'N'){
                cout<<"Try this item next time :)"<<endl;
            }
            else{
                cout<<"Invalid input!"<<endl;
            }
        } //end if
        else{ //if the removed item is not the first node
            while(item_ID != (tempPtr -> nodeItem_ID)&& (tempPtr -> diff) != NULL){
                previous = tempPtr;
                tempPtr = tempPtr -> diff; //we move the pointer to next link
            }//end while
            if((tempPtr -> nodeItem_ID) == item_ID){
                cout<<"Item is  found!"<<endl;
                cout<<"Do you really want to buy this item? Enter 'y' or 'n' to continue:  ";
                cin>>choices;
                cout<<endl;
                if(choices == 'y' || choice == 'Y'){
                    //open file to check the amount and pay
                    string temp,line;
                    menu.open("item.txt",ios::in);
                    if(menu.is_open()){
                        while(getline(menu,temp)){
                            menu>>temp;
                            line.append(temp);
                            if(line.find(itemID) != string::npos){
                                menu>>itemName>>itemPrice;
                                cout<<"Item name: "<<itemName<<endl;
                                cout<<"Item price: "<<itemPrice<<endl;
                                break;
                            }
                        }
                    }
                    else{
                        cout<<"item.txt is unable to open!"<<endl;
                    }
                    cout<<"Please pay and get your item: ";
                    cin>>payment;
                    if(payment != itemPrice){
                        cout<<"Payment is not success!"<<endl;
                    }
                    else{
                        //remove node from machine
                        cout<<"Payment is successfully made."<<endl;
                        success = true;
                        traverse = tempPtr -> next;
                        traverse -> diff = tempPtr -> diff;
                        previous -> diff = traverse;
                        free(tempPtr);
                        cout<<"Item is selected to pop out!"<<endl;
                    }
                }//end choice y
                else if (choices == 'n' || choices == 'N'){
                    cout<<"Try this item next time :)"<<endl;
                }
                else{
                    cout<<"invalid input!"<<endl;
                }
            }else{
                cout<<"No such item."<<endl;
            }//end else
        }//end else for outer if

        //add the selected item into the txt file
        if(success == true){
            ofstream hot_sell;
            hot_sell.open("Hotselling.txt",ios::out|ios::app);
            if(hot_sell.is_open()){
                hot_sell<<item_ID <<"\n";
                cout<<"This will be added to count the hot selling item."<<endl;
            }else{
                cout<<"Hotselling.txt is unable to open."<<endl;
            }
            hot_sell.close();
        }
        system("pause");
        system("cls");
        menu.close();
    }//end selectBuy()

    //Display the most hot selling item, will have one hotselling.txt, sorting and calculating the most hot item
    void user::hotSelling(){
        ifstream hot;
        hot.open("Hotselling.txt");
        int i, j,temp, index, small,line,current,MAX_ID;
        int count=0;
        int amount=1;
        int Size=100;
        int row=0;
        int col=1;
        int myArray[Size][2];
        int MAX=0;

        //Put the id into the array
        while (hot >> line){
            numbers.push_back(line);
        }
        hot.close();
        //show the id from the array
        cout <<"Numbers: ";
        for (int i=0; i < numbers.size();i++){
            cout << numbers[i] << "  ";
        }
        cout<< endl;
        //Sorting the array using selection sort algorithm
        for (i=0;i< numbers.size(); i++){
            small = numbers[i];
            for (j=(i+1); j<numbers.size(); j++){
                if (small>numbers[j]){//if the left node bigger than the right node
                    small = numbers[j];  //the right node is smaller, so right node is assigned in small
                    count++;
                    index = j;
                }
            }
            if (count!=0){
                temp = numbers[i];
                numbers[i] = small;
                numbers[index] = temp;
            }
            count = 0;
        }//end for
        cout<< "\nArray after sorting is : \n";
        for (i=0;i<numbers.size();i++)
        cout<<numbers[i]<<" ";

        cout<< endl;
        //end sorting
        //counting the value and put into the new array
        for(i=0;i<numbers.size();i++){
            if(numbers[i]==numbers[i+1]){
                amount++;    //1st num == 2nd num
                myArray[row][col-1]=numbers[i]; //put id
                myArray[row][col]=amount; //put amount
            }
            else{
                row++;
                amount=1;
            }
        }
        for( i=0; i<row; i++){
            for( j=0; j<2; j++){
                cout<<endl;
                cout << "Element at x[" << i<< "][" << j << "]: ";
                cout << myArray[i][j]<<endl;
            }
        }
        cout << endl;
        //finding the max number
        for(i=0;i<row; i++){
            if(myArray[i][1]>myArray[i+1][1]){
                current=myArray[i][1];
            }
            if(MAX < current){
                MAX = current;
            }
        }
        for(i=0; i<row; i++){
            if(MAX == myArray[i][1])
                MAX_ID = myArray[i][0];
        }
        cout<<"\nOur MOST POPULAR ITEM IS ~~~~~~ "<<MAX_ID<<"~~~~~~"<<endl;
        cout << endl;
        system("pause");
        system("cls");
        hot.close();
    }//end hotselling()
//end user class

    /*For admin to add new item into the file.
    File is for reference to count money, is like a food menu.*/
    void admin::addItem_file(){
        ofstream add_Item;
        add_Item.open("item.txt",ios::out|ios::app);
            if(add_Item.is_open()){  //add into file
                cout<<"Enter item ID: ";
                cin >> item_ID;
                setID();
                cout<<"\nEnter item name: ";
                cin >> item_name;
                setName();
                cout<<"\nEnter item price: ";
                cin>>item_price;
                setPrice();
                add_Item<<item_ID<<"\t\t"<<item_name<<"\t\t"<<item_price<<endl;
                cout<<"New item is added successfully in file!"<<endl;
            }
            else{
                cout<<"File is unable to open"<<endl;
            }
            add_Item.close();
            system("pause");
            system("cls");
    }//end addNewItemFile()

    /*For admin to delete an item from the File. */
    void admin::deleteItem_file(){
        string line;
        string item_ID;
        ifstream deletefile;
        deletefile.open("item.txt");
        ofstream temp;
        temp.open("temp.txt");

        cout << "Enter item ID that you want to delete from the file: " << endl;
        cin >> item_ID;
        while (getline(deletefile,line)){
            if (line.substr(0, item_ID.size()) != item_ID){
                    temp << line << endl;
            }
        }
        cout << "The item " << item_ID << " has been deleted." << endl;
        temp.close();
        deletefile.close();
        remove ("item.txt");
        rename ("temp.txt","item.txt");
        system("pause");
        system("cls");
    }//end deleteItem_file()

    /*For admin to add item into the link list.
      Link list is the machine state, it contains the number of items currently in the machine*/
    void admin::addNode_Linklist(){
        cout<<"You can add new item in machine."<<endl;
        cout<<"~~~Press 1 to add a brand new item."<<endl;
        cout<<"~~~Press 2 to add an original item."<<endl;
        cout<<"~~~Press 9 to exit"<<endl;
        cout<<"Your choice is :"<<endl;
        cin>>choice;
        cout<<endl;

        while(choice != 9){
            //this temp points to the address of front
            //tempPtr has a copy of frontPtr
            node *tempPtr = frontPtr;
            //add a brand new item, only moving the diff pointer
            if(choice == 1){
                cout<<"\nPlease insert the brand new item ID that you want to add: "<<endl;
                cin>>item_ID;
                //create new node
                node *newNodePtr = new node;
                newNodePtr -> nodeItem_ID = item_ID;
                newNodePtr -> next = NULL;
                newNodePtr -> diff = NULL;

                if(frontPtr == NULL){   //means the whole list is empty
                    frontPtr = newNodePtr;
                    cout<<"The first item of the first link is added!\n"<<endl;
                }
                else{
                    while(tempPtr -> diff != NULL){//finding the null node that is pointed by diff pointer
                        tempPtr= tempPtr->diff;
                    }//stop when if found the null node
                    cout<<"Empty link is found!"<<endl;
                    tempPtr -> diff = newNodePtr;
                    cout<<"New item is added in this link!\n"<<endl; //found it, and link together
                }//end else
            }//end if choice 1

            //add the new node that the its type is original in the list
            else if(choice == 2){
                cout<<"\nPlease insert the item ID that you want to add: "<<endl;
                cin>>item_ID;
                //create new node
                node *newNodePtr = new node;
                newNodePtr -> nodeItem_ID = item_ID;
                newNodePtr -> next = NULL;

                //finding the matched id in the list
                while((tempPtr -> nodeItem_ID) != (newNodePtr -> nodeItem_ID) && (tempPtr -> diff) != NULL){
                    tempPtr = tempPtr -> diff; //we move the pointer to next link
                }//when it find the correct id, stop

                if(tempPtr -> nodeItem_ID != newNodePtr-> nodeItem_ID){
                    cout<<"No such item in the list..."<<endl;
                }
                else{
                    // we find the last node of the correct link
                    cout<<"The link is found!"<<endl;
                        while(tempPtr->next != NULL){
                            tempPtr = tempPtr -> next;  //it will go the next node at the same link
                        }
                    tempPtr->next = newNodePtr;
                    cout<<"Item is added!\n"<<endl;
                }//end else
            }//end if choice 2
            else{
                 cout<<"Invalid input!"<<endl;
            }
        system("pause");
        system("cls");
        cout<<"\nContinue to add item, please: "<<endl;
        cout<<"~~~Press 1 to add a new item in the list."<<endl;
        cout<<"~~~Press 2 to add an original item in the list."<<endl;
        cout<<"~~~Press 9 to exit."<<endl;
        cout<<"Your choice is :"<<endl;
        cin>>choice;
        cout<<endl;
        } //end while loop to exit
} //end function

    /*initialize the machine with some food*/
    void admin::initialize_machine(int ID,int quantity,int first){
            node *tempPtr = frontPtr;
            //add a brand new item, only moving the diff pointer
            if(first == 1){
                //create new node
                node *newNodePtr = new node;
                newNodePtr -> nodeItem_ID = ID;
                newNodePtr -> next = NULL;
                newNodePtr -> diff = NULL;
                if(frontPtr == NULL){
                    frontPtr = newNodePtr;
                }
                else{
                    while(tempPtr -> diff != NULL){
                        tempPtr= tempPtr->diff;
                    }
                    tempPtr -> diff = newNodePtr;
                }//end else
            }//end if choice 1
            //add the new node that the its type is original in the list
            for(int i=1; i<quantity; i++){
                node *tempPtr = frontPtr;
                node *newNodePtr = new node;
                newNodePtr -> nodeItem_ID = ID;
                newNodePtr -> next = NULL;
                while((tempPtr -> nodeItem_ID) != (newNodePtr -> nodeItem_ID)){
                    tempPtr = tempPtr -> diff;
                }
                if(tempPtr -> nodeItem_ID != newNodePtr-> nodeItem_ID){
                    cout<<"No such item in the list..."<<endl;
                }
                else{
                    while(tempPtr->next != NULL){
                        tempPtr = tempPtr -> next;
                }
                    tempPtr->next = newNodePtr;
                }//end else
            }//end for loop
}//end initialize_machine

    /*For admin to remove an item from the link list.*/
    void admin::removeNode_Linklist(){
        cout<<"Here you can move out one item."<<endl;
        cout<<"Enter any number to continue."<<endl;
        cout<<"Enter 9 to exit."<<endl;
        cout<<"Your choice: "<<endl;
        cin>>choice;
        cout<<endl;
        node *traverse;
        node *previous = new node;
        node *tempPtr = frontPtr;
        previous = frontPtr;

        while(choice != 9){
            cout<<"Enter the item ID that you want to move out: "<<endl;
            cin>>item_ID;

            //finding the matched id in the list
            if(item_ID == (frontPtr -> nodeItem_ID)){
                    frontPtr = frontPtr -> next;
                    frontPtr -> diff = tempPtr -> diff;
                    free(tempPtr);
            }
            else{ //if the removed item is not the first node
                while(item_ID != (tempPtr -> nodeItem_ID) && (tempPtr -> diff) != NULL){
                    previous = tempPtr;
                    tempPtr = tempPtr -> diff; //we move the pointer to next link
                }//end while
                if((tempPtr -> nodeItem_ID) == item_ID){
                    cout<<"Item is found!"<<endl;
                    traverse = tempPtr -> next;
                    traverse -> diff = tempPtr -> diff;
                    previous -> diff = traverse;
                    free(tempPtr);
                    cout<<"Item is deleted."<<endl;
                }else{
                    cout<<"No such item. Please try again."<<endl;
                }//end else
            }//end else
            system("pause");
            system("cls");
            cout<<"Here you can move out one item."<<endl;
            cout<<"Enter any number to continue."<<endl;
            cout<<"Enter 9 to exit."<<endl;
            cout<<"Your choice: "<<endl;
            cin>>choice;
            cout<<endl;
        }//end while
    }//end removeNode_Linklist()

    /*For admin to edit product's name, id and price in the file. */
    void admin::edit_Item(){
        cout<<"Press 1 to add new item in the file."<<endl;
        cout<<"Press 2 to delete item from the file."<<endl;
        cout<<"Press any number to go back."<<endl;
        cout<<"Your choice: "<<endl;
        cin>>choice;

        while(choice == 1 || choice == 2){
            display_File_LinkList();
            if(choice == 1){
                addItem_file();
                cout<<"Press 1 to add new item in the file."<<endl;
                cout<<"Press 2 to delete item from the file."<<endl;
                cout<<"Press any number to go back."<<endl;
                cout<<"Your choice: "<<endl;
                cin>>choice;
            }
            else if (choice == 2){
                deleteItem_file();
                cout<<"Press 1 to add new item in the file."<<endl;
                cout<<"Press 2 to delete item from the file."<<endl;
                cout<<"Press any number to go back."<<endl;
                cout<<"Your choice: "<<endl;
                cin>>choice;
            }
            else{
                cout<<"Invalid Input!"<<endl;
                system("pause");
                system("cls");
            }
        }//end while
    }//end edit_Item()
 //end admin class





