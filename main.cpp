#include "Container.h"
#include "ShapeFactory.h"

int main() {
	srand((int)std::time(nullptr));
	ShapeFactory factory;
	factory.RegisterInFactory<Square>("square");
	factory.RegisterInFactory<Point>("point");
	factory.RegisterInFactory<Circle>("circle");
	factory.RegisterInFactory<Rect>("rect");
	factory.RegisterInFactory<Polyline>("polyline");
	factory.RegisterInFactory<Polygon>("polygon");

	Container<Shape *> shapeContainer;
	unsigned int numb = 20 + rand() / 1000;
	for (size_t i = 0; i < numb; ++i) {
		shapeContainer.push_back(factory.CreateRandomShape());
	}
	std::cout << "Shape count: " << Shape::GetCount() << std::endl;
	for (Container<Shape *>::Iterator it = shapeContainer.begin(); it != shapeContainer.end(); ++it) {
		std::cout << **it << std::endl;
	}
	for (Container<Shape *>::Iterator it = shapeContainer.begin(); it != shapeContainer.end(); ++it) {
		delete *it;
	}
	shapeContainer.clear();
	std::cout << "Shape count after clear: " << Shape::GetCount() << std::endl;

	system("pause");
	return 0;
};