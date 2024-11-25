int getName(std::string& userInput, bool& isAllowed);
int getUserName(std::string& userInput, bool& isAllowed);
bool lengthChecker(std::string const& userInput);
bool checkRetryLimit(int maxTriesChecker, bool& isAllowed);
int blankChecker(std::string const& userInput);
int displayOptions();
void greetUser();
int getUserEmail(std::string& email, bool& isAllowed);
bool isValidEmail(std::string const& email);
bool isAvailable();
template<typename T>
int storeData(std::string const& key, T const& value);
