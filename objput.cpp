#include <iostream>
#include <string>
#include <fstream>
#include "tools.h"

using namespace std;

int main(int argc, char * argv[]){

	if (argc < 2) {
		cerr << "Usage:" 
			<< argv[0] 
			<<  " <objectname>\n" 
			<< endl;
	}
	string object_name = argv[1];

	//Usernames, group names, and object names can contain letters, digits, and
	//underscores; no other characters are legal.

	if (sanitize(object_name, 1) < 1){
		cerr << "Sorry invalid input, please try again!\n" << endl;
		exit(1);
	}

	// Set the egid to flat_fs's gid
	if(raise_privilege() < 0 ){
		cerr << "Sorry there was an error accessing the repository" << endl;
		exit(1);
	}

	string user_name = get_real_username();
	string group_name = get_real_groupname();

	string file_name = user_name + "-" + object_name;

	string path = "flat_fs_repo/" + file_name;

	ofstream file_to_write; 

	file_to_write.open(path);

	if (file_to_write.is_open()){

		string line;

		string default_acl = user_name + ".* rwxpv\n%\n";

		file_to_write << default_acl << endl;

		while(getline(cin, line))
			file_to_write << line <<endl;

		file_to_write.close();

		change_permissions(path);
		// chmod the path 

	}
	drop_privilege();

}





