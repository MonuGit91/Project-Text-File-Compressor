#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <limits>
#include <fstream>
using namespace std;


class Node
{
public:
	int value;
	char charector;
	Node* left;
	Node* right;

	Node(pair<char, int> pair)
	{
		value = pair.second;
		charector = pair.first;
		left = NULL;
		right = NULL;
	}
	Node()
	{
		value = INT_MAX;
		charector = '\0';
		left = NULL;
		right = NULL;
	}
	
};

class Priority_queue
{
private:
	vector<Node*> v;
public:
	Priority_queue(){
	
	}	

	void push(Node* obj)
	{
		v.push_back(obj);
		int ci = v.size()-1;
		int pi = (ci-1)/2;
		
		while(ci > 0)
		{
			if((v.at(ci))->value < (v.at(pi))->value)
			{
				Node* temp = v.at(ci);
				v.at(ci) = v.at(pi);
				v.at(pi) = temp;
				ci = pi;
				pi = (ci-1)/2;
			}
			else break;
		}
	}
	void pop()
	{
		v.at(0) = v.at(v.size()-1);
		v.pop_back();

		int pi = 0;
		int lci = 1;
		int rci = 2;
		int sci;

		while(lci < v.size())
		{
			sci = pi;
			if((v.at(lci))->value < (v.at(sci))->value) sci = lci;
			if(rci < v.size() && ((v.at(rci)->value) < (v.at(sci))->value )) sci = rci;
			
			if(sci == pi) return;

			Node* temp = v.at(sci);
			v.at(sci) = v.at(pi);
			v.at(pi) = temp;

			pi = sci;
			lci = 2*pi + 1;
			rci = 2*pi + 2;
		}
	}

	Node* top()
	{
		if(v.size() < 1)
		{
			return NULL;
		}		
		return v.at(0);
	}

	int size()
	{
		return v.size();
	}

	bool isEnpty()
	{
		return v.size() == 0;
	} 
};

void print(Node* root)
{
	if(root == NULL) return;

	 cout << root->charector << " " << root->value << endl;

	print(root->left);
	print(root->right);
	return;
}


void makeChart(Node* root, unordered_map<char, string>* code_chart, unordered_map<string, char>* decode_chart,  string code)
{
	if(root->left == NULL && root->right == NULL)
	{
		pair<char, string> pair0(root->charector, code);
		code_chart->insert(pair0);

		pair<string, char> pair1(code, root->charector);
		decode_chart->insert(pair1);
		return;
	}
	
	makeChart(root->left, code_chart, decode_chart, code + '0');
	makeChart(root->right, code_chart, decode_chart, code + '1');
	return;
}

int main()
{

//-----------------------------------extracting file-------------------------------------

	fstream file;
	string A;
	file.open("file handeling.txt", ios::in);
	if(file.is_open())
	{
		string line;
		while(getline(file, line))
		{
			A += line;
		}
		file.close();
//		cout << A << endl << A.size() << " : " << 8*(A.size()) << endl;
	}


//-----------------------------------counting charector(map)------------------------------

	unordered_map<char, int> map;
	for(int i = 0; i < A.size(); i++)
	{
		if(map.count(A[i])) map.at(A[i])++;
		else
		{

			pair<char, int> p(A[i], 1);
			map.insert(p);
		}
	}


//---------------------------------creating min_heap--------------------------------

	Priority_queue  min_heap;
	for(auto pair : map)
	{
		Node* obj = new Node(pair);
		min_heap.push(obj);
		
	}


//------------------------------making tree(min_heap)----------------------------------

	while(min_heap.size() > 1)
	{
		Node* obj1 = min_heap.top();
		min_heap.pop();

		Node* obj2 = min_heap.top();
		min_heap.pop();

		Node* ans = new Node;;
		ans->value = obj1->value + obj2->value;
		ans->charector = '+';
		ans->left = obj1;
		ans->right =  obj2;

		min_heap.push(ans);
	}

	Node* root = min_heap.top();
//	print(root);


//------------------------------------making map / decoding map-------------------------------------

	unordered_map<char, string>* code_chart = new unordered_map<char, string>;
	unordered_map<string, char>* decode_chart = new unordered_map<string, char>;
	string code;

	makeChart(root, code_chart, decode_chart, code);
	
	fstream decode_file;
	decode_file.open("decode.txt", ios::trunc | ios::out);
	if(decode_file.is_open())
	{
		for(auto it : *code_chart)
		{
			string line;
			line += it.second;
			line += " ";
			line += it.first;
			decode_file << line << endl;
		}
		decode_file.close();
	}	

/*
//------------------------------------printing code_chart-----------------------------------
	
	unordered_map<char, string> :: iterator it = code_chart->begin();
	for(it ; it != code_chart->end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}

cout << endl;


//------------------------------------printing decode_chart-----------------------------------

	unordered_map<string, char> :: iterator it1 = decode_chart->begin();
	for(it1 ; it1 != decode_chart->end(); it1++)	cout << it1->first << " " << it1->second << endl;

*/
//------------------------------------converting file in 0 1 form----------------------------

	string cod;
	for(int i = 0; i < A.size(); i++)
	{
		cod += code_chart->at(A[i]);		
	}	
//	cout << endl << cod << endl << cod.size() << endl;;
//cout << cod.size() << endl;
        int i = 0;
        string bit_str;

        while(i < cod.size())
        {
                char ch = 'a';
                ch = (ch & (~ch));
                for(int pos = 7; pos >= 0; pos--)
                {
                        if(i < cod.size())
                        {
                                int bit;
                                cod[i] == '1' ? bit = 1 : bit = 0;
                                ch = (ch | (bit << pos));
                                i++;
                        }
                        else    break;
                }

                 bit_str += ch;
        }
cout << 8*(bit_str.size()) << endl;
	file.open("file handeling.txt", ios::trunc | ios::out);
	if(file.is_open())
	{
		file << bit_str;
		file.close();
	}
	

//-------------------------------------------DECODING--------------------------------------------
/*	string ans;
	string* sub_str = new string;
	for(int i = 0; i < cod.size(); i++) 
	{
		if(decode_chart->count(*sub_str))
		{	
			ans += decode_chart->at(*sub_str);
			free(sub_str);
			sub_str = new string;
		}
		sub_str->push_back(cod.at(i));
	}
//	cout << ans << endl;
	file.open("file handeling.txt", ios::trunc | ios::out);
        if(file.is_open())
        {
                file << ans;
                file.close();
        }*/
	return 0;
}
