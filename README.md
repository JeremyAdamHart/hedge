# Hedge

Hedge is a half edge data structure designed to be as compact as possible through defining as many lookup operations implicitly as possible, and stored as flat arrays to guarantee as much cache coherency as possible.

## TriangleHalfEdge

For a half edge data structure consisting only of triangles, we can specify the data structure with only a face index array (such as those used in OpenGL's ELEMENT_ARRAY_BUFFER). The entries in this array are also conceptually the "Half edges", and an equally sized list is created that maps between the half edges and their pairs. Since the face index array will often be necessary for rendering purposes, the array of pairs is the only additional memory required.

The second optimization used is reordering the faces in the face index array such that each vertex index corresponds to a unique face that contains that vertex (Allowing for implicit vertex to face and vertex to half-edge lookups).
