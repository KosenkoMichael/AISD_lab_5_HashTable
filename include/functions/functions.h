#pragma once
#include<vector>
#include<exception>
#include<iostream>
#include<string>
#include <cstdlib>
#include <ctime>
#include<iomanip>

using namespace std;

char get_rome_sequence() {
	string mass = "IVXLCDM";
	int randomIndex = rand() % mass.size();
	char result = mass[randomIndex];
	return result;
}

template <typename K, typename V>
class HashTable {
private:
	const int _min_size = 10;
	enum State { empty = 0, filled = 1, deleted = 2 };
	template <typename K, typename V>
	struct Elem {
		K key;
		V value;
		State status;
		Elem() : key(NAN), value(NAN), status(empty) {};
		void print() const {
			if (status == filled)
				cout << "Key: " << key << " Value: " << value << endl;
		}
		void null() {
			key = NAN;
			value = NAN;
			status = deleted;
		}
	};
	vector<Elem<K, V>> _data;
	size_t _count;
	void check() {
		if (_count / _data.size() >= 0.5) {
			cout << "Size changed to " << _data.size() * 2 + 1 << endl;
			vector<Elem<K, V>> old_data = _data;
			vector<Elem<K, V>> new_data;
			new_data.resize(_data.size() * 2 + 1);
			_data = new_data;
			for (auto& i : old_data) {
				insert(i.key, i.value);
			}
		}
	}
	size_t h(K key) const {
		if (_data.size() > 0) {
			char hash = key;
			hash = (hash ^ 61) ^ (hash >> 16);
			hash *= 9;
			hash ^= hash >> 4;
			hash *= 0x27d4eb2d;
			hash ^= hash >> 15;
			return hash % _data.size();
		}
		else
			throw ("Hash table is zero size");
	}
public:
	HashTable() {
		_data.resize(_min_size);
		_count = 0;
	}
	HashTable(size_t size) {
		_data.resize(size);
		_count = 0;
	}
	HashTable(const HashTable<K, V>& other) {
		_data = other._data;
		_count = other._count;
	}
	~HashTable() = default;
	HashTable<K, V>& operator=(const HashTable<K, V>& other) {
		if (this == &other) {
			return *this;
		}
		_data = other._data;
		_count = other._count;
	}
	void print() const {
		for (auto& i : _data) {
			i.print();
		}
	}
	bool insert(K key, V value) {
		if (search(key) != nullptr)
			return false;
		size_t index = h(key);
		if (_data[index].status != filled) {
			_data[index].key = key;
			_data[index].value = value;
			_data[index].status = filled;
			_count++;
			check();
			return true;
		}
		else {
			int i = 1;
			while (true) {
				index = (index + i) % _data.size();
				if (index == h(key))
					return false;
				if (_data[index].status != filled) {
					_data[index].key = key;
					_data[index].value = value;
					_data[index].status = filled;
					_count++;
					check();
					break;
				}
				i++;
			}
			return true;
		}
	}
	bool insert_or_assign(K key, V value) {
		if (search(key) != nullptr)
			return false;
		size_t index = h(key);
		_data[index].key = key;
		_data[index].value = value;
		if (_data[index].status != filled) {
			_data[index].status = filled;
			_count++;
			check();
		}
		return true;
	}
	bool contains(V value) const {
		for (auto& i : _data) {
			if (i.value == value)
				return true;
		}
		return false;
	}
	V* search(K key) {
		size_t index = h(key);
		if (_data[index].key == key)
			return &_data[index].value;
		else {
			int i = 1;
			while (true) {
				index = (index + i) % _data.size();
				if (index == h(key))
					return nullptr;
				if (_data[index].key == key)
					return &_data[index].value;
				i++;
			}
		}
	}
	bool erase(K key) {
		size_t index = h(key);
		if (_data[index].key == key) {
			_data[index].null();
			_count--;
			return true;
		}
		else {
			int i = 1;
			while (true) {
				index = (index + i) % _data.size();
				if (index = h(key))
					return false;
				if (_data[index].key == key) {
					_data[index].null();
					_count--;
					return true;
				}
				i++;
			}
		}
	}
	size_t count(K key) {
		size_t count = 0;
		for (auto& i : _data) {
			if (h(i.key) == h(key)) {
				count++;
			}
		}
		return count;
	}
	size_t count() const {
		return _count;
	}
	size_t size() const {
		return _data.size();
	}
};
void fill_for_Rome_numbers(HashTable<char, int>& table) {
	table.insert('I', 1);
	table.insert('V', 5);
	table.insert('X', 10);
	table.insert('L', 50);
	table.insert('C', 100);
	table.insert('D', 500);
	table.insert('M', 1000);
}
int get_arabic_number(string rome_num,HashTable<char, int>& table) {
	int result = 0;
	int prevValue = 0;
	for (int i = rome_num.length() - 1; i >= 0; i--) {
		int value = *table.search(rome_num[i]);
		if (value < prevValue)
			result -= value;
		else
			result += value;
		prevValue = value;
	}
	return result;
}
void fill_rome(HashTable<char, int>& table, size_t size) {
	for (int i = 0; i <= size; i++) {
		table.insert(get_rome_sequence(), i);
	}
}
