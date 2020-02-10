#include<map>
#include<vector>
#include<iostream>
template <typename T>
class complex_trie{
public:
complex_trie(const std::vector<std::vector<T>>& paterns){
	check_node = root = new node;
	//vector of pairs for creating trie like bfs search
	std::vector<std::pair<bool, node*>> trie_ends;
	unsigned fin_pat = 0; // number of finished  paterns 
	
	//create first level of trie
	for(unsigned i = 0; i < paterns.size(); ++i){
		if(root->edges.find(paterns[i][0]) == root->edges.end())
			root->edges[paterns[i][0]] = new node;
		root->edges[paterns[i][0]]->unluck_edge = root;
		if(paterns[i].size() > 1)
			trie_ends.push_back(std::pair<bool, node*>{true, root->edges[paterns[i][0]]});
		else{
			trie_ends.push_back(std::pair<bool, node*>{false, root->edges[paterns[i][0]]});
			fin_pat+=1;
			//root->edges[paterns[i][0]]->patern_num = i+1;
			root->edges[paterns[i][0]]->patern_num.push_back(i+1);
		}
	}
	
	for(unsigned j =1; fin_pat < paterns.size() ; ++j){ // cicle for getting every symbol of alphabet
		for(unsigned i =0; i < trie_ends.size(); ++i){ // cicle for every patern 
			if(!trie_ends[i].first) //already builded for this patern?
				continue;
			//didn't create this edge?
			if(trie_ends[i].second->edges.find(paterns[i][j]) == trie_ends[i].second->edges.end()){ 
				//create new edge
				trie_ends[i].second->edges[paterns[i][j]] = new node;
				node* nod=trie_ends[i].second->unluck_edge;
				while( (nod->edges.find(paterns[i][j]) == nod->edges.end()) && (nod != root) ) //go to the node, that have edge pointed by needed symbol, or root
					nod = nod->unluck_edge;
				if(nod->edges.find(paterns[i][j]) != nod->edges.end()){
					trie_ends[i].second->edges[paterns[i][j]]->unluck_edge = nod->edges[paterns[i][j]];
					trie_ends[i].second->edges[paterns[i][j]] -> output_edge = nod->edges[paterns[i][j]]->output_edge;//????????????
					if(nod->edges[paterns[i][j]]->patern_num.size() > 0){
						trie_ends[i].second->edges[paterns[i][j]]->output_edge = nod->edges[paterns[i][j]];
					}
				}else{
					trie_ends[i].second->edges[paterns[i][j]]->unluck_edge = root;
				}
			}
			if(paterns[i].size()==j+1){
				fin_pat+=1;
				trie_ends[i].first = false;
				//trie_ends[i].second->edges[paterns[i][j]]->patern_num = i+1;
				trie_ends[i].second->edges[paterns[i][j]]->patern_num.push_back(i+1);
			}else{
				trie_ends[i].second = trie_ends[i].second->edges[paterns[i][j]];
			}
		}
	}

}

~complex_trie(){
	delete root;
}


bool compare(const T& cmp, std::vector<unsigned>& ans ){
	ans.clear();
	while( (check_node->edges.find(cmp) == check_node->edges.end()) && ( check_node != root) )
		check_node = check_node->unluck_edge;
	if(check_node->edges.find(cmp) == check_node->edges.end())
		return false;
	check_node = check_node->edges[cmp];
	if(check_node->patern_num.size() > 0)
		//ans.push_back(check_node->patern_num);
		ans.insert(ans.end(), check_node->patern_num.begin(), check_node->patern_num.end());
	node *output = check_node->output_edge;
	while(output != nullptr){
		//ans.push_back(output->patern_num);
		ans.insert(ans.end(), output->patern_num.begin(), output->patern_num.end());
		output = output->output_edge;
	}
	return true;
}

void check(){
	root->check(0);
}

private:
class node{
public:
//unsigned patern_num = 0;
std::vector<unsigned> patern_num;
node *unluck_edge = nullptr;
node *output_edge = nullptr;
std::map<T, node*> edges;

~node(){
	for(std::pair<T, node*> edge : edges){
		delete edge.second;
	}
}
void check(unsigned i){
	std::cout<<i<<". ";
	for(unsigned j : patern_num)
		std::cout<<j<<' ';
	std::cout<<this<<' '<<unluck_edge<<' '<<output_edge<<' ';
	for(std::pair<T, node*> edge : edges)
		std::cout<<edge.first<<' ';
	std::cout<<std::endl;
	for(std::pair<T, node*> edge : edges)
		edge.second->check(i+1);
}

};
node *check_node = nullptr;
node *root = nullptr;
};
