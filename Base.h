
#include <iostream>
#include <string>

class Printable {
public:
	virtual ~Printable() {};
	virtual std::string GetPrintInfo() const = 0;
};

class Named : public Printable {
public:
	explicit Named(const std::string & name) : _name(name) {};
	std::string GetName() const {
		return _name;
	}
	void SetName(const std::string & name) {
		_name = name;
	};
	std::string GetPrintInfo() const {
		return _name;
	}
private:
	std::string _name;
};