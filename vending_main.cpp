#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "vending.hpp"
using namespace std;
using Vending2::user;
using Vending2::admin;

    void showMenu_user(){
        cout << "1. Choose product to buy :) "<< endl;  //call selectBuy(), see the menu, and select an item to buy, and exit
        cout << "2. !!!Hot Selling Item!!!"<<endl;  //call hotSelling()
        cout << "9. Exit "<< endl;

    };

    void showMenu_admin(){
        cout << "Welcome!! Admin. "<<endl;
        cout << "1. Add and delete item in the menu (file)."<< endl;              //call  edit_Item()
        cout << "2. Add item into the machine (link list).  "<< endl;            //call  addNode_Linklist()
        cout << "3. Remove item from the machine."<< endl;                       //call  removeNode_Linklist()
        cout << "4. Display the menu and the items in the machine. "<< endl;       //call display_File_LinkList()
        cout << "9. Exit "<< endl;

    };

int main(){
        int choice,select;//select : Select whether you are the customer
        string password = "123";
        string input_password;
        admin a;
        user u;
        cout.setf(ios::fixed);
        cout.precision(2);
        cout.setf(ios::showpoint);

    //initialize the machine with 10 banana, 10 apple, 10 orange
    a.initialize_machine(1001,10,1);  //ID, quantity, 1, the last number always set to 1
    a.initialize_machine(2001,10,1);

        cout<< "########################################################################################################"<<endl;
        cout<< "##########///////////////////////////////////////////////////////////////////////////////###############"<<endl;
        cout<< "##########/////         //_____/____////____//_____/__//_//  _______//__/__/        /////###############"<<endl;
        cout<< "##########/////         /  ___|     |//    |/     |/| |/ |  |      |/| | | |        /////###############"<<endl;
        cout<< "##########/////         (  |_/|  _  ||  o  |/  /////|  ' / /|____  |/| | | |        /////###############"<<endl;
        cout<< "##########/////         /\__  || | | ||     |/  /////|    \/////// ////| |_| |        /////###############"<<endl;
        cout<< "##########/////         ////\ || | | ||  _  |/  /////|     \///// /////|____ |        /////###############"<<endl;
        cout<< "##########/////         |--  || | | || | | |/  ///|/|  .   |/// /__// /____|        /////###############"<<endl;
        cout<< "##########/////         |____||_| |_||_|_|_|\______|/|_|-|_ |/|_____|/|_____/        /////###############"<<endl;
        cout<< "##########///////////////////////////////////////////////////////////////////////////////###############"<<endl;
        cout<< "######################################################################################################################"<<endl;
        cout<< "######################################################################################################################"<<endl<<endl;
        cout<< " --------------------------------------------------------------------------------------------------------------------"<<endl;

    do{
        cout<< "                            ********************WELCOME TO SNACKZY****************"<<endl;
        cout<< "                            ******************************************************"<<endl;
        cout<< "                            ******************     WHO ARE YOU ?? ****************"<<endl;
        cout<< "                            *************** 1.         USER         *************"<<endl;
        cout<< "                            *************** 2.        ADMIN          *************"<<endl;
        cout<< "                            ******************************************************"<<endl<<endl;

        cout<< " Enter 1 if you are the user."<<endl;
        cout<< " Enter 2 if you are the admin. "<<endl;
        cout<< " Press any number to exit."<<endl;
        cout<< " Your choice : ";
        cin>> select;        //verify is admin or user
        system("cls");      //clear screen

        switch (select){   //to know is user or admin
            cout.setf(ios::fixed);
            cout.precision(2);
            cout.setf(ios::showpoint);
        case 1:                 //if is user
            do {
                showMenu_user();
                cout<<endl;
                cout<<"Welcome to Snackzy ^.^";
                cout << "Please key in your choice (Example: 1) : ";
                cin>>choice;
                system("cls");

                switch (choice){  //choice for user
                    case 1:
                        a.selectBuy();
                        break;
                    case 2:
                        u.hotSelling();
                        break;
                    default:
                        cout<< "Invalid input, Please try again!"<<endl;
                        cout<<endl;
                }//end user choice
            }while(choice!=9);  //end user choice
            break;

        case 2:  //if is admin
            cout<< "Please key in the password for admin : ";
            cin>>input_password;
            if (input_password==password){
                do{
                    system("cls");
                    showMenu_admin();
                    cout<<endl;
                    cout << "Please key in your choice (Example: 1) : ";
                    cin>>choice;
                    system("cls");
                    switch (choice){ //choice for admin
                        case 1:
                            a.edit_Item();
                            break;
                        case 2:
                            a.addNode_Linklist();
                            break;
                        case 3:
                            a.removeNode_Linklist();
                            break;
                        case 4:
                            a.display_File_LinkList();
                            break;
                        default:
                            cout << "Invalid input!" << endl;
                    }
                }while(choice!=9);
            }//end if
            else{
                cout<< "Invalid password. Please leave this page. "<<endl;
                system("pause");
                system("cls");
            }
            default:
                cout<< "bye bye!"<<endl;
        }//end switch
    }while(select==1||select==2);
    return 0;
}//end main
