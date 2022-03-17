#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
//----------------------------extracting file-----------------------------------------
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
//              cout << A << endl << A.size() << " : " << 8*(A.size()) << endl;
        }
cout << 8*(A.size()) << endl;
//------------------------------string to 0 1 form----------------------------
	string cod;
	int i = 0;
	while( i < A.size())
	{
		for(int j = 7; j >= 0; j--)
		{
			if(i < A.size())
			{
				int z = ((A[i] & (1 << j)) != 0);
				if(z == 0) cod += '0';
				else cod += '1';
			}
			else break;
		}
		i++;
	}
	cout << cod.size() << endl << i*8 << endl;	
//--------------------------------decode map-----------------------------------
        unordered_map<string, char>* decode_chart = new unordered_map<string, char>;
	fstream decode_file;
	
	decode_file.open("decode.txt", ios::in);
	if(decode_file.is_open())
	{
		string line;
		while(getline(decode_file, line))
		{
			pair<string, char> p;
			for(int i = 0; i < line.size(); i++)
			{
				if(line[i] == '0' || line[i] == '1')
				{
					p.first += line[i];
				}
				else
				{
					p.second = line[i];
					/*if(line[i] != ' ')
					{
						p.second = line[i];
					}*/
					
				}
			}
			decode_chart->insert(p);
		}
		decode_file.close();
	}

//	unordered_map<string, char> :: iterator it1 = decode_chart->begin();
//      for(it1 ; it1 != decode_chart->end(); it1++)    cout << it1->first << " " << it1->second << endl;

//-------------------------------decoding file---------------------------------	
	string ans;
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
//        cout << ans << endl;
        file.open("file handeling.txt", ios::trunc | ios::out);
        if(file.is_open())
        {
                file << ans;
                file.close();
        }
	return 0;
}
