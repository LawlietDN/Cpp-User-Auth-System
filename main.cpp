#include <iostream>
#include <fstream>
#include "needles.h"
#include <regex>
#include <limits>
#include <nlohmann-json.hpp>

int main() 
{ 
    bool isAllowed = true;
    std::string userName;
    std::string userFullName;
    std::string userEmail;
    
    
    switch(displayOptions())
    {
        case 1: return 1;
                
        case 2:
        uniqueIDGenerator();
        getName(userFullName, isAllowed);
        getUserName(userName, isAllowed);
        getUserEmail(userEmail, isAllowed);
        break;
        
    }
    
    
    
    return 0;
}

int uniqueIDGenerator()
{
    std::string key = "ID";
    int ID = 0;
    if(!isAvailable(ID, key))
    {
       ID++;
       storeData(key, ID);
       return 0;
    }
       storeData(key, ID);
       return 0;
    

}

bool lengthChecker(std::string const& userInput) 
{
    if(userInput.length() < 3 || userInput.length() > 30)
    {
    std::cout << "This field can't be less than 3 character and can't exceed 30 characters long!\n";
    return true;
    }
    return false;
}

bool checkRetryLimit(int maxTriesChecker, bool& isAllowed)
{
    if(maxTriesChecker == 5) 
    {
        isAllowed = false;
        std::cout << "Invalid inputs!\nTry again later.";
        return true;
    } 
        return false;
}

bool blankChecker(std::string& userInput) 
{
        if(userInput.empty()) 
        {
        std::cout << "Field required!\nField cannot be blank!\n"; 
        return true;
        }
            return false;
}

int getName(std::string& userInput, bool& isAllowed)
{
    if(isAllowed)
    {
    int maxTries = -1;
    do
    {
    maxTries++;
    if(checkRetryLimit(maxTries, isAllowed)) return 1;
    std::cout << "Full name: ";
    std::getline(std::cin, userInput);
   
    }while(blankChecker(userInput) || lengthChecker(userInput) || !isAvailable(userInput, "Name"));
    }
    storeData("Name", userInput);
    return 0;
}

int getUserName(std::string& userInput, bool& isAllowed)
{
    if(isAllowed)
    {
    int maxTries = -1;
    do
    {
    maxTries++;
    std::cout << "Choose a username for display:  ";
    std::getline(std::cin, userInput);
    if(checkRetryLimit(maxTries, isAllowed)) return 1;
    }while(blankChecker(userInput));
    
}
    storeData("Username",userInput);
    return 0;
}

int getUserEmail(std::string& email, bool& isAllowed)
{
    if(isAllowed)
    {
    int maxTries = -1;
    do
    {
    maxTries++;
    std::cout << "Email: ";
    std::getline(std::cin, email);
    if(checkRetryLimit(maxTries, isAllowed)) return 1;
    }while(blankChecker(email) || !isValidEmail(email));
  }
    storeData("Email",email);
    return 0;
  }
int displayOptions() 
{
    int t = 0;
    while(true) {
        std::cout << "1. Log in\n2. Sign up\n>>> ";
        if (!(std::cin >> t)) 
        {
            std::cout << "Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } 
        else if (t == 1 || t == 2) 
        {
            std::cin.ignore();
            return t;
        } 
        else {
            std::cout << "Invalid option. Please choose 1 or 2.\n";
        }
    }
}


void greetUser() 
{
    std::cout << "Welcome! You finshed the signing up process!";
}


bool isValidEmail(std::string const& email) 
{
    const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
     if(std::regex_match(email, pattern)) return true;
     
     std::cout << "Invalid Email foramat.\n";
     return false;
}
template<typename T>
bool isAvailable(T& searchTerm, std::string const& key)
{
    nlohmann::json jsonFile;    
    std::ifstream file("userData.json");

    if (!file) {
        std::cerr << "Unable to open file.\n";
        return true; 
    }

    if (file.peek() == std::ifstream::traits_type::eof()) {
        return true; 
    }

    try
    {
        file >> jsonFile;
    }
    catch(nlohmann::json::parse_error& err)
    {
        std::cerr << "An error occured while parsing the JSON file: " << err.what() << '\n';
        return false;
    }

    if constexpr(std::is_same<T, int>::value)
    {

      if(key == "ID")
    {
        int lastID = 0;

        for(auto const& item: jsonFile)
        {
            if(item.contains("ID"))
            {
                int currentID = item["ID"];
                lastID = currentID;
            }
        }
        if(lastID == searchTerm)
        {
            return false;
        }
        return true;
        
      }
    }

     if constexpr(std::is_same<T, std::string>::value)
     {

    if(key == "Name")
    {
        for(auto const& item : jsonFile)
    {
        if(item.contains("Name") && item["Name"] == searchTerm) 
        {
            std::cout << "Name is already taken.\nChoose another name\n"; 
            return false;
            }         
        }
       }
     }
     return true;

}


template<typename T>
int storeData(std::string const& key, T const& value)
{
     std::string fileName = "userData.json";
     nlohmann::json jsonFile;
     std::ifstream file(fileName,  std::ios::in);

     if(!file) 
     {
        std::cerr << "Unable to open file\n"; return 1;
        }
    if(file.peek() == std::ifstream::traits_type::eof())
        {
             jsonFile = nlohmann::json::object();
        }
        else
        {
            try
            {
                file >> jsonFile;
            } catch (nlohmann::json::parse_error const& err) {
                std::cerr << "JSON parsing error: " << err.what() << '\n';
                return 1; 
            }
        }
     file.close();
     jsonFile[key] = value;          // Update JSON with new key-value pair


     std::ofstream ofile(fileName,std::ios::app);
     if(!ofile)
     {
        std::cerr << "Unable to open file.";
        return 1;
     }

     ofile << jsonFile.dump(4);
     ofile.close();
     return 0;
}