
// selection.cpp code -

// class for files mangament
class files
{
protected:
    // protected data members accesed by child class only
    string type = ""; // type of file
    int i = 0;
    int n = 0;
    int a = 0;
    string file_names[10] = {}; // array to store file names
public:
    // default constructor for parent class
    files()
    {
    }
    // function to get names of all files in a directory
    void make_files(int &j, string &file_type)
    {
        type = file_type;
        a = j;
        for (i = 1; i <= a; i++)
        {
            n = i - 1;
            file_names[n] = ".\\" + type + "s\\" + type + to_string(i) + ".txt";
        }
    }

    // function to display choice menu
    void choice_display()
    {
        
        string option = "";
        string addinfo = "";
        cout << "\nList of " << type << "s\n\n";
        for (i = 1; i <= a; i++)
        {
            n = i - 1;
            ifstream in(file_names[n]);
            if (!in.fail())
            {
                getline(in, option);
                cout << COLOR_RED << i << "." << option << COLOR_RESET;
                getline(in, addinfo);
                getline(in, addinfo);
                cout << COLOR_YELLOW << " (" << addinfo << ")" << COLOR_RESET << endl;
            }
            else
                cout << " ...";
        }
    }

    // function to display content of user selected option from menu
    string selection()
    {
        // void choice_display();
       
        cout << COLOR_BLUE << "\n\nSelect an Option from above to see details: " << COLOR_RESET;
        cin >> n;
        if (cin.fail())
        {
            system("cls");
            cout << "\nEnter valid choice\n\n";
            return selection();
        }
        i = n - 1;
        string result = "";
        string return_result;
        string selected = file_names[i];
        ifstream in(selected);
        system("cls");
        cout << "\n\nSpecifications :\n\n";

        while (in.eof() == 0)
        {
            getline(in, result);
            cout << COLOR_CYAN << result << COLOR_RESET << endl;
        }
        in.close();

        ifstream inf(selected);
        getline(inf, return_result);
        return return_result;
    }
    
    //function to return third line of a file
     string third_ln(){
        string returnln;
        ifstream in(file_names[i]);
        getline(in, returnln);
        getline(in, returnln);
        getline(in, returnln);
        
        return returnln;
    }
};

// -End of selection.cpp-
