#include <map>
#include <string>
#include <iostream>

using namespace std;

map<string, string> query_parser(const string &query)
{
	string str = query;
    map<string, string> result;
    int cutAt;
    string delim = "&";
    while( (cutAt = str.find_first_of(delim)) != str.npos )
    {
        if(cutAt > 0)
        {
       		string entry = str.substr(0, cutAt);

       		int c;
       		if( (c = entry.find_first_of("=")) != entry.npos )
       		{
    	   		string key   = entry.substr(0, c);
       			string value = entry.substr(c + 1);
	       		result.insert( map<string, string>::value_type( key, value ) );
       		}
        }
        str = str.substr(cutAt + 1);
    }
    if(str.length() > 0)
    {
    	//std::cout << str << std::endl;
    	int c;
    	if( (c = str.find_first_of("=")) != str.npos )
       	{
       		string key   = str.substr(0, c);
       		string value = str.substr(c + 1);
	    	result.insert( map<string, string>::value_type( key, value ) );
       	}
    }
	return result;	
}


/*
// test code
int main(void)
{
	std::string query = "test1=12345&test2=56789";
	//std::string query = "";

	std::map<std::string, std::string> values = query_parser(query);

	std::cout << "test1: " << values["test1"] << std::endl;
	std::cout << "test2: " << values["test2"] << std::endl;

}
*/
