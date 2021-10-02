#ifndef VENDING_HPP
#define VENDING_HPP
using namespace std;
namespace Vending2{

class user{
protected:
        string item_name;
        double item_price;
        int item_ID;
        int choice;
        vector<int> numbers;

        struct node{
            int nodeItem_ID;
            struct node *next; //point to the same link
            struct node *diff; //point to the different link
        };
        node  *frontPtr = NULL;
public:
    void setID();
    void setName();
    void setPrice();
    void display_File_LinkList();
    void selectBuy();
    void hotSelling();
}; //end user class

class admin : public user{
public:
    int choice;
    void addItem_file();
    void deleteItem_file();
    void addNode_Linklist();
    void initialize_machine(int ID,int quantity,int first);
    void removeNode_Linklist();
    void edit_Item();
};//end admin class
}
#endif // QUEUE_L_HPP
