#include <iostream>
#include <string>
#include "List.h"
#include "List.cpp"
#include "Map.h"
#include "Map.cpp"

using namespace std;

struct Element {
	char key = 0;
	int amount = 0;
	Element* left = nullptr;
	Element* right = nullptr;

	Element() {
		key = 0;
		amount = 0;
	}

	Element(char key, int amount) {
		this->key = key;
		this->amount = amount;
	}

	bool operator > (const Element& b) {
		return (amount > b.amount);
	}

	bool operator < (const Element& b) {
		return (amount < b.amount);
	}
};

List<Element*> symbols;
Map<char, string> codes;
Map<string, char> decodes;

void makeHufTree(string input) {
	
	Map<char, int> ar;
	for (int i = 0; i < input.size(); i++) { // counting the number of occurrences of symbols
		if (ar.exist(input[i])) ar[input[i]]++;
		else ar.insert(input[i], 1);
	}

	while (ar.getSize()) { // put them in a sorted form of the Element type in the list
		Element* temp = new Element;
		temp->key = ar.getHeadKey();
		temp->amount = ar.getHeadValue();
		ar.remove(ar.getHeadKey());
		symbols.sortedInsert(temp);
	}
	while (symbols.getSize() != 1) { // building the Huffman tree
		Element* first = symbols[0];
		Element* second = symbols[1];
		symbols.pop_front();
		symbols.pop_front();
		Element* newElement = new Element;
		newElement->amount = first->amount + second->amount;
		newElement->left = first;
		newElement->right = second;
		symbols.sortedInsert(newElement);
	}
}

void makeCodeTable(string code, Element* current) {
	if (current->left) makeCodeTable(code + '0', current->left); // If we go to the left, then we add 0 elements to the code

	if (current->right) makeCodeTable(code + '1', current->right); // If we go to the right, then we add 1 to the code of elements

	if (!current->left && !current->right) {
		codes.insert(current->key, code);
		decodes.insert(code, current->key);
	}
}

string code(string input) {
	string coded_input = "";
	for (int i = 0; i < input.size(); i++) coded_input += codes[input[i]];
	return coded_input;
}

string decode(string input) { 
	string decode_input = "";
	string buff = "";
	for (int i = 0; i < input.size(); i++) {
		buff += input[i];
		if (decodes.exist(buff)) {
			decode_input += decodes[buff];
			buff = "";
		}
	}
	return decode_input;
}

void answer(string coded, string decoded) {
	cout << "codes table\n";
	codes.print();
	cout << "decodes table\n";
	decodes.print();

	cout << '\n' << coded << '\n' << decoded << '\n';
	cout << " Coded Memory Size : " << coded.size() << '\n';
	cout << " Decoded Memory Size : " << decoded.size() * 8 << '\n';
	double ratio = decoded.size() * static_cast<double>(8) / coded.size();
	cout << " Copression ratio : " << ratio << '\n';
}

int main() {

	string input = "qwertywwwrrtttttt";
	string coded = "", decoded = "";
	cin >> input;

	makeHufTree(input);
	makeCodeTable("", symbols[0]);

	coded = code(input);
	decoded = decode(coded);

	answer(coded, decoded);

	while (symbols.getSize()) {
		Element* temp = symbols[0];
		symbols.pop_front();
		if (temp->right)symbols.push_front(temp->right);
		if (temp->left)symbols.push_front(temp->left);
		delete temp;
	}
}