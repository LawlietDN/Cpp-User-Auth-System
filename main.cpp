#include <iostream>
#include <fstream>
#include "needles.h"
#include <regex>
#include <limits>
#include <nlohmann-json.hpp>
#include <filesystem>


int main() 
{ 
    bool isAllowed = true;
    int ID = 0;
    std::string userName;
    std::string userFullName;
    std::string userEmail;
    std::string password;
    size_t userHashedPassword = 0;
    LoginManager logInManager(" ", " ");
    switch(displayOptions())
    {
        case 1:
        promptCredentials(userFullName,password);
        logInManager = LoginManager(userFullName, password);
        if(logInManager.authentication())
        {
            logInMessage();
        }
        else
        {
            std::cout << "Invalid credentials.\n";
        }
        break;

        case 2:
        uniqueIDGenerator(ID);
        getName(userFullName, isAllowed);
        getUserName(userName, isAllowed);
        getUserEmail(userEmail, isAllowed);
        hashPassword(userHashedPassword,isAllowed);

        if(isAllowed)
        {
            nlohmann::json userData = {
                {"ID", ID},
                {"Username", userName},
                {"Email", userEmail},
                {"Hashed Password", userHashedPassword}
            };
            storeData(userFullName,userData);

        }
        
        break;
        
    }
    
    
    
    return 0;
}

int uniqueIDGenerator(int& ID)
{
    std::string key = "ID";
    if(!isAvailable(ID, key))
    {
       ID++;
       
       return 0;
    }

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
    
    return 0;
  }

bool checkPasswordLength(std::string const& password)
{
    if(password.length() < 9)
    {
        std::cout << "Password cannot be less than 9 characters.\n";
        return true;
    }
    return false;
}

int hashPassword(size_t& password, bool& isAllowed)
{
    
    if(isAllowed)
    {
    std::string unhashedPassword;
    int maxTries = -1;
    do
    {
    maxTries++;
    std::cout << "Create a password: ";
    std::getline(std::cin, unhashedPassword);
    if(checkRetryLimit(maxTries, isAllowed)) return 1;
    }while(blankChecker(unhashedPassword) || checkPasswordLength(unhashedPassword));
     std::hash<std::string> hashFunction;
     password = hashFunction(unhashedPassword);
  }
    
    
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

        for(auto const& [identifier, userData] : jsonFile.items())
        {
            if(userData.contains("ID") && userData["ID"] == searchTerm) return false;
        }

        
      }
    }

     if constexpr(std::is_same<T, std::string>::value)
     {

        if(key == "Name")
    {
           if(jsonFile.contains(searchTerm))
           {
            std::cout << "Name is already taken.\nChoose another name\n"; 
            return false;
            }         
        
       }
     }
     return true;

}



int storeData(std::string const& identifier, nlohmann::json const& userData)
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
     jsonFile[identifier] = userData;   // Add or update the user information under the unique identifier



     std::ofstream ofile(fileName);
     if(!ofile)
     {
        std::cerr << "Unable to open file.";
        return 1;
     }

     ofile << jsonFile.dump(4);
     ofile.close();
     return 0;
}

