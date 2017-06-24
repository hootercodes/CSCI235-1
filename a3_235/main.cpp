#include "dict.h"

//allows for as many calls to 'suggest' as user would like until program is terminated
int main(int argc, char **argv){
    
    int i;
  
    std::ifstream stream;
    stream.open(argv[1]);
  
    Dict d(stream);

    std::string input;
    std::string str;
    
    std::cout << "Welcome to your Dictionary!" << std::endl;
  
    do {
        std::cout << "Please enter a prefix, followed by the number of possible words you would like." << std::endl;
        std::cout << "If you would like to EXIT, please type \"EXIT\"" << std::endl;
        getline(std::cin, input);
        str = input;
    
        int j = 0;
        char c;
        while (str[j]) {
            c=str[j];
            str[j] = tolower(c);
            j++;
        }           
        if (str == "exit") {
            std::cout << "Goodbye!" << std::endl;
        }
        else {
            int index = str.find(' ');
            std::string word = str.substr(0, index);
            std::string num = str.substr(index);
            int i = stoi(num);
            d.suggest(word, i);
        }    
    }
    while (str != "exit");
    return 0;
};