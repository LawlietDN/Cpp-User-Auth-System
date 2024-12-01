#include <fstream>
#include <iostream>
#include <nlohmann-json.hpp>


enum { SUCCESS = 0, FAILURE = 1};
class LoginManager
{
private:
    std::string fullName;
    std::string password;
    std::string fileName = "userData.json";
    nlohmann::json storedData;


    size_t hashPassword(std::string const& pwd)
    {
         std::hash<std::string> hashFunction;
         return hashFunction(pwd);
    }
public:

    LoginManager(std::string const& name, std::string const& pwd)
    {
        fullName = name;
        password = pwd;
    }
    
    bool authentication()
    {

        size_t storedPassword;
        if(loadData(storedPassword) != SUCCESS)
        {
            return false;
        }


        size_t inputHash = hashPassword(password);
        size_t storedHash = storedPassword;

        if(inputHash == storedHash)
        {
            
            return true;
        }
        
        return false;

    }





    int loadData(size_t& loadedPassword)
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
        catch(nlohmann::json::parse_error const& err)
        {
            std::cerr << "An error occured while parsing the JSON file: " << err.what() << '\n';
            return FAILURE;
        }

        if(storedData.contains(fullName))
        {
            try
            {
                for(auto const& [fullName, data] : storedData.items())
                {
                    loadedPassword = data["Hashed Password"];
                }
               
            }
            catch(nlohmann::json_abi_v3_11_2::detail::type_error const& err)
            {
                std::cerr << "No idea what happend, but here take a look at this error message: " << err.what();
            }
        }
        else
        {
            return FAILURE;
        }
        return 0;
    }

    
};




void promptCredentials(std::string& name, std::string& password)
{
    
    std::cout << "Full name: ";
    std::getline(std::cin, name);

    std::cout << "Password: ";
    std::getline(std::cin, password);
    
}


void logInMessage()
{
    std::cout << "Sucessfully logged in.\n";
}