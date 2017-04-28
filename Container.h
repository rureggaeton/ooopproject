#pragma once

template<class T>
class Container {
public:
	Container() : _front(nullptr), _back(nullptr), _size(0) {};
	Container(const Container& iOther) {
		for (Iterator it = iOther.begin(); it != iOther.end(); ++it) {
			this->push_back(*it);
		}
	};
	~Container();
	unsigned int size() const;
	bool empty() const;
	T & back() const;
	T & front() const;
	void push_back(const T & value);
	void push_front(const T & value);
	void pop_back();
	void pop_front();
	void clear();
	T & operator[](size_t i) const;
private:
	struct Vertex {
		Vertex() = delete;
		~Vertex() {
		}
		explicit Vertex(const T & value) : _next(nullptr), _prev(nullptr), _value(value) {};
		Vertex * _next;
		Vertex * _prev;
		T _value;
	};
public:
	class Iterator {
	public:
		Iterator() : _currVertex(nullptr) {};
		Iterator(Vertex * vertex) : _currVertex(vertex) {};
		Iterator & operator ++();
		bool operator !=(const Iterator & iter) const;
		T operator *();
		T * operator ->();
	private:
		Vertex * _currVertex;
	};
	Iterator begin() const;
	Iterator end() const;
private:
	Vertex * _front;
	Vertex * _back;
	unsigned int _size;
};

template <class T>
typename Container<T>::Iterator & Container<T>::Iterator::operator ++() {
	try {
		if (!_currVertex) {
			throw "Out of range";
		}
		_currVertex = _currVertex->_next;
		return *this;
	}
	catch (const std::string & str) {
		std::cout << str << std::endl;
	}
}

template <class T>
bool Container<T>::Iterator::operator !=(const typename Container<T>::Iterator & iter) const {
	return _currVertex != iter._currVertex;
}

template <class T>
T Container<T>::Iterator::operator *() {
	try {
		if (!_currVertex) {
			throw "Out of range";
		}
		return _currVertex->_value;
	}
	catch (const std::string & str) {
		std::cout << str << std::endl;
	}
}

template <class T>
T * Container<T>::Iterator::operator ->() {
	try {
		if (!_currVertex) {
			throw "Out of range";
		}
		return &_currVertex->_value;
	}
	catch (const std::string & str) {
		std::cout << str << std::endl;
	}
}

template<class T>
Container<T>::~Container() {
	this->clear();
}

template<class T>
unsigned int Container<T>::size() const {
	return _size;
}

template<class T>
bool Container<T>::empty() const {
	return (_size == 0);
}

template<class T>
T & Container<T>::back() const {
	try{
		if (this->empty()) {
			throw "Out of range";
		};
		return _back->_value;
	}
	catch(const std::string & str) {
		std::cout << str << std::endl;
	}
}

template<class T>
T & Container<T>::front() const {
	try{
		if (this->empty()) {
			throw "Out of range";
		};
		return _front->_value;
	}
	catch (const std::string & str) {
		std::cout << str << std::endl;
	}
}

template<class T>
void Container<T>::push_back(const T & value) {
	Vertex * newVertex = new Vertex(value);
	if (!this->empty()) {
		_back->_next = newVertex;
	}
	else {
		_front = newVertex;
	}
	newVertex->_prev = _back;
	_back = newVertex;
	_size++;
	return;
}

template<class T>
void Container<T>::push_front(const T & value) {
	Vertex * newVertex = new Vertex(value);
	if (!this->empty()) {
		_front->_prev = newVertex;
	}
	else {
		_back = newVertex;
	}
	newVertex->_next = _front;
	_front = newVertex;
	_size++;
	return;
}

template<class T>
void Container<T>::pop_back() {
	try{
		if (this->empty()) {
			throw "Out of range";
		};
		_size--;
		Vertex * newEnd = _back->_prev;
		delete _back;
		_back = newEnd;
		if (_size == 0) {
			_front = nullptr;
		}
	}
	catch (const std::string & str) {
		std::cout << str << std::endl;
	}
	return;
}

template<class T>
void Container<T>::pop_front() {
	try{
		if (this->empty()) {
			throw "Out of range";
		};
		_size--;
		Vertex * newFront = _front->_next;
		delete _front;
		_front = newFront;
		if (_size == 0) {
			_back = nullptr;
		}
	}
	catch (const std::string & str) {
		std::cout << str << std::endl;
	}
	return;
}

template<class T>
void Container<T>::clear() {
	while (_size > 0) {
		this->pop_back();
	}
}

template<class T>
typename Container<T>::Iterator Container<T>::begin() const {
	return Iterator(_front);
}

template<class T>
typename Container<T>::Iterator Container<T>::end() const {
	return Iterator();
}

template<class T>
T & Container<T>::operator[](size_t i) const {
	try {
		if (i < 0 && i >= _size) {
			throw "Out of range";
		}
		size_t j = 0;
		Vertex * currNode = _front;
		while (j++ != i) {
			currNode = currNode->_next;
		}
		return currNode->_value;
	}
	catch (const std::string & str) {
		std::cout << str << std::endl;
		return front();
	}
}