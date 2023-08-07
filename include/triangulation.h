#include "./primitive.h"
#include "./nmtype.h"

#ifdef __cplusplus
		extern "C" {
#endif

    void masks( TrianglePointers * srcTriangles, int srcCount, int maxWidth, int maxHeight, int * flags );;

    void sort( 	TrianglePointers * srcTriangles, int srcCount,
			    TrianglePointers * toSplitTriangles, int * toSplitTrianglesCount,
			    TrianglePointers * resultTriangles, int * resultCount,
			    int maxDstSize, int * flags );

    void squareSum( float * edgeArray, float * dX, float * dY, int edgeCount );

    void maxEdge( int * maxEdgeArray, float * edge1, float * edge2, float * edge3, int edgeCount );

    void split( TrianglePointers * toSplitTriangles, int toSplitTrianglesCount,
                TrianglePointers * splittedTriangles, int * splittedTrianglesCount,
                int * srcTreatedCount );

    void triangulation(	TrianglePointers* srcVertex, int srcCount,
						int maxWidth, int maxHeight,
						int maxDstSize, TrianglePointers* dstVertex,
						int* srcTreatedCount );

#ifdef __cplusplus
	};
#endif