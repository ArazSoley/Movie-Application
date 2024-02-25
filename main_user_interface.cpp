#ifndef MAIN_USER_INTERFACE_H
#define MAIN_USER_INTERFACE_H
#include "user_interface.h"
#include "movie.h"
#include "user.h"
#include<vector>

int main() {

	// You can test your implementations here
	UserInterface fake;
	vector<string *> res;

	Trie<string> tr;
	tr.insert("user1");
	tr.insert("abcdef123");
	tr.insert("12345ac");
	tr.insert("1345ac");

	tr.wildcardSearch("*1*", res);

	for (size_t i = 0, size = res.size(); i < size; i++)
	{
		cout << *res[i] << endl;
	}
}
#endif //MAIN_USER_INTERFACE_H