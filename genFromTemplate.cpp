#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>

#define TEMPLATE "tool/template_spider.py"
#define GENERATE "firstSpider.py"

/*
 * templatefileのプレースホルダを任意の文字列に置き換えて
 * generatefileに出力する.
 * substituteの要素は<プレースホルダ, 置き換える文字列>
 */
void genFromTemplate(std::string templatefile, std::string generatefile, 
                     std::map<std::string, std::string> substitute) {
        try {
                std::ifstream templfile(templatefile);
                if (templfile.fail()) {
                        throw std::runtime_error("fileopen failed.");
                }

                std::ofstream genfile(generatefile);

                std::string line;
                while (getline(templfile, line)) {
                        for (auto elm : substitute) {
                                std::string::size_type pos = line.find(elm.first);
                                while (pos != std::string::npos) {
                                        line.replace(pos, elm.first.length(), elm.second);
                                        pos = line.find(elm.first, pos + elm.second.length());
                                }
                        }
                        genfile << line << std::endl;
                }
        } 
        catch(std::runtime_error e) {
                std::cerr << e.what() << std::endl;
                std::exit(1);
        }
}

int main(int argc, char *argv[])
{
        std::map<std::string, std::string> substitute;
        std::string target;

        for (int i = 1; i < argc; i++) {
                target += argv[i];
                if (i != argc - 1) target += '+';
        }

        substitute["$target"] = target;

        genFromTemplate(TEMPLATE, GENERATE, substitute);
}




