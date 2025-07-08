// Copyright (c) 2025 Jeremy Hart (JeremyAdamHart)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>
#include <limits>

namespace hedge{

template<class Index = size_t>
class TriangleHalfEdge{
public:
    TriangleHalfEdge(std::vector<Index> faces):m_faces(std::move(faces)){}

    struct Vertex{
        Index idx;
    };
    struct Face{
        Index verts [3];
    };
    struct HalfEdge{
        Index idx;
    };

    auto vertex(HalfEdge h)->Vertex; // Identity function
    auto face(HalfEdge h)->Face; // Implicitly
    auto next(HalfEdge h)->HalfEdge; // Implicitly
    auto pair(HalfEdge h)->HalfEdge; // Pair map

    auto vertex(Face f)->Vertex; // Implicitly
    auto edge(Face f)->HalfEdge; // Implicitly
    auto neighbours(Face f)->std::vector<Face>;

    // Requires # of faces greater than number of vertices.
    // Vertex index is the index of the face that vertex lies on
    // 
    auto edge(Vertex v)->HalfEdge; // ???
    auto face(Vertex v)->Face; // ??? Rearrange so the vertices and faces align some
    auto neighbours(Vertex v)->std::vector<Vertex>; // ???

private:
    //Half Edge "struct"
    std::vector<Face> m_faces;
    std::vector<HalfEdge> m_pairs;

    
}; 

auto reorderFaces(std::vector<TriangleHalfEdge<int>::Face>& faces, size_t numVertices)->void
{
    std::vector<int> vertexToFace;
    std::vector<unsigned char> valence;
    vertexToFace.resize(numVertices, -1);
    valence.resize(numVertices, 0);

    for(size_t f=0; f<faces.size(); f++){
        for(auto v : faces[f].verts){
            valence[v]++;
            vertexToFace[v] = f;
        }
    }

    auto assignFace = [&](int f){
        int idx = -1;
        unsigned char minValence = std::numeric_limits<unsigned char>::max();
        for(auto v : faces[f].verts){
            if(vertexToFace[v] == f) return;
            if(vertexToFace[v] < f) continue;

            if(valence[v] < minValence){
                minValence = valence[v];
                idx = v;
            }
        }

        assert(idx != -1);
        vertexToFace[idx] = f;
    };

    for(size_t f=0; f<faces.size(); f++){
        assignFace(f);
    }

    // Rearrange faces
    for(size_t v=0; v < vertexToFace.size(); v++){
        int target = vertexToFace[v];
        while(target < v){
            target = vertexToFace[target];
        }
        if(target != v) std::swap(faces[v], faces[target]);    
    }
}

}