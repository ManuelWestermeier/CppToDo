#include <iostream>
#include <string>
#include <list>
//#include <algorithm>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void writeFile(string fileName, string data) {

	//open file
	ofstream MyFile(fileName);
	//write file
	MyFile << data;
	//close file
	MyFile.close();

}

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

int str2int(const string& str) {
	stringstream ss(str);
	int num;
	if ((ss >> num).fail())
	{
		return 0;
	}
	return num;
}

string replace(string original, char find, string replacer) {

	string new_str;

	for (int i = 0; i < original.length(); i++) {
		if (original.at(i) == find)
			new_str += replacer;
		else new_str += original[i];
	}
	
	return new_str;

}

class ToDoList {

	private:

		list<ToDoItem> _ToDoList;
		int itemCount = 0;
		string V = " 1.0.45";

	public:

		void  Update() {

			Render();
			string input = readLine(" write the first letter : ");

			if (input.length() == 0)
				input = "#";

			char inputFunction = tolower(input.at(0));

			if (inputFunction == 'a')
				Add();
			else if (inputFunction == 'c')
				Complete();
			else if (inputFunction == 'd')
				Delete();
			else if (inputFunction == 'q')
				exit(0);
			else if (inputFunction == 'r')
				_ToDoList.clear();
			else if (inputFunction == 'h')
				StoreAsHTML();

			Store();

		}

		void Store() {

			string out = "";
			list<ToDoItem>::iterator it;
			int i = 0;
			bool isFirstTry = true;

			for (it = _ToDoList.begin(); it != _ToDoList.end(); ++it) {

				string chunk;
				//check if it isnt the first item
				if (isFirstTry)
					isFirstTry = false;
				else chunk += '\n';
				//Is Completed
				chunk += (char)(int)it->isCompleted;

				//Content
				chunk += it->text;
				//Add the relative string	
				out += chunk;

			}

			writeFile(".tododata", out);

			//system("attrib +h .tododata");

		}

		void StoreAsHTML() {

			string out = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF - 8\">  <style>* {margin: 5px;padding: 5px;font-family: system-ui, -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;}</style><meta name=\"viewport\" content=\"width = device - width, initial - scale = 1.0\"><title>ToDos</title></head><body>";
			
			list<ToDoItem>::iterator it;
			int i = 0;
			bool isFirstTry = true;

			for (it = _ToDoList.begin(); it != _ToDoList.end(); ++it) {

				string chunk;
				i++;

				//Is Completed
				if (it->isCompleted)
					chunk += "complete ";
				else chunk += "incomplete ";


				//Content
				chunk += replace(it -> text,'<', "< ");

				//check if it isnt the first item
				if (isFirstTry)
					isFirstTry = false;
				else chunk += "<br>";

				//Add the relative string	
				out += chunk;

			}

			out += "</body></html>";

			writeFile("todoadata.html", out);

			system("start todoadata.html");

			this_thread::sleep_for(2s);

			system("del \"./todoadata.html\"");

		}

		void Render() {

			string output = "";

			output += " MW TODOO V" +	V + "\n";

			output += "--------------------------------------------\n";

			for (const auto& _ToDoItem: _ToDoList)
			{

				output += "  ------------------------------------------\n";

				string itemString = "  " + to_string(_ToDoItem.id) + " | " + _ToDoItem.text + " | ";
				
				if(_ToDoItem.isCompleted)
					itemString += "completed";
				else itemString += "incomplete";

				output += (" " + itemString + "\n");

				output += "  ------------------------------------------\n";

			}

			output += " --------------------------------------------\n";

			output += " [q]uit\n [a]dd\n [c]omplete\n [d]elete\n [r]emove all\n [h]store ss HTML\n";


			//clear
			system("cls");
			//Render
			cout << output.c_str();

		}

		void Add() {

			ToDoItem item = ToDoItem();

			itemCount++;
			item.id = itemCount;

			item.text = readLine(" new Item Text : ");

			_ToDoList.push_back(item);

		}

		void Complete() {

			string idStr = readLine(" The Complete ID : ");

			int id = str2int(idStr);

			for (auto _ToDoItem = _ToDoList.rbegin(); _ToDoItem != _ToDoList.rend(); _ToDoItem++) {

				bool hasSameID = _ToDoItem -> id == id;

				if (hasSameID) {

					_ToDoItem -> toggleCompleted();

					break;

				}

			}

		}

		void Delete() {

			string idStr = readLine(" The Delete ID : ");
			int id = str2int(idStr);

			auto it = _ToDoList.begin();
			while (it != _ToDoList.end()) {
				if (it -> id == id) {
					it = _ToDoList.erase(it);
				}
				else {
					++it;
				}
			}

		} 

		void start() {

			//Set Title
			string title = "title MW TODOO V" + V;
			system(title.c_str());

			ReadStorage();

		}

		void ReadStorage() {

			ifstream dataFile;

			string dataLines[1000];

			dataFile.open(".tododata");

			if (dataFile.fail())
				return;

			int line = 0;

			while (!dataFile.eof()) {

				//read line
				getline(dataFile, dataLines[line]);
				line++;

			}

			dataFile.close();

			//Loop For All Lines
			for (int i = 0; i < line; i++)
			{
				string ToDoData = dataLines[i];
				//Add To The Itemcout 1
				itemCount++;
				//Create The ToDoy
				ToDoItem _ToDo;
				//Add ID
				_ToDo.id = itemCount;
				//Add Complete
				_ToDo.isCompleted = (bool)(int)ToDoData.at(0);
				//Remove first character because it is the completed boolean
				ToDoData.erase(0, 1);
				//Add ToDo Text
				_ToDo.text = ToDoData;
				//Add the ToDo to the list
				_ToDoList.push_back(_ToDo);

			}

		}

};

int main()
{
	//Create The List
	ToDoList _ToDoList;
	//Start
	_ToDoList.start();
	//Update
	while (true)
		_ToDoList.Update();

}