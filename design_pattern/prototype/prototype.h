#include <string>
using namespace std;

class Document
{
public:
	virtual Document *clone() = 0;
	virtual void edit(string content) = 0;
	virtual string get_content() = 0;
	virtual ~Document() {}
};