#include <gtest/gtest.h>
#include <functions/functions.h>

using namespace std;

TEST(test_Hash, test) {
	HashTable<char, int> table_0;
	HashTable<char, int> table_1(8);
	HashTable<char, int> table_2(table_1);
	HashTable<char, int> table_3 = table_2;
	table_0.print();
	cout << "is insert -> " << boolalpha << table_0.insert('Q', 1000) << endl;
	cout << "Q count in table -> " << table_0.count('Q') << endl;
	cout << "contains 1000 -> " << boolalpha << table_0.contains(1000) << endl;
	cout << "contains Q -> " << boolalpha << *table_0.search('Q') << endl;
	cout << "delete Q -> " << boolalpha << table_0.erase('Q') << endl;
	cout << "count elements -> " << table_0.count() << endl;
	cout << "size -> " << table_0.size() << endl;
	fill_rome(table_0, 10);
	table_0.print();
}

TEST(test_Rome, test) {
	HashTable<char, int> table(8);
	fill_for_Rome_numbers(table);
	string rome_num = "MCMXCIV";
	table.print();
	cout << rome_num << " --> " << get_arabic_number(rome_num, table) << endl;
}