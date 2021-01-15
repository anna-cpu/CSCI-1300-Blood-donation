#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

//struct
struct donor
{
	int id;
	string name;
	long long int phone;
	int age;
	string type;
	int amount;
};

//global variable
const int ENTRIES = 100;

int y = 0;	// counts the number of items in the file so that the last digit is not re-printed and the file is not over written
int acc;	// real count

// global arrays
int total[8];

//most pointers are used all over the code to print arrays esp. the calc function
//functions
void addnew(donor array[]);
void deletedonor(donor array[]);
void print(donor array[]);
void update(donor array[]);
void calc(donor array[], int i);
bool bloodchecker(donor array[], int i);
bool amountchecker(donor array[], int i);
void write(donor array[], int acc);
void read(donor array[]);

int main()
{
	// variables
	string choice;

	// arrays
	donor alpha[ENTRIES];

	
	read(alpha);
	acc = y - 1;	//avoids the file from overwriting

	while (true)
	{
		cout << "\t\t==========*******************************************==========" << endl;
		cout << "\t\t\t\t  Blood Donation Management System   " << endl;
		cout << "\t\t==========*******************************************==========" << endl;
		cout << "\t\t\t\t Enter 1 to create new Donor:" << endl;
		cout << "\t\t\t\t Enter 2 to update  Donor details:" << endl;
		cout << "\t\t\t\t Enter 3 to delete Donor:" << endl;
		cout << "\t\t\t\t Enter 4 to view Donor:" << endl;
		cout << "\t\t\t\t Enter 5 to exit:" << endl;
		cout << "\t\t=============================================================" << endl;
		cout << "\t\t=============================================================" << endl;

		cin >> choice;

		if (choice == "1")
		{
			addnew(alpha);

		}
		else if (choice == "2")
		{
			update(alpha);
		}
		else if (choice == "3")
		{
			deletedonor(alpha);
		}
		else if (choice == "4")
		{
			print(alpha);
		}
		else if (choice == "5")
		{
			cout << " Thank you!" << endl;

			break;
		}
		else
		{
			cout << "please enter a valid option" << endl;
		}
	}

	return 0;
}

// FUNCTION FOR CREATING DATA
void addnew(donor array[])
{
	//variables
	int num;
	int no = 105;
	// acc = y-1;// avoids the file from overwriting

	if (acc == -1)
	{
		acc = 0;
	}

	// this if is needed coz acc can be negative when the file is empty 

	cout << "Enter the number of donors you want to create " << endl;
	cin >> num;

	for (int i = 0; i < num; i++)
	{
		array[acc].id = no + acc;
		cout << "The assigned ID for this  new donor is " << array[acc].id << endl;
		cout << "Enter the name of the donor: " << endl;
		cin >> (array + acc)->name;
		cout << "Enter the phone number of the donor: " << endl;
		cin >> (array + acc)->phone;
		cout << "Enter the age of the donor: " << endl;
		cin >> (array + acc)->age;
		if (array[acc].age < 18 || array[acc].age > 60)
		{
			cout << "We are sorry :(donor " << array[0].id + acc << " does not  meet the age requirments";
			(array + acc)->id = 0;
			(array + acc)->name = "0";
			(array + acc)->phone = 0;
			(array + acc)->age = 0;
			break;
		}

		cout << "Enter the blood type of the donor: " << endl;
		cin >> (array + acc)->type;
		while (bloodchecker(array, acc) == 0)
		{
			cout << "Please Enter a valid blood type: " << endl;
			cin >> (array + acc)->type;
		}

		cout << "Enter the number of packages to be donated by the donor: " << endl;
		cin >> (array + acc)->amount;
		while (amountchecker(array, acc) == 0)
		{
			cout << "A maximum of 5 packages and a minimum of 1 package can be donated at a given time " << endl;
			cout << "Please enter a valid amount: " << endl;
			cin >> (array + acc)->amount;
		}

		write(array, acc);

		acc = acc + 1;
	}
}

// function for checking if the blood type is correct
bool bloodchecker(donor array[], int i)
{
	bool flag = true;

	if (array[i].type != "o+" && array[i].type != "b+" && array[i].type != "o-" && array[i].type != "b-" &&
		array[i].type != "O+" && array[i].type != "B+" && array[i].type != "O-" && array[i].type != "B-" &&
		array[i].type != "a+" && array[i].type != "ab+" && array[i].type != "a-" && array[i].type != "ab-" &&
		array[i].type != "A+" && array[i].type != "AB+" && array[i].type != "A-" && array[i].type != "AB-")
	{
		flag = 0;
	}

	return flag;

}

// function that checks if the amount of blood to be donated is correct
bool amountchecker(donor array[], int i)
{
	bool flag = true;

	if (array[i].amount > 5 || array[i].amount <= 0)
	{
		flag = false;
	}

	return flag;
}

//read from file
void read(donor array[])
{
	ifstream putout("blooddonation.txt");
	if (putout.is_open()) {}
	else
	{
		cout << "ERROR OCCURRED FILE NOT OPEN FOR READING\n";
	}

	while (putout.good())
	{
		putout >> array[y].id >> array[y].name >> array[y].phone >> array[y].age >> array[y].type >> array[y].amount;
		y++;

	}

	putout.close();
}

//to write on file
void write(donor array[], int i)
{
	ofstream putin("blooddonation.txt");

	if (putin.is_open())
	{
		for (int i = 0; i <= acc; i++)
		{
			putin << array[i].id << "\t\t" << array[i].name << "\t\t\t" << array[i].phone << "\t\t\t" << array[i].age << "\t\t" << array[i].type << "\t\t " << array[i].amount << endl;
		}
	}
	else
	{
		cout << "ERROR OCCURRED FILE NOT OPEN FOR WRITING\n";
	}

	putin.close();
}

// FUNCTION FOR UPDATING DATA
void update(donor array[])
{
	//variables
	int renew, found;
	string sure;

	//read(array);	//this read file reads from file to update it

	cout << "Please enter the ID number of the donor details that you want to update" << endl;
	cin >> renew;
	for (int i = 0; i < acc ; i++)
	{
		found = i;
		if (renew == array[i].id)
		{
			break;
		}
	}

	if (found == acc )
	{
		cout << "donor not found" << endl;

	}
	else
	{
		cout << " are certain you want to update the information of donor " << array[found].name << " with ID number " << array[found].id << " ? " << endl;
		cout << "Enter 1 for yes and any key for no " << endl;
		cin >> sure;
		if (sure != "1")
		{
			cout << cout << " donor details not updated " << endl;

		}
		else if (sure == "1")
		{
			array[found].id = renew;
			cout << "The ID for this  donor is " << array[found].id << endl;
			cout << "Enter the name of the donor: " << endl;
			cin >> array[found].name;
			cout << "Enter the phone number of the donor: " << endl;
			cin >> array[found].phone;
			cout << "Enter the age of the donor: " << endl;
			cin >> array[found].age;
			if (array[found].age < 18 || array[found].age > 60)
			{
				cout << "We are sorry :(donor " << array[0].id << " does not  meet the age requirements" << endl;
				cout << "Please Enter a valid age: " << endl;
				cin >> array[found].age;

			}

			cout << "Enter the blood type of the donor: " << endl;
			cin >> array[found].type;
			while (bloodchecker(array, found) == 0)
			{
				cout << "Please Enter a valid blood type: " << endl;
				cin >> array[found].type;
			}

			cout << "Enter the number of packages to be donated by the donor: " << endl;
			cin >> array[found].amount;
			while (amountchecker(array, found) == 0)
			{
				cout << "A maximum of 5 packages and a minimum of 1 package can be donated at a given time. " << endl;
				cout << "Please enter a valid amount: " << endl;
				cin >> array[found].amount;
			}

			write(array, found);
			cout << "data successfully updated " << endl;
		}
	}
}

// FUNCTION FOR DELETING DATA
void deletedonor(donor array[])
{
	//variables
	string pass = "eop";//password
	string word;
	int checkID;
	string sure = "1";
	int temp;

	cout << " Only authorized personnel can delete donor data " << endl;
	cout << " Please enter password for verification: " << endl;
	cin >> word;
	if (word != pass)
	{
		cout << "you are not authorized to delete data" << endl;

	}
	else if (word == pass)
	{
		cout << "Enter the ID number of the donor you would like to delete: " << endl;
		cin >> checkID;

		for (int i = 0; i < acc; i++)
		{
			temp = i;
			if (checkID == array[temp].id)

				break;

		}

		if (temp == acc)
			cout << "invalid id number";
		else
		{
			cout <<"------------------------------------------------------------------------\n";
			cout << " are certain you want to delete donor " << array[temp].name << " with ID number " << array[temp].id << " ? " << endl;
			cout << "Enter 1 for yes and any key for no " << endl;
			cout <<"------------------------------------------------------------------------\n";
			cin >> sure;
			if (sure == "1")
			{
				(array + temp)->id = 0;
				(array + temp)->name = "0";
				(array + temp)->phone = 0;
				(array + temp)->age = 0;
				(array + temp)->type = "0";
				(array + temp)->amount = 0;

				write(array, acc);
				cout <<"------------------------------------------------------------------------\n";
				cout << " donor successfully deleted" << endl;
				cout <<"------------------------------------------------------------------------\n";
			}
			else
			    cout <<"------------------------------------------------------------------------\n";
				cout << " donor not deleted" << endl;
				cout <<"------------------------------------------------------------------------\n";
		}
	}
}

// FUNCTION FOR PRINTING
void print(donor array[])
{
	//variables 
	string opt;
	int view, found;
    cout <<"------------------------------------------------------------------------\n";
	cout << "Enter 1 to view the information of one registered donor. " << endl;
	cout << "Enter 2 to view all available information. " << endl;
	cout << "Enter 3 to view all available blood types and number of packages for each type. " << endl;
	cout <<"------------------------------------------------------------------------\n";
	cin >> opt;

	if (opt == "3")

	{

		//the first for loob turns everything to zero, to avoid double count
		if (acc >= 0)
		{
			for (int i = 0; i <= acc; i++)
			{
				total[i] = 0;
			}

			for (int i = 0; i < acc; i++)
			{
				calc(array, i);
			}
		}
		
		cout <<"---------------------------------------------------------------------\n";

		cout << total[0] << "  Packages of blood type A+" << endl;
		cout << total[1] << "  Packages of blood type B+" << endl;
		cout << total[2] << "  Packages of blood type O+" << endl;
		cout << total[3] << "  Packages of blood type AB+" << endl;
		cout << total[4] << "  Packages of blood type A-" << endl;
		cout << total[5] << "  Packages of blood type B-" << endl;
		cout << total[6] << "  Packages of blood type O-" << endl;
		cout << total[7] << "  Packages of blood type AB-" << endl;
		cout <<"---------------------------------------------------------------------\n";


	}
	else if (opt == "1")
	{
		cout << "Please enter the ID number of the donor details that you want to view" << endl;
		cin >> view;
		for (int i = 0; i <= acc; i++)
		{
			found = i;
			if (view == array[i].id)
			{
				break;
			}
		}

		if (found == acc)
		{
			cout <<"------------------------------------------------------------------------\n";
			cout << "Donor not found" << endl;
			cout <<"------------------------------------------------------------------------\n";
		}
		else
		{
			cout <<"------------------------------------------------------------------------\n";
			cout << "The  donor's  ID is:  " << (array + found)->id << endl;
			cout << "The donor's name is:  " << (array + found)->name << endl;
			cout << "The donor's phone number is:  " << (array + found)->phone << endl;
			cout << "The donor's age is:  " << (array + found)->age << endl;
			cout << "The donor's' blood type is:  " << (array + found)->type << endl;
			cout << "The number of packages  donated by the donor: " << (array + found)->amount << endl;
			cout <<"------------------------------------------------------------------------\n";

		}
	}
	else if (opt == "2")
	{
		cout << "Donor ID \t Donor name \t\t\tPhone \t\t\t Age \t Blood type \t Packages" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 0; i < acc; i++)
		{
			cout << (array + i)->id << " \t\t " << (array + i)->name << "\t\t\t     " << (array + i)->phone << "\t\t\t  " << (array + i)->age << "\t\t" << (array + i)->type << "\t\t " << (array + i)->amount << endl;

		}
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	else
	{   cout <<"------------------------------------------------------------------------\n";
		cout << "Invalid entry!" << endl;
		cout <<"------------------------------------------------------------------------\n";
	}
}

// FUNCTION FOR CALCULATING AMOUNT 

void calc(donor array[], int i)
{
	donor *aryptr = array;

	if ((aryptr + i)->type == "a+" || (aryptr + i)->type == "A+")
	{
		total[0] = total[1] + (aryptr + i)->amount;
	}
	else if ((aryptr + i)->type == "b+" || (aryptr + i)->type == "B+")
	{
		total[1] = total[1] + (aryptr + i)->amount;
	}
	else if ((aryptr + i)->type == "o+" || (aryptr + i)->type == "O+")
	{
		total[2] = total[2] + (aryptr + i)->amount;
	}
	else if ((aryptr + i)->type == "ab+" || (aryptr + i)->type == "AB+")
	{
		total[3] = total[3] + (aryptr + i)->amount;
	}
	else if ((aryptr + i)->type == "a-" || (aryptr + i)->type == "A-")
	{
		total[4] = total[4] + (aryptr + i)->amount;
	}
	else if ((aryptr + i)->type == "b-" || (aryptr + i)->type == "B-")
	{
		total[5] = total[5] + (aryptr + i)->amount;
	}
	else if ((aryptr + i)->type == "o-" || (aryptr + i)->type == "O-")
	{
		total[6] = total[6] + (aryptr + i)->amount;
	}
	else if ((aryptr + i)->type == "ab-" || (aryptr + i)->type == "AB-")
	{
		total[7] = total[7] + (aryptr + i)->amount;
	}
}

