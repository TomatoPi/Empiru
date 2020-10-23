#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <unordered_map>
#include <list>
#include "../src/utils/pattern/SuperObserver.h"

using namespace std;

using E1 = char;
using E2 = float;

struct C {
	void pouet(E1 e) { cout << "C Pouet 1 : " << e << endl; }
	void foobo(E2 e) { cout << "C Foobo 2 : " << e << endl; }
};

struct D {
	void pouet(E1 e) { cout << "D Pouet 1 : " << e << endl; } 
	void pouat(E2 e) { cout << "D Pouet 2 : " << e << endl; }
};

template <typename T, typename ...U>
struct B : public B<T>, public B<U...> {
};

using Func = std::function<int(void)>;

template <typename T>
struct B<T> {
	using Callback = std::function<void(const T&)>;
	std::vector<Callback> _obs;

	template <typename ...U>
	void coucou(U&& ...u) {
		T t(std::forward<U>(u)...);  
		for (auto& callback : _obs) {
			callback(t);
		}
	}

	void add(Callback&& c) {
		_obs.emplace_back(c);
	}
};

int main() {
	using namespace std::placeholders;
	using namespace SuperObserver;
	auto s = Subject<int,E1,E2>();
	auto b = B<E1,E2>();
	C c;
	D d;
	cout << "===" << endl;
	b.B<E1>::coucou('a');
	b.B<E2>::coucou(6);
	cout << "===" << endl;
	b.B<E1>::add(std::bind(&C::pouet, &c, _1));
	b.B<E2>::add(std::bind(&C::foobo, &c, _1));
	b.B<E1>::add(std::bind(&D::pouet, &d, _1));
	b.B<E2>::add(std::bind(&D::pouat, &d, _1));
	cout << "===" << endl;
	b.B<E1>::coucou('a');
	cout << "===" << endl;
	b.B<E2>::coucou(6);
	cout << "===" << endl;
	cout << sizeof(b) << endl;
	cout << sizeof(char) << endl;
	cout << sizeof(map<int,int>) << endl;
	cout << sizeof(unordered_map<int,int>) << endl;
	cout << sizeof(vector<int>) << endl;
	cout << sizeof(list<int>) << endl;
}
