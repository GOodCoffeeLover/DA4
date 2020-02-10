#include"ACSubStringSearch.h"
#include<string>
#include<iostream>

void parse(const std::string& str, std::vector<std::string>& vec){
	vec.clear();
	if(str.size() == 0)
		return;
	vec.push_back(std::string{});
	int space = 0;
	//int len=0;
	for(unsigned i=0; i<str.size(); ++i){
		if(str[i] == ' '){
			space = 1;
			//len = 0;
			continue;
		}
		if(space == 1){
			space = 0;
			vec.push_back(std::string{});
		}
		//len+=1;
		if((str[i] >= 'A') && (str[i] <= 'Z'))
			*(--vec.end()) += str[i] - 'A' + 'a';
		else
			*(--vec.end()) += str[i];
		/*if(len == 16 ){
			vec.push_back(std::string{});
			len =0;
		}*/
	}
}

int main(){
	std::ios::sync_with_stdio(false);
	std::vector<std::vector<std::string>> paterns;
	std::string str;
	while(true){
		std::getline(std::cin, str);
		if(str.size() == 0)
			break;
		paterns.push_back(std::vector<std::string>{});
		parse(str, *(--paterns.end()));
	}
	/*for(std::vector<std::string> v : vec )
		for(std::string s : v){
			std::cout<<s<<std::endl;
		}*/
	complex_trie<std::string> trie(paterns); trie.check();
	std::vector<unsigned> str_sizes;
	std::vector<std::string> words;
	std::vector<unsigned> ans;
	while(true){
		std::getline(std::cin, str);
		parse(str, words);
		str_sizes.push_back(words.size());
		if(*(--str_sizes.end()) == 0)
			break;
		for(unsigned i = 0; i < words.size(); ++i){
			if(trie.compare(words[i], ans)){
				for(unsigned j = 0; j <ans.size(); ++j){ 
					//номер строки, номер слова в строке, номер патерна
					unsigned back = 1, size = i+1;
					//std::cout<<"size = "<<size<<" ans[i] -1 = "<<(ans[j]-1)<<" paterns[ans[i]-1].size() = "<<paterns[ans[j]-1].size()<<std::endl;
					while(size < paterns[ans[j]-1].size()){
						size += *(str_sizes.end() - ++back);
					}
					std::cout<< (str_sizes.size() -back +1) <<", "<< (size - paterns[ans[j]-1].size() +1) <<", "<< ans[j]<<std::endl;
				}
			}
		}
	}
	return 0;
}
