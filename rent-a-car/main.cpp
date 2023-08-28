#include <iostream> //input output stream
#include <unistd.h> // uni standard library - to use sleep function
#include <ctime>     //to show current date and time
#include <fstream>   // file handling
#include <iomanip>   // output manipulation, setw()
#include <conio.h>   // console i/o - used in getch()
#include <dirent.h>  //directory handling
#include "utils.h" //data from utils
using namespace std; // standard namespace


//function declarations
void welcome(); //welcome function to display initial text
int login();                 // login function (at the start of program)
void main_menu();            // function to show main menu
void customer_menu();        //  function to show customer options
void admin_menu();           // function to show admin menu
void open_invoice(string &); // function to open existing invoice
string tell_time(int ); //function to return current date or time

// car class
class car : protected files // inheritance (inherited data members from files class)
{
    // private data members of car
    string model_name;
    string car_number;
    string fuel_type;
    long int km_travelled;
    int max_speed;
    int no_of_seats;
    string body_type;
    string type;

public:
    // declared an object to access functions of files for car
    files car_files;
    // constructor to get number of car files in cars directory
    car()
    {
        // calculating number of files in cars directory
        DIR *dp;
        i = 0;
        struct dirent *ep;
        dp = opendir(".\\cars");
        while (ep = readdir(dp))
            i++;

        (void)closedir(dp);
        n = i - 2;
        type = "car";
        car_files.make_files(n, type);
    }

    // function to add new cars (Admin access)
    void AddCar()
    {

        //getting info from user
        cout << "Enter the Name of the model: ";
        cin.ignore();
        getline(cin, model_name);
        cout << "Enter the Car Number: ";
        getline(cin, car_number);
        cout << "Enter the type of fuel: ";
        getline(cin, fuel_type);
        cout << "Enter the Number of KMs travelled by the car: ";
        cin >> km_travelled;
        cout << "Enter the max speed of the car(kmph): ";
        cin >> max_speed;
        cout << "Enter the number of seats in the car: ";
        cin >> no_of_seats;
        cout << "Enter the body type of the car: ";
        cin.ignore();
        getline(cin, body_type);

        //creating a car file and storing info in it
        ofstream car(".\\cars\\car" + to_string(n + 1) + ".txt");
        car << model_name << "\n";
        car << "Name of the model: " << model_name << "\n";
        car << car_number << endl;
        car << "Fuel Type: " << fuel_type << "\n";
        car << "KM Travelled: " << km_travelled << "\n";
        car << "Max speed of the car: " << max_speed << "\n";
        car << "Number of seats: " << no_of_seats << "\n";
        car << "Body Type: " << body_type << "\n";

        car.close();

        cout << "\nNew Car Model added successfully\n\n";

        system("pause");
        main_menu(); // returning to main menu
    }

    // function to display cars from available choices
    string car_menu_display()
    {
        car_files.choice_display();
        string opted = car_files.selection();
        return opted;
    }
    string car_num(){
       string a =  car_files.third_ln();

        return a;
    }
   

};

// rent class
class rent : car // inherited to use functions from car class
{
    string car_model;
    string car_no;
    int invoice_no;
    string contact_no;
    string address;
    int days;
    int rent_perd = 2000;
    float gst_per = 0.12;
    float gst;

public:
    int total_rent;
    // constructor to calculate rent
    rent()
    {
        car_model = car_menu_display(); // function from car class
        car_no = car_num();
        cout << "How many days you want to rent the car?" << endl;
        cin >> days;
        total_rent = rent_perd * days;
        gst = gst_per * total_rent;
    }
    // function to create invoice, display it and store it in a .txt file

    void invoice(string &name, int &j)
    {
        // calculating number of files in invoices
        DIR *dp;
        int t = 0;
        struct dirent *ep;
        dp = opendir(".\\invoices");
        while (ep = readdir(dp))
            t++;

        (void)closedir(dp);
        int k = t - 2;
        invoice_no = k + 1;
        cout << invoice_no;

        // opening the customer file to get customer data to create invoice
        ifstream cust(".\\customers\\customer" + to_string(j) + ".txt");
        getline(cust, name);
        string junk;
        getline(cust, junk);
        getline(cust, contact_no);
        getline(cust, address);
        
        // creating invoice
        system("cls");
         cout <<"Time: " << tell_time(1)<<endl<<endl;
        cout << "\t\t-------------------------INVOICE--------------------------------------------\n\n"
             << setw(10);
        cout << "\t\t\t"
             << R"(Rental Cars Services)" << setw(10) << " \t\t|  Invoice No. | | Date:  |" << endl;

        cout << "\t\t	___________________________________________________________________" << endl;
        cout << "\t\t	|"
             << "--------------------------------|" << setw(10) << "#" + invoice_no << " |\t"
             << tell_time(0)
             << " |" << endl;
        cout << "\t\t	| Customer Name:"
             << "-----------------|" << setw(10) << name << " |" << endl;
        cout << "\t\t	| Contact no.:"
             << "-------------------|" << setw(10) << contact_no << "|" << endl;
        cout << "\t\t	| Car Model :"
             << "--------------------|" << setw(10) << car_model << "|" << endl;
        cout << "\t\t	| Car No. :"
         << "----------------------|" << setw(10) << car_no << " |" << endl;
        cout << "\t\t	| Number of days :"
             << "---------------|" << setw(10) << days << " |" << endl;
        cout << "\t\t	| Your Rental Amount is :"
             << "--------|" << setw(10) << total_rent << " |" << endl;
        cout << "\t\t	| Address"
             << "-----------------------|" << setw(10) << address << " |" << endl;
        cout << "\t\t	| GST :"
             << "--------------------------|" << setw(10) << gst << " |" << endl;
        cout << "\t\t	 ________________________________________________________" << endl;
        cout << "\n";
        cout << "\t\t	| Total Rental Amount is :"
             << "-------|" << setw(10) << total_rent + gst << " |" << endl;
        cout << "\t\t	 ________________________________________________________" << endl;
        cout << "\t\t	 # This is a computer generated invoce and it does not" << endl;
        cout << "\t\t	 require an authorised signture #" << endl;
        cout << " " << endl;
        cout << "\t\t	######################################################" << endl;
        cout << "\t\t	You are advised to pay up the amount before due date." << endl;
        cout << "\t\t	Otherwise penelty fee will be applied" << endl;
        cout << "\t\t	######################################################" << endl;

        // creating a invoice file and storing customer invoice in it
        ofstream invoice(".\\invoices\\" + name + ".txt");

                 invoice <<"Time: " << tell_time(1)<<endl<<endl;
        invoice << "\t\t-------------------------INVOICE--------------------------------------------\n\n"
                << setw(10);
        invoice << "\t\t\t"
                << R"(Rental Cars Services)" << setw(10) << " \t\t|  Invoice No. | | Date:  |" << endl;

        invoice << "\t\t	___________________________________________________________________" << endl;
        invoice << "\t\t	|"
                << "--------------------------------|" << setw(10) << "#" + invoice_no << " |\t"
                << tell_time(0)
                << " |" << endl;
        invoice << "\t\t	| Customer Name:"
                << "-----------------|" << setw(10) << name << " |" << endl;
        invoice << "\t\t	| Contact no.:"
                << "-------------------|" << setw(10) << contact_no << "|" << endl;
        invoice << "\t\t	| Car Model :"
                << "--------------------|" << setw(10) << car_model << "|" << endl;
        invoice << "\t\t	| Car No. :"
         << "----------------------|" << setw(10) << car_no << " |" << endl;
        invoice << "\t\t	| Number of days :"
                << "---------------|" << setw(10) << days << " |" << endl;
        invoice << "\t\t	| Your Rental Amount is :"
                << "--------|" << setw(10) << total_rent << " |" << endl;
        invoice << "\t\t	| Address"
                << "---------------------------|" << setw(10) << address << " |" << endl;
        invoice << "\t\t	| GST :"
                << "--------------------------|" << setw(10) << gst << " |" << endl;
        invoice << "\t\t	 ________________________________________________________" << endl;
        invoice << "\n";
        invoice << "\t\t	| Total Rental Amount is :"
                << "-------|" << setw(10) << total_rent + gst << " |" << endl;
        invoice << "\t\t	 ________________________________________________________" << endl;
        invoice << "\t\t	 # This is a computer generated invoce and it does not" << endl;
        invoice << "\t\t	 require an authorised signture #" << endl;
        invoice << " " << endl;
        invoice << "\t\t	######################################################" << endl;
        invoice << "\t\t	You are advised to pay up the amount before due date." << endl;
        invoice << "\t\t	Otherwise penelty fee will be applied" << endl;
        invoice << "\t\t	######################################################" << endl;
        invoice.close();

        system("pause");
        main_menu(); // returning to main menu
    }
};

// customer class
class customer : protected files // inherited protected data members of files
{
protected:
    string customer_name;
    unsigned long long int contact_no;
    string address;
    string password;
    char ch;

public:
    // creating object of type files
    files customer_files;
    customer()
    {
        // calculating number of files in customers directory
        DIR *dp;
        i = 0;
        struct dirent *ep;
        dp = opendir(".\\customers");
        while (ep = readdir(dp))
            i++;

        (void)closedir(dp);
        n = i - 2;

        type = "customer";

        customer_files.make_files(n, type);
    }

    // function to add a new customer

    void add_customer()
    {
        //getting info from user
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, customer_name);
        cout << "Enter a new password: ";
        getline(cin, password);
        cout << "Enter your contact number: ";
        cin >> contact_no;
        cout << "Enter your address: ";
        cin.ignore();
        getline(cin, address);
        
        //creating a customer file and adding info to it
        ofstream customer(".\\customers\\customer" + to_string(n + 1) + ".txt");
        customer << customer_name << endl;
        customer << password << endl;
        customer << contact_no << "\n";
        customer << address << "\n";
        customer.close();
        cout << "\nNew customer information added successfully.\n\n";
        system("pause");
        main_menu();
    }

    // function to login previous customer:

    void customer_login()
    {
        password = "";
        cout << "Enter your name: ";
        getline(cin, customer_name);
       
        cout << "Enter password: ";
         ch = _getch();
    while (ch != 13)
    { // character 13 is 'enter button'
        password.push_back(ch);
        cout << '*';
        ch = _getch();
    }
   

        for(i = 1; i <= n; i++)
        {
            string existing_customers = "";
            string existing_pass = "";
            ifstream in(".\\customers\\customer" + to_string(i) + ".txt");
            getline(in, existing_customers);
            getline(in, existing_pass);

            if (existing_customers == customer_name && existing_pass == password)
            {
            
                int choice;
                cout << "\n\nCustomer logged in successfully.\n" << endl;
                // logged in customer options:
                cout << "select an option: " << endl;
                cout << "\t\t	___________________________________________________________________" << endl;
                cout << "\n\t\t                       1) Book a new car                   " << endl;
                cout << "\n\t\t                       2) See previous invoice                 " << endl;
                cin >> choice;

                if (choice == 1)
                {
                    system("cls");
                    int k = i;
                    // creating an object of type rent to call it's cunstructor to book a car
                    rent r1;
                    // calling invoice function of r1 object
                    r1.invoice(customer_name, k);
                }
                else if (choice == 2)
                {
                    
                    // calling function to open previous invoice
                    open_invoice(customer_name);
                }
                // default :
                else{ cout << "Enter a valid choice.";}
                break;
            }
            else if(i == n){
                // output if customer don't exist
        
            system("cls");
            cout << "Couldn't log in, please check whether the name and password are correct.\n" << endl;
            customer_login();         
            }
            in.close();
        }
      
    }

    // displaying list of all customers:
    void customer_menu_display()
    {
        customer_files.choice_display();
        system("pause");
        main_menu();
    }
};

// main function:
int main()
{
    
    //calling welcome function to show initial text
    welcome();

    // calling main menu function to display menu
    main_menu(); 
    
    return 0;
}
// login function body -

int login()
{
    string pass = "";
    char ch;
    cout << "\t\t\t\t\t------------------------------\n\n";
    cout << "\t\t\t\t\tADMIN LOGIN \n\n";
    cout << "\t\t\t\t\t------------------------------\n\n";
    cout << "\t\t\t\t\tEnter Password: ";
    ch = _getch();
    while (ch != 13)
    { // character 13 is 'enter button'
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if (pass == PASS)
    {
        cout << "\n\n\nAccess Granted! \n";
        system("PAUSE");
        system("CLS");
    }
    else
    {
        system("cls");
        cout << "\nWrong Credentials...\nPlease Try Again\n\n";
        login();
    }
}
// main - menu function body-

void main_menu()
{
    system("cls");
    system("color 02");
    int choice;
    cout << "\t\t	___________________________________________________________________" << endl;
    cout << "\n\t\t                       Main Menu                  " << endl;
    cout << "\n\t\t                       1) Customer Access                   " << endl;
    cout << "\n\t\t                       2) Admin Access                  " << endl;
    cout << "\n\t\t                       3) Exit                " << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    start:
    case 1:
        system("cls"); // clearing terminal
        // calling customer menu for choice - 1
        
        customer_menu();

        break;
    case 2:
        system("cls");
        //admin access login
        login();
        // calling admin menu for choice - 2

        admin_menu();
        break;
    case 3:
        break;
    default:
        cout << "Enter a valid choice: ";
        cin >> choice;
        goto start;
    }
}

// body of customer_menu function -

void customer_menu()
{
    int choice;
    // created a C1 object of type customer to access it's functions
    customer C1;
    cout << "\t\t	___________________________________________________________________" << endl;
    cout << "\n\t\t                       Customer Menu                  " << endl;
    cout << "\n\t\t                       1) Add New Customer                  " << endl;
    cout << "\n\t\t                       2) Customer Login                  " << endl;
    // getting user choice -
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    start:
    case 1:
        // if choice is 1 - call add_customer function to add a customer
        system("cls");

        C1.add_customer();
        break;
    case 2:
        // if choice is 2 - call customer_login function to login a customer
        system("cls");
        cin.ignore();
        C1.customer_login();
        break;
    default:
        cout << "Enter a valid choice: ";
        cin >> choice;
        goto start;
    }
}

// body of admin_menu() function-

void admin_menu()
{
    int choice;
    // created car1 object of type car to access functions/methods of car
    car car1;
    // created C2 object of type customer to access its function below
    customer C2;
    cout << "\t\t	___________________________________________________________________" << endl;
    cout << "\n\t\t                       Admin Menu                  " << endl;
    cout << "\n\t\t                       1) Add New Car Model                  " << endl;
    cout << "\n\t\t                       2) Car Model list                " << endl;
    cout << "\n\t\t                       3) Customer list                  " << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    start:
    case 1:
        // if choice if 1 then calling AddCar() function of car1 object
        system("cls");

        car1.AddCar();
        break;
    case 2:
        car1.car_menu_display();
        system("pause");
        break;
    case 3:
        // if choice is 2 then displaying list f customers
        system("cls");

        C2.customer_menu_display();
        break;
    default:
        cout << "Enter a valid choice: ";
        cin >> choice;
        goto start;
    }
}

//body of tell_time() function
string tell_time(int x)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int year, month, day, hr, min, sec;
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;

    hr = ltm->tm_hour;
    min = +ltm->tm_min;
    sec = ltm->tm_sec;
    string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    string time = to_string(hr) + ":" + to_string(min) + ":" + to_string(sec);

    if (x == 1)
    {
        return time;
    }
    else
    {
        return date;
    }
}

// function to open previous invoice
void open_invoice(string &name) // getting customer name as argument
{

    // opening customer invoice file
    system("cls");
    ifstream open(".\\invoices\\" + name + ".txt");
    // if file don't exists then show no previous bookings.
    if (!open)
    {
        cout << "No previous bookings...\n";
    }
    // else show the previous invoice
    char str[5000]; // character array of index 5000
    // while file doesn't reach end
    while (open)
    {
        open.getline(str, 5000); // getting content of invoice in str
        if (open)
            cout << str << endl; // printing content of str in terminal
    }
    open.close();    // closing invoice file
    system("pause"); // prints "press any key to continue..." in terminal

    main_menu();
}

//body of welcome-
void welcome()
{
    system("cls");

    ifstream in("welcome.txt"); // displaying welcome ASCII image text on output screen fn1353

    if (!in)
    {
        
    }
    char str[1000];
    while (in)
    {
        in.getline(str, 1000); // delim defaults to '\n' cp
        if (in)
            cout << COLOR_MAGENTA << str << COLOR_RESET << endl;
    }
    in.close();
    sleep(1);

    
    system("cls");
    cout << "\n\n\n Loading files please wait.../";
    sleep(1);
    system("cls");
    cout << "\n\n\n Loading files please wait...-";
    sleep(1);
    system("cls");
    cout << "\n\n\n Loading files please wait...\\";
    sleep(1);
     system("cls");
    cout << "\n\n\n Loading files please wait...|";
    sleep(1);
    system("cls");
   
    
}
