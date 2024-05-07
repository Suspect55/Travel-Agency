#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <random>
#include <chrono>
#include <ctime>

#include"function.cpp"
using namespace std;

const int Country = 14;
const int State = 8;

struct DestinationInfo 
{
    int dest_id;
    string country;
    string loc;
    int dur;
    double cost;
};

class ADTqueue
 {
    private:
    DestinationInfo queue[10];
    int head,tail;
    public:
    ADTqueue()
    {
        tail =-1;
        head = 0;
    }

    int empty()
    {
        if(head == tail+1)
        return 1;
        else
        return 0;
    }

    int full()
    {
        if(tail == 9)
        return 1;
        else
        return 0;
    }

    void append(DestinationInfo& data)
    {
        if (!full())
        {
            tail++;
            queue[tail] = data;
        }

        else
        {
            cout<<"Queue is Full"<<endl;
        }
    }
    
    DestinationInfo serve()
    {
        DestinationInfo retVal;
        if(!empty())
        {
            retVal = queue[head];
            head++;
            return retVal;
        }

        else
        {
            cout<<"Queue is Empty"<<endl;
            exit(0);
        }
    }


};

struct Node
{    
    DestinationInfo data;
    Node* next;
};

struct UserDetails {
    string username;
    string ic;
};


Node* createNode(DestinationInfo& data)
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}


Node* destList(DestinationInfo* arr, int size)
{
    Node* head = nullptr;
    Node* current = nullptr;

    for(int i = 0; i < size; i++)
    {
        Node* newNode = createNode(arr[i]);

        if(head == nullptr)
        {
            head = newNode;
            current = newNode;
        }

        else{
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}


void dispDest(Node* head)
{
    Node* current = head;

    int i = 1;

    while (current) {
            cout << endl;
            cout << "                                                                  ______________________________________________" << endl;
            cout << "                                                                 |  __________________________________________  |" << endl;
            cout << "                                                                 | |                                          | |" << endl;
            cout << "                                                                 | |                                          | |" << endl;
            cout << "                                                                 | |             "<< "< Packages " << i << " >" << setw(18) << right << "| |" << endl;
            cout << "                                                                 | |                                          | |" << endl;
            cout << "                                                                 | |                                          | |" << endl;
            cout << "                                                                 | |       "<< "ID              : " << current->data.dest_id << setw(16) << right << "| |" << endl;
            string adjustedCountry = adjustCountry(current->data.country, Country);
            cout << "                                                                 | |       "<< "Country         : " << adjustedCountry << setw(6) << right << "| |" << endl;
            string adjustedState = adjustState(current->data.loc, State);
            cout << "                                                                 | |       "<< "State           : " << adjustedState << setw(13) << right <<"| | " << endl;
            cout << "                                                                 | |       "<< "Duration (days) : " << current->data.dur << setw(20) << right <<"| | " << endl;
            cout << "                                                                 | |       "<< "Cost            : $" << current->data.cost << setw(13) << right <<"| |" << endl;
            cout << "                                                                 | |                                          | |" << endl;
            cout << "                                                                 | |__________________________________________| |" << endl;
            cout << "                                                                 |______________________________________________|" << endl;
            cout << endl;
            current = current->next;
            i++;
    }
    cout << endl;
}

void addDest(Node* head, DestinationInfo& data)
{
    Node* newNode = createNode(data);
    if(head == nullptr)
    {
        head = newNode;
    }

    else{
        Node* current = head;
        while(current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;
    }
}

Node* searchDest(Node* head, int searchId) //linear search
{
    Node* current = head;
        while (current) {
            if (current->data.dest_id == searchId) {
                return current; // Found the destination
            }
            current = current->next;
        }
        return nullptr;
}

void editDest(Node* editNode, DestinationInfo& data)
{
   editNode->data = data;
}


void deleteDest(Node*& head, int delId)
{
    Node* current = head;
    Node* prev = nullptr;

        while (current) {
            if (current->data.dest_id == delId) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }

                cout << "\n" << endl;
                cout << "                                                                   ===========================================" << endl;
                cout << "                                                                   |                                         |" << endl;
                string adjustedCountry = adjustCountry(current->data.country, Country);
                cout << "                                                                   |  " << adjustedCountry << " deleted successfully !" << "  |" << endl;
                cout << "                                                                   |                                         |" << endl;
                cout << "                                                                   ===========================================" << endl;
                delete current;
                return;
            }

            prev = current;
            current = current->next;
        }

        TPnotFound();

}

class userPage
{
    private:
        UserDetails userStack[10]; // Assuming a maximum of 10 users
        int top;
    public:
        userPage() 
        {
            top = -1; // Initialize top of the stack
        }

        void pushUserDetails(const UserDetails& userDetails)
        {
            if (top < 9) {
                top++;
                userStack[top] = userDetails;
            } else {
                cout << "Stack is full. Cannot push more user details." << endl;
            }
        }
        void user(Node* head)
        {
            UserDetails userDetails;
            cout << endl;
            cout << "                                                                        Enter your username : ";
            cin >> userDetails.username;
            cout << endl;
            cout << "                                                                       Enter your IC number : ";
            cin >> userDetails.ic;

            pushUserDetails(userDetails);

            int choice;
            ADTqueue cart;
            char cont = 'Y';

            do{
            mainPage();
            cout << "                                                                               Enter choice : ";
            cin >> choice;
            
            
            switch(choice)
            {
                case 1:
                {
                    int userAddId;
                    dispDest(head);
                    cout << "                                     Enter ID of travel package you would like to add : ";
                    cin >> userAddId;
                    Node* destToAdd = searchDest(head, userAddId);
                    if(destToAdd)
                    {
                        cart.append(destToAdd->data);
                        addCart();
                    }

                    else
                    {
                        invalidTP();
                    }
                    
                break;
                }

                case 2:
                    
                    int cartChoice;
                    int sect;
                    if(cart.empty()) 
                    {
                        emptyCart();
                    } 

                    else 
                    {
                        do
                        {
                            double total = 0;
                            sect = 0;
                            cout << "\n--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" << endl;
                            cout << "                                                                                < Cart Contents >" << endl;
                            ADTqueue tempCart = cart; //assigns values of cart to a temporary queue

                            //temporary queue gets printed and emptied whilst original queue remains unchanged
                            while (!tempCart.empty()) 
                            {
                                DestinationInfo dest = tempCart.serve();
                                cout << endl;
                                cout << "                                                                  ______________________________________________" << endl;
                                cout << "                                                                 |  __________________________________________  |" << endl;
                                cout << "                                                                 | |                                          | |" << endl;
                                cout << "                                                                 | |                                          | |" << endl;
                                cout << "                                                                 | |       "<< "ID             : " << dest.dest_id << setw(17) << right << "| |" << endl;
                                string adjustedCountry = adjustCountry(dest.country, Country);
                                cout << "                                                                 | |       "<< "Country        : " << adjustedCountry << setw(7) << right << "| |" << endl;
                                string adjustedState = adjustState(dest.loc, State);
                                cout << "                                                                 | |       "<< "State          : " << adjustedState << setw(14) << right <<"| | " << endl;
                                cout << "                                                                 | |       "<< "Duration (day) : " << dest.dur << setw(21) << right <<"| | " << endl;
                                cout << "                                                                 | |       "<< "Cost           : $" << dest.cost << setw(14) << right <<"| |" << endl;
                                cout << "                                                                 | |                                          | |" << endl;
                                cout << "                                                                 | |__________________________________________| |" << endl;
                                cout << "                                                                 |______________________________________________|" << endl;
                                cout << endl;
                                total = total + dest.cost;
                            }
                            cout << "                                                                               Grand Total : $" << total << endl << endl;

                            cartMenu();
                            cout << "                                                                               Enter Choice : ";
                            cin >> cartChoice;

                            switch(cartChoice)
                            {
                                int removeId;
                                case 1:
                                {
                                    cout << endl;
                                    cout << "                                                       Enter ID of travel package to delete : ";
                                    cin >> removeId;
                                    int found = -1;

                                    
                                    while (!cart.empty())
                                    {
                                        DestinationInfo tempDest = cart.serve();
                                        if (tempDest.dest_id != removeId)
                                        {
                                            tempCart.append(tempDest); 
                                        }

                                        else
                                        {
                                            found = 1;
                                            removeCart();
                                            sect = 1;
                                        }
                                    }

                                    if (found < 0)
                                    {
                                        TPnotFound();
                                    }

                                    cart = tempCart;
                                break;
                                }

                                case 2:
                                    {
                                        //generate invoice number
                                        random_device rd;
                                        mt19937 gen(rd());
                                        uniform_int_distribution<> dis(10000, 99999);
                                        int invoiceNum = dis(gen);

                                        //current date and time
                                        chrono::system_clock::time_point now = chrono::system_clock::now();
                                        time_t currentTime = chrono::system_clock::to_time_t(now);
                                        tm* localTime = localtime(&currentTime);
                                        int year = localTime->tm_year + 1900;
                                        int month = localTime->tm_mon + 1;
                                        int day = localTime->tm_mday;
                                        int hour = localTime->tm_hour;
                                        int minute = localTime->tm_min;
                                        int second = localTime->tm_sec;

                                        string ampm = (hour < 12) ? "AM" : "PM";

                                        // Adjust the hour for AM/PM format
                                        if (hour > 12) {
                                            hour -= 12;
                                        }

                                        cout << endl;
                                        cout << "                                                      ------------------------------------------------------------------------------  " << endl;
                                        cout << "                                                     |                                                                              | " << endl;
                                        cout << "                                                     |           ______        _______.     ___       __  ___      ___              | " << endl;
                                        cout << "                                                     |          /  __  \\      /       |    /   \\     |  |/  /     /   \\             | " << endl;
                                        cout << "                                                     |         |  |  |  |    |   (----`   /  ^  \\    |  '  /     /  ^  \\            | " << endl;
                                        cout << "                                                     |         |  |  |  |     \\   \\      /  /_\\  \\   |    <     /  /_\\  \\           | " << endl;
                                        cout << "                                                     |         |  `--'  | .----)   |    /  _____  \\  |  .  \\   /  _____  \\          | " << endl;
                                        cout << "                                                     |          \\______/  |_______/    /__/     \\__\\ |__|\\__\\ /__/     \\__\\         | " << endl;
                                        cout << "                                                     |                                                                              | " << endl;
                                        cout << "                                                     |                                                                              | " << endl;
                                        cout << "                                                     |                        Osaka Travel Agency Sdn.Bhd                           | " << endl;
                                        cout << "                                                     |                                                                              | " << endl;
                                        cout << "                                                     |                            Persiaran Multimedia                              | " << endl;
                                        cout << "                                                     |                               63100 Cyberjaya                                | " << endl;
                                        cout << "                                                     |                                  Selangor.                                   | " << endl;
                                        cout << "                                                     |                                1-300-80-0668                                 | " << endl;
                                        cout << "                                                     |                               www.mmu.edu.my                                 | " << endl;
                                        cout << "                                                     |                                                                              | " << endl;
                                        cout << "                                                     |==============================================================================| " << endl;
                                        cout << "                                                     |                                   Invoice                                    | " << endl;
                                        cout << "                                                     |==============================================================================| " << endl;
                                        cout << "                                                     |                                                                              | " << endl;
                                        cout << "                                                     | Invoice Number : " << invoiceNum << "                                                       | " << endl;
                                        cout << "                                                     | Date           : " << day << "/" << month << "/" << year << "                                                   | " << endl;
                                        cout << "                                                     | Time           : " << hour << ":" << minute << " " << ampm << "                                                     | " << endl;
                                        cout << "                                                     | BILL TO        : " << setw(30) << left << userDetails.username << "                              | " << endl;
                                        cout << "                                                     | IC             : " << setw(30) << left << userDetails.ic << "                              | " << endl;
                                        if (top >= 0) {
                                            top--;
                                        }
                                        cout << "                                                     |                                                                              | " << endl;
                                        cout << "                                                     |==============================================================================| " << endl;
                                        cout << "                                                     |                                                                              | " << endl;
                                        cout << "                                                     |                                 DESCRIPTION                                  | " << endl;
                                        cout << "                                                     |                                                                              | " << endl;
                                        cout << "                                                     | " << setw(10) << left << "ID" << setw(2) << right << "Country" << setw(19) << right << "State" << setw(27) << right << "Duration(day)" << setw(12) << right << "Cost($)" << "  | " << endl;
                                        cout << "                                                     |------------------------------------------------------------------------------| " << endl;                                
                                    while(!cart.empty())
                                    {
                                        DestinationInfo receipt = cart.serve();
                                        string adjustedCountry = adjustCountry(receipt.country, Country);
                                        string adjustedState = adjustState(receipt.loc, State);
                                        
                                        cout << "                                                     | " << setw(10) << left << receipt.dest_id << left << setw(2) << right << adjustedCountry << setw(15) << right << adjustedState << setw(17) << right << receipt.dur << setw(18) << right << receipt.cost <<"   | " << endl;
                                    }
                                    cout << "                                                     |------------------------------------------------------------------------------| " << endl;
                                    cout << "                                                     |" << " Total Payment : $ " << setw(56) << right << total << "   | " << endl;
                                    cout << "                                                     |------------------------------------------------------------------------------| " << endl;
                                    cout << "                                                     |                                                                              | " << endl;
                                    cout << "                                                     |       Thanks for choosing Osaka Travel Agency as your travel partners!       | " << endl;
                                    cout << "                                                     |                                                                              | " << endl;
                                    cout << "                                                     |                    We hope you enjoy your holiday with us!                   | " << endl;
                                    cout << "                                                     |                                                                              | " << endl;
                                    cout << "                                                     |                                                                              | " << endl;
                                    cout << "                                                     |      ___       ________  ___      ___ _______           ___  ___             | " << endl;     
                                    cout << "                                                     |     |\\  \\     |\\   __  \\|\\  \\    /  /|\\  ___ \\         |\\  \\|\\  \\            | " << endl;   
                                    cout << "                                                     |     \\ \\  \\    \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|        \\ \\  \\ \\  \\           | " << endl;   
                                    cout << "                                                     |      \\ \\  \\    \\ \\  \\ \\  \\ \\  \\/  / / \\ \\  \\_|/__       \\ \\  \\ \\  \\          | " << endl;  
                                    cout << "                                                     |       \\ \\  \\____\\ \\  \\_\\  \\ \\    / /   \\ \\  \\_|\\ \\       \\ \\  \\_\\  \\         | " << endl; 
                                    cout << "                                                     |        \\ \\_______\\ \\_______\\ \\__/ /     \\ \\_______\\       \\ \\_______\\        | " << endl;
                                    cout << "                                                     |         \\|_______|\\|_______|\\|__|/       \\|_______|        \\|_______|        | " << endl;
                                    cout << "                                                     |                                                                              | " << endl;
                                    cout << "                                                     |                                                                              | " << endl;
                                    cout << "                                                     |                                                                              | " << endl;
                                    cout << "                                                      ------------------------------------------------------------------------------  " << endl;
                                    cout << endl;
                                    sect = 1;
                                    cout << "                                                               Do you wish to continue? (Y/N) : ";
                                    cin >> cont;
                                    if (cont == 'N' || cont == 'n') 
                                    {
                                        thankyou();
                                        exit(0);
                                    } else if (cont == 'Y' || cont == 'y') {
                                        return;
                                    } else {
                                        cout << "Invalid choice. Exiting." << endl;
                                        exit(0);
                                    }
                                break;
                            }
                                
                                

                        }


                        }while(cartChoice != 3 && sect == 0);
                    }

                break;

                case 3:
                    thankyou();
                    exit(0);

                default:
                    invalid();
            }


            }while(choice != 3 && (cont == 'Y' || cont == 'y'));
        }
};



int admin(DestinationInfo* arr, int size, Node* head){
    int choice;
    do 
    {
        adminMenu();
        cout << "                                                                               Enter choice : ";
        cin >> choice;
        cin.ignore();

         switch (choice)
         {
            
            case 1:
                cout << endl;
                cout << "                                                                    Enter Travel Package ID : ";
                cin >> arr[size].dest_id;

                cout << endl;
                cout << "                                                                              Enter Country : ";
                cin.ignore();
                getline(cin, arr[size].country);

                cout << endl;
                cout << "                                                                                Enter State : ";
                getline(cin, arr[size].loc);

                cout << endl;
                cout << "                                                                   Enter Duration (in days) : ";
                cin >> arr[size].dur;

                cout << endl;
                cout << "                                                                                 Enter Cost : $ ";
                cin >> arr[size].cost;

                addDest(head, arr[size]); //function for adding new destination
                size++;
                newPackage();

            break;

            case 2:
            dispDest(head); //function to display destination list
            break;

            case 3:
            {
                DestinationInfo newData;
                int index;
                int editId;
                int editChoice;

                cout << endl;
                cout << "                                                         Enter ID of travel package to edit : ";
                cin >> editId;

                Node* destToEdit = searchDest(head, editId); //function to search for the index to edit in the linked list
                if(destToEdit)
                {
                    for(int i = 0; i < size; i++)
                    {
                        if(arr[i].dest_id == editId)
                        {
                            index = i;
                        }
                    }

                    editMenu();
                    cout << "                                                                               Enter choice : ";
                    cin >> editChoice;

                    cin.ignore();

                    switch(editChoice)
                    {
                        case 1: 
                            cout << endl;
                            cout << "                                                                          Enter new country : ";
                            getline(cin, arr[index].country);
                            editDest(destToEdit, arr[index]); //function to edit specific value of the struct in the linked list
                        break;

                        case 2: 
                            cout << endl;
                            cout << "                                                                            Enter new state : ";
                            getline(cin, arr[index].loc);
                            editDest(destToEdit, arr[index]);
                        break;

                        case 3: 
                            cout << endl;
                            cout << "                                                                   Enter new duration (day) : ";
                            cin >> arr[index].dur;
                            editDest(destToEdit, arr[index]);
                        break;

                        case 4: 
                            cout << endl;
                            cout << "                                                                             Enter new cost : $ ";
                            cin >> arr[index].cost;
                            editDest(destToEdit, arr[index]);
                        break;

                        case 5:
                            break;

                        default:
                            invalid();
                    }
                }

                else
                {
                    TPnotFound();
                }

            break;
         }

            case 4:
                int delId;
                cout << endl;
                cout << "                                                       Enter ID of travel package to delete : ";
                cin >> delId;

                deleteDest(head, delId); //function to delete destinations
                break;

            case 5:
                break;

            case 6:
                thankyou();
                exit(0);   
                        
            default:
                invalid();
         }
         
        
        }while(choice != 5);

        return size;
}

int adminLogin() 
{
    char username[50];
    char password[50];

    cout << endl;
    cout << "                                                                       Enter Admin Username : ";
    cin >> username;

    cout << endl;
    cout << "                                                                             Enter Password : ";
    cin>>password;

        if (strcmp(username, "mar") == 0 && strcmp(password, "911") == 0) //added login for admin
        {
            return 1;
        } 
        else 
        {
            invalidAdmin();
        }

    return 0;
}


int main()
{
    char option;
    DestinationInfo arr[10]; //amount of packages limited to 10
    int size = 3;
    userPage cust;

    //pre-defined destinations 
    arr[0].dest_id = 2001;
    arr[0].country = "Atlantic Ocean";
    arr[0].loc = "Atlantis"; 
    arr[0].dur = 5;
    arr[0].cost = 250000;

    arr[1].dest_id = 2002;
    arr[1].country = "The Sun       ";
    arr[1].loc = "Helios  "; 
    arr[1].dur = 4;
    arr[1].cost = 100000;

    arr[2].dest_id = 2003;
    arr[2].country = "Malaysia      ";
    arr[2].loc = "Kedah   "; 
    arr[2].dur = 6;
    arr[2].cost = 600000;

    Node* head = destList(arr, size); //passing array into the linked list

    do
    {
        login();
        cout << "                                                                               Enter choice : ";
        cin >> option;

        if (option == '1') 
        {
            int pass;
            pass = adminLogin();
            if(pass == 1){
                size = admin(arr, size, head); 
            }
        
            
        } 

        else 
        {
            
            cust.user(head);
            
            
        }
    } while(option != '0');

    return 0;
}
