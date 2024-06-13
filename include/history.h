#include<bits/stdc++.h>
extern std::vector<std::string> History;
void printHistory(){
	for(string s : History){
		std::cout << s << std::endl;
	}
}
void clearHistory(){
	History.clear();
}