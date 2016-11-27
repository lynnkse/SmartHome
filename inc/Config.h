#include <map>
#include <string>

using namespace std;

class Config
{
public:
	Config() {}
	~Config() {};
	void SetData(const string& _key, const string& _val);
	const string& GetData(const string& _key) const;
	const map<string, string>& GetConfig() const;
private:
	map<string, string> m_data;
};
