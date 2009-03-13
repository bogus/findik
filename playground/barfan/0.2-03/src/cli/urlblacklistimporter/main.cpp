#include "importer_tool.hpp"





int main(int argc, char* argv[])
{
	std::string cmd("./");
        std::string temp("");
        if(argc > 1)
        {
                cmd = argv[1];
        }
	findik::importer::tool::import i(cmd);
}
