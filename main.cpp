#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

bool nameValid(string);
bool mobValid(string);

class contact
{
	string name;
	string mob;

public:
	//Initialising the contact to a default value
	contact(): name(""), mob("")
	{}
	//Creating a function to show all the contacts
	bool show()
	{
		if (name != "")
		{
			cout << name << "\t" << mob <<endl;
			return 1; //Success
		}
		else
		{
			return 0; //Failure
		}
	}
	//Creating a function to search for contacts
	bool show(string searchTerm)
	{
		if (searchTerm == name)
		{
			cout << name << "\t" << mob << endl;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//Creating a function to check if a name exists
	bool nameExist(string tName)
	{
		if (tName == name)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//Initialising the contacts to new values
	bool add(string newName, string newMob)
	{
		if (name == "")
		{
			name = newName;
			mob = newMob;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//Creating a function to edit the contact details
	bool edit(string);
	//Sets the contact details to its default values i.e. The values are erased
	bool erase(string newName)
	{
		if (newName == name)
		{
			name = "";
			mob = "";
			return 1;
		}
		else
		{
			return 0;
		}
	}
};
//To edit the contact
bool contact::edit(string newName)
{
	string newMob;
	if (newName == name)
	{
		cout << "Enter a new name: ";
		cin >> newName;
		cout << "Enter a new mobile number: ";
		cin >> newMob;

		name = newName;
		mob = newMob;
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	contact person[100];
	string tempName, tempMob;
	int choice, i, counter;
	bool flag;
	bool cancelFlag;

	cout << "\tPHONEBOOK\t" <<endl;
	do
	{
		cout << "\n\n\n";
		cout << "0. Show Contacts" << endl;
		cout << "1. Add Contacts" << endl;
		cout << "2. Edit Contacts" << endl;
		cout << "3. Delete Contact" << endl;
		cout << "4. Search Contact" << endl;
		cout << "5. Quit" << endl;
		cin >> choice;

		system("cls");
		cancelFlag = 0;
		flag = 0;
		counter = 0;

		switch (choice)
		{
		case 0:
			cout << "Showing Contacts:" << endl;
			for (i = 0; i < 100; i++)
			{
				if (person[i].show())
					flag = 1;
			}
			if (!flag)
				cout << "No Contact Found." << endl;
			break;
		case 1:
			cout << "Add New Contact:" << endl;
			counter = 0;
//Creating a loop to search until the correct name and number are entered
			do
			{
				flag = 0;
				if (counter)
				{
					cout << "Try again.\t\t\t\tPress $ to cancel." << endl;
				}
//Counts how many times the loop runs
				counter++;
				cout << "Name: ";
				cin >> tempName;
				cout << "Mobile Number: ";
				cin >> tempMob;
//To check whether the name entered exists
				for (i = 0; i < 100; i++)
				{
					if (person[i].nameExist(tempName))
					{
						cout << "The name you entered already exists. Enter a different name." <<endl;
						flag = 1;
						break;
					}
				}

			} while (!nameValid(tempName) || flag || !mobValid(tempMob));
//to add a new number and name to the phonebook
			for(i=0; i<100; i++)
				if (person[i].add(tempName, tempMob))
				{
					cout << "Contact added successfully!" << endl;
					flag = 1;
					break;
				}
			if (!flag)
			{
				cout << "Memory full. Delete some contacts and try again." << endl;
				break;
			}
		case 2:
			cout << "Enter a contact name to edit.\n" << endl;
			cin >> tempName;
			for (i = 0; i < 100; i++)
			{
				if (person[i].edit(tempName))
				{
					cout << "Contact Edited Successful";
					flag = 1;
					break;
				}

				if (!flag)
				{
					cout << "Contact not found" << endl;
					break;
				}
			}
		case 3:
			do
			{
				if (counter)
				{
					cout << "Try again." << endl;
					counter++;
					cout << "Enter a contact name to delete." << endl;
					cin >> tempName;
				}
				//Final Confirmation for deletion
				for (i = 0; i < 100; i++)
				{
					if (person[i].nameExist(tempName))
					{
						flag = 1;
						cout << "Are you sure you want to delete this contact?(1/0)" << endl;
						int yes;
						cin >> yes;
						if (!yes)
						{
							system("cls");
							cancelFlag = 1;
						}
						break;
					}
					if (!flag)
						cout << "Contact name not found." << endl;
					if (cancelFlag)
						break;
					//To delete the contact
					if (flag)
					{
						for(i=0; i<100; i++)
							if (person[i].erase(tempName))
							{
								cout << "Deleted successfully." << endl;
								break;
							}
					}
				}
			} while (!flag);
			break;
		case 4:
			do
			{
				if (counter)
					cout << "Try again" << endl;
				counter++;
				cout << "Search for a name: \t\t\t\tPress $ to cancel\n";
				cin >> tempName;
			//The cancel operation
				if (tempName == "$")
				{
					system("cls");
					break;
				}
				for(i=0; i<100; i++)
					if (person[i].show(tempName))
					{
						flag = 1;
						break;
					}
				if (!flag)
					cout << "Contact not found" << endl;
			} while (!flag);
				break;
		case 5:
			return 0;
			break;
		}
	}while (1);
	_getch();
	return 0;
}
//To validate the contact name
bool nameValid(string tName)
{
	if (tName.size() > 20)
	{
		cout << "Invalid entry. Enter a name within 20 characters." << endl;
		return 0;
	}
	else if (tName == "")
	{
		cout << "Invalid entry. Name can not be blank." << endl;
		return 0;
	}
	else
		return 1;
}
//To validate the mobile number
bool mobValid(string tMob)
{
	if (tMob.size() > 13 || tMob.size() < 10)
	{
		cout << "Invalid number.\nEnter a number between 10 and 13 characters" << endl;
		return 0;
	}
	else if (tMob == "")
	{
		cout << "Invalid entry. Number can not be blank." << endl;
		return 0;
	}
	else
		return 1;
}
