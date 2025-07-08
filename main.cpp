#include <iostream>
#include <hedge.hpp>


int main(){
	std::vector<hedge::TriangleHalfEdge<int>::Face> faces = {
		{1, 4, 5}, {1, 2, 3}, {5, 6, 7}, {3, 6, 7}, {0, 1, 3}, {0, 1, 2}, {3, 5, 7}, {3, 5, 6}
	};

	hedge::reorderFaces(faces, 8);

	for(auto face : faces){
		std::cout << "{" << face.idxs[0] << ", " << face.idxs[1] << ", " << face.idxs[2] << "}" << std::endl;
	}

	return 0;
}
