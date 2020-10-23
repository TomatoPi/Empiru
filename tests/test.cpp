#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <map>
#include <set>

using namespace std;

int main() {
	cout << sizeof(map<int,int>) << endl;
	cout << sizeof(set<int>) << endl;
	cout << sizeof(vector<int>) << endl;
	cout << sizeof(vector<vector<int>>) << endl;
	cout << sizeof(unordered_map<int,int>) << endl;
	cout << sizeof(unordered_map<long int, vector<int>>) << endl;
	cout << sizeof(unordered_set<int>) << endl;
	return 0;
}
