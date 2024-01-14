#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <cstdlib>
using namespace std;

using namespace std;

string readLine(string header) {
	cout << "\n" << header;
	string line;
	getline(cin, line);
	return line;
}

class ToDoItem {

	public:

		string text = "";
		
		int id;

		bool isCompleted = false;

		void toggleCompleted() {
			isCompleted = !isCompleted;
		}

};

class ToDoList {

	private:

		list<ToDoItem> _ToDoList;
		int itemCount = 0;
		int version = 17;

	public:

		void  Update() {

			Render();
			cout << " [q]uit\n [a]dd\n [c]omplete\n [d]elete\n [clear]\n";
			string input = readLine(" write the first letter : ");

			if (input == "a")
				Add();
			else if (input == "c")
				Complete();
			else if (input == "d")
				Delete();
			else if (input == "q")
				exit(0);
			else if (input == "clear")
				_ToDoList.clear();

		}

		void Render() {

			//clear
			system("cls");

			cout << " MW TODOO V" +	to_string(version) + "\n";

			cout << " --------------------------------------------\n";

			for (const auto& _ToDoItem: _ToDoList)
			{

				cout << "  ------------------------------------------\n";

				string itemString = "  " + to_string(_ToDoItem.id) + " | " + _ToDoItem.text + " | ";
				
				if(_ToDoItem.isCompleted)
					itemString += "completed";
				else itemString += "isnt completed";

				cout << (" " + itemString + "\n");

				cout << "  ------------------------------------------\n";

			}

			cout << " --------------------------------------------\n";

		}

		void Add() {

			ToDoItem item = ToDoItem();

			itemCount++;
			item.id = itemCount;

			item.text = readLine(" new Item Text : ");

			_ToDoList.push_back(item);

			Store();

		}

		void Complete() {

			int id;
			cout << " The Complete ID : ";
			cin >> id;

			for (auto _ToDoItem = _ToDoList.rbegin(); _ToDoItem != _ToDoList.rend(); _ToDoItem++) {

				bool hasSameID = _ToDoItem->id == id;

				if (hasSameID) {

					_ToDoItem->toggleCompleted();

					break;

				}

			}

			Store();

		}

		void Delete() {

			int id;
			cout << " The Delete ID : ";
			cin >> id;

			auto it = _ToDoList.begin();
			while (it != _ToDoList.end()) {
				if (it -> id == id) {
					it = _ToDoList.erase(it);
				}
				else {
					++it;
				}
			}

			Store();

		}

		void Store() {
			//Build Later....
		}

};

int main()
{
	system("title MW TODOO V17");
	ToDoList _ToDoList;
	while (true) {
		_ToDoList.Update();
	}
}