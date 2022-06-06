#include "cmdmanager.h"

int main(int argc, char* argv[]){
	CmdManager manager(argc, argv);
	bool res = manager.parse_command();
	if(!res) {
		return -1;
	}
	return 0;
}
