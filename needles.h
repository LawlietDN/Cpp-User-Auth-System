#include <nlohmann-json.hpp>
int getName(std::string& userInput, bool& isAllowed);
int getUserName(std::string& userInput, bool& isAllowed);
bool lengthChecker(std::string const& userInput);
bool checkRetryLimit(int maxTriesChecker, bool& isAllowed);
int blankChecker(std::string const& userInput);
int displayOptions();
void greetUser();
int getUserEmail(std::string& email, bool& isAllowed);
bool isValidEmail(std::string const& email);
template<typename T>
bool isAvailable(T& searchTerm, std::string const& key);
int storeData(std::string const& identifier, nlohmann::json const& userData);
int uniqueIDGenerator(int& ID);