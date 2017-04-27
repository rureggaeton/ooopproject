#pragma once
#include "Base.h"
#include "Container.h"
#include <algorithm>

class Shape : public Printable {
public:
	Shape() {
		_count++;
	}
	virtual ~Shape() {
		_count--;
	}
	static unsigned int GetCount() {
		return _count;
	};
	friend std::ostream & operator << (std::ostream & ioStream, const Shape & shape) {
		return ioStream << shape.GetPrintInfo();
	}
private:
	static unsigned int _count;
};

unsigned int Shape::_count = 0;

class Point : public Shape,  public Named {
public:
	Point(std::string name = "defaultPoint") : _x(0), _y(0), Named(name) {};
	Point(double x, double y, std::string name = "defaultPoint") : _x(x), _y(y), Named(name) {};
	Point(const Point & p) : _x(p._x), _y(p._y), Named(p.GetName()) {};
	~Point() {};
	double GetX() const {
		return _x;
	}
	double GetY() const {
		return _y;
	}
	void SetX(double x) {
		_x = x;
		return;
	}
	void SetY(double y) {
		_y = y;
		return;
	}
	double GetDistance(const Point & point) const {
		return sqrt((_x - point._x) * (_x - point._x) + (_y - point._y) * (_y - point._y));
	}
	std::string GetPrintInfo() const {
		std::string info = Named::GetPrintInfo() + "( " + std::to_string(_x) + ";" + std::to_string(_y) + " )\n";
		return info;
	}
private:
	double _x, _y;
};

class Circle : public Shape, public Named {
public:
	Circle() = delete;
	Circle(const Point & O, double r, std::string name = "defaultCircle") : _O(O), Named(name) {
		try{
			if (r < 0) {
				throw "Wrong radius";
			}
			_r = r;
		}
		catch (const std::string & str) {
			std::cout << str << std::endl;
		}
	};
	Circle(const Circle & circle) : _O(circle._O), _r(circle._r),Named(circle.GetName()) {}
	~Circle() {};
	double GetRadius() const {
		return _r;
	}
	Point GetCenter() const {
		return _O;
	}
	void SetRadius(double r) {
		try{
			if (r < 0) {
				throw "Wrong radius";
			}
			_r = r;
		}
		catch (const std::string & str) {
			std::cout << str << std::endl;
		}
		return;
	}
	void SetCenter(const Point & O) {
		_O = O;
		return;
	}
	std::string GetPrintInfo() const {
		std::string info = Named::GetPrintInfo() +"( Center: " + _O.GetPrintInfo() + "Radius: " + std::to_string(_r) + " )\n";
		return info;
	}
private:
	Point _O;
	double _r;
};

class Rect : public Shape, public Named {
public:
	Rect() = delete;
	Rect(const Point & p1, const Point & p2, std::string name = "defaultRect") : Named(name) {
		try{
			if (p1.GetX() > p2.GetX() || p1.GetY() > p2.GetY()) {
				throw "Wrong rectangle";
			}
			_p1 = p1;
			_p2 = p2;
		}
		catch (const std::string & str) {
			std::cout << str << std::endl;
		}
	};
	Rect(const Rect & rect) : _p1(rect._p1), _p2(rect._p2), Named(rect.GetName()) {};
	~Rect() {};
	Point GetPoint1() const {
		return _p1;
	}
	Point GetPoint2() const {
		return _p2;
	}
	double GetMinX() const {
		return std::min(_p1.GetX(), _p2.GetX());
	}
	double GetMaxX() const {
		return std::max(_p1.GetX(), _p2.GetX());
	}
	double GetMinY() const {
		return std::min(_p1.GetY(), _p2.GetY());
	}
	double GetMaxY() const {
		return std::min(_p1.GetY(), _p2.GetY());
	}
	void SetPoint1(const Point & p1) {
		try{
			if (p1.GetX() > _p2.GetX() || p1.GetY() > _p2.GetY()) {
				throw "Wrong rectangle";
			}
			_p1 = p1;
		}
		catch (const std::string & str) {
			std::cout << str << std::endl;
		}
		return;
	}
	void SetPoint2(const Point & p2) {
		try{
			if (_p1.GetX() > p2.GetX() || _p1.GetY() > p2.GetY()) {
				throw "Wrong rectangle";
			}
			_p2 = p2;
		}
		catch (const std::string & str) {
			std::cout << str << std::endl;
		}
		return;
	}
	void SetPoints(const Point & p1, const Point & p2) {
		try{
			if (p1.GetX() > p2.GetX() || p1.GetY() > p2.GetY()) {
				throw "Wrong rectangle";
			}
			_p1 = p1;
			_p2 = p2;
		}
		catch (const std::string & str) {
			std::cout << str << std::endl;
		}
		return;
	}
	std::string GetPrintInfo() const {
		std::string info = Named::GetPrintInfo() + "( P1: " + _p1.GetPrintInfo() + "P2: " + _p2.GetPrintInfo() + " )\n";
		return info;
	}
private:
	Point _p1;
	Point _p2;
};

class Square : public Rect {
public:
	Square(std::string name = "defaultSquare") = delete;
	Square(const Point & p1, double l, std::string name = "defaultSquare") : Rect(p1, Point(p1.GetX() + l, p1.GetY() + l), name) {};
	Square(const Square & sq) : Rect(sq) {};
	~Square() {};
	double GetSideLength() const {
		return this->GetMaxX() - this->GetMinX();
	}
	Point GetPoint() const {
		return this->GetPoint1();
	}
	void SetSideLength(double l) {
		this->SetPoint2(Point(GetPoint().GetX() + l, GetPoint().GetX() + l));
		return;
	}
	void SetPoint(const Point & p1) {
		double lenght = this->GetSideLength();
		*this = Square(p1, lenght);
		return;
	}
	std::string GetPrintInfo() const {
		std::string info = Named::GetPrintInfo() + "( P1: " + this->GetPoint().GetPrintInfo() + "SideLength: " + std::to_string(this->GetSideLength()) + " )\n";
		return info;
	}
};

class Polyline : public Shape, public Named {
public:
	Polyline(std::string name = "defaultPolyline") : _points(), Named(name) {};
	Polyline(const Container<Point *> & points, std::string name = "defaultPolyline") = delete;
	Polyline(const Polyline & polyline) = delete;
	~Polyline() {};
	std::string GetPrintInfo() const {
		std::string info = Named::GetPrintInfo() + "( Perimetr: " + std::to_string(this->GetLength()) +
			(GetFrontPoint() ? ("\nFirst point: " + GetFrontPoint()->GetPrintInfo()) : "") + (GetBackPoint() ? ("End point: " + GetBackPoint()->GetPrintInfo()) : "") + " )\n";
		return info;
	}
	void PushBackPoint(Point * point) {
		_points.push_back(point);
		return;
	}
	void PushFrontPoint(Point * point) {
		_points.push_front(point);
		return;
	}
	void PopBackPoint() {
		_points.pop_back();
		return;
	}
	void PopFrontPoint() {
		_points.pop_front();
		return;
	}
	Point * GetBackPoint() const {
		return _points.back();
	}
	Point * GetFrontPoint() const {
		return _points.front();
	}
	double GetLength() const {
		double ans = 0;
		if (_points.empty()) {
			return ans;
		}
		Point * prevPoint = _points.front();
		for (size_t i = 1; i < _points.size(); ++i) {
			Point * nextPoint = _points[i];
			ans += prevPoint->GetDistance(*nextPoint);
		}
		return ans;
	}
protected:
	Container<Point *> _points;
};

class Polygon : public Polyline {
public:
	Polygon(std::string name = "defaultPolygon") : Polyline(name) {};
	Polygon(const Container<Point *> & points, std::string name = "defaultPolygon") = delete;
	Polygon(const Polyline & polyline, std::string name = "defaultPolygon") = delete;
	Polygon(const Polygon & polygon) = delete;
	~Polygon() {};
	std::string GetPrintInfo() const {
		std::string info = Named::GetPrintInfo() + "( Perimetr: " + std::to_string(this->GetPerimetr()) + " )\n";
		return info;
	}
	double GetPerimetr() const {
		double ans = 0;
		if (_points.empty()) {
			return ans;
		}
		Point * prevPoint = _points.back();
		for (size_t i = 0; i < _points.size(); ++i) {
			Point * nextPoint = _points[i];
			ans += prevPoint->GetDistance(*nextPoint);
		}
		return ans;
	}
};