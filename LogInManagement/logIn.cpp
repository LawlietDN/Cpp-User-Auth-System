#include <iostream>
#include <fstream>
#include <nlohmann-json.hpp>
class LoginManager
{
private:
    std::string fullName;
    std::string password;
    std::string fileName = "userData.json";
    nlohmann::json storedData;
    size_t hashedPassword = hashPassword();

public:

    LoginManager(std::string const& name, std::string const& pwd)
    {
        fullName = name;
        password = pwd;
    }
    
    bool authentication()
    {
        std::cout << "DEBUG: INSIDE THE FUNCTION AUTHETNITUCION";
        std::string loadedPassword;
        std::string loadedName;
        loadData(loadedName, loadedPassword);
        std::cout << loadedPassword;

    }

    int loadData(std::string& loadedFullName, std::string& loadedPassword)
    {
        std::ifstream ifile(fileName);
        
        if(!ifile)
        {
            std::cerr << "An error occured while opening the file,\n";
            return 1;
        }
        try
        {
            ifile >> storedData;
        }
        catch(nlohmann::json::parse_error& err)
        {
            std::cerr << "An error occured while parsing the JSON file: " << err.what() << '\n';
        }
        for(auto const& [identifer, data] : storedData.items())
        {
            if(!storedData.contains(fullName))
            {

            }
        }

        
            for(auto const& [identifer, data] : storedData.items())
            {
                if(identifer == loadedFullName)
                {
                    loadedPassword = data["Hashed Password"];
                }
            }
        
        return 0;
    }

    int hashPassword()
    {
         std::hash<std::string> hashFunction;
         return hashFunction(password);
    }
    
};




void promptCredentials(std::string& name, std::string& password)
{
    std::cout << "Full name: ";
    std::getline(std::cin, name);

    std::cout << "Password: ";
    std::getline(std::cin, password);
}
