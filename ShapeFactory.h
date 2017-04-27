#pragma once
#include "Shape.h"
#include <random>
#include <map>
#include <string>
#include <ctime>

double Rand(double min = 0)
{
	double f = (double)rand() / 100;
	return min + f;
}

class AbstractShapeCreator {
public:
	AbstractShapeCreator() {};
	virtual ~AbstractShapeCreator() {};
	virtual Shape * Create() const = 0;
};

template <class T>
class ShapeCreator : public AbstractShapeCreator
{
public:
	ShapeCreator<T>() {};
	virtual Shape * Create() const  {
		new T();
	}
};

class ShapeFactory {
public:
	ShapeFactory() {};
	template <class T>
	void RegisterInFactory(const std::string & str) {
		try {
			if (_factoryMap.find(str) != _factoryMap.end()) {
				throw "Repeated insertion";
			}
			_factoryMap[str] = new ShapeCreator<T>();
		}
		catch (const std::string & str) {
			std::cout << str << std::endl;
		}
		return;
	}
	Shape * CreateShape(const std::string & str) {
		try {
			if (_factoryMap.find(str) == _factoryMap.end()) {
				throw "Wrong shape";
			}
			return _factoryMap[str]->Create();
		}
		catch (const std::string & str) {
			std::cout << str << std::endl;
		}
	}
	Shape * CreateRandomShape() {
		try {
			if (_factoryMap.empty()) {
				throw "Empty FactorMap";
			}
			unsigned int number = rand() % _factoryMap.size();
			FactoryMap::iterator it = _factoryMap.begin();
			for (size_t i = 0; it != _factoryMap.end() && i < number; ++it, ++i);
			try {
				if (it == _factoryMap.end()) {
					throw "Out of range map";
				}
				return it->second->Create();
			}
			catch (const std::string & str) {
				std::cout << str << std::endl;
			}
		}
		catch (const std::string & str) {
			std::cout << str << std::endl;
		}
	}
private:
	typedef std::map<std::string, AbstractShapeCreator *> FactoryMap;
	FactoryMap _factoryMap;
};


Shape * ShapeCreator<Point>::Create() const {
	double x = Rand(-Rand());
	double y = Rand(-Rand());
	return new Point(x, y);
}

Shape * ShapeCreator<Circle>::Create() const {
	double x = Rand(-Rand());
	double y = Rand(-Rand());
	double r = Rand();
	return new Circle(Point(x, y), r);
}

Shape * ShapeCreator<Rect>::Create() const {
	double x1 = Rand(-Rand());
	double y1 = Rand(-Rand());
	double x2 = x1 + Rand();
	double y2 = y1 + Rand();
	return new Rect(Point(x1, y1), Point(x2, y2));
}

Shape * ShapeCreator<Square>::Create() const {
	double x = Rand(-Rand());
	double y = Rand(-Rand());
	double l = Rand();
	return new Square(Point(x, y), l);
}

Shape * ShapeCreator<Polyline>::Create() const {
	unsigned int number = rand() / 1000;
	Polyline * newPolyline = new Polyline();
	for (size_t i = 0; i < number; ++i) {
		double x = Rand(-Rand());
		double y = Rand(-Rand());
		newPolyline->PushBackPoint(new Point(x, y));
	}
	return newPolyline;
}

Shape * ShapeCreator<Polygon>::Create() const {
	unsigned int number = (int) rand() / 1000;
	Polygon * newPolygon = new Polygon();
	for (size_t i = 0; i < number; ++i) {
		double x = Rand(-Rand());
		double y = Rand(-Rand());
		newPolygon->PushBackPoint(new Point(x, y));
	}
	return newPolygon;
}





