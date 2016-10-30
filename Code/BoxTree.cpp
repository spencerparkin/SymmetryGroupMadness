// BoxTree.cpp

#include "BoxTree.h"

BoxTreeNode::BoxTreeNode( void )
{
}

/*virtual*/ BoxTreeNode::~BoxTreeNode( void )
{
}

BoxTreeBranchNode::BoxTreeBranchNode( void )
{
	node[0] = nullptr;
	node[1] = nullptr;
}

/*virtual*/ BoxTreeBranchNode::~BoxTreeBranchNode( void )
{
	delete node[0];
	delete node[1];
}

/*virtual*/ bool BoxTreeBranchNode::InsertVertex( const Vertex& vertex )
{
	for( int i = 0; i < 2; i++ )
		if( node[i]->box.ContainsPoint( vertex.point ) )
			return node[i]->InsertVertex( vertex );

	return false;
}

/*virtual*/ void BoxTreeBranchNode::CalculateBoxTreeStats( BoxTreeStats& boxTreeStats )
{
	for( int i = 0; i < 2; i++ )
		node[i]->CalculateBoxTreeStats( boxTreeStats );
}

BoxTreeLeafNode::BoxTreeLeafNode( void )
{
}

/*virtual*/ BoxTreeLeafNode::~BoxTreeLeafNode( void )
{
	for( VertexGroupList::iterator iter = vertexGroupList.begin(); iter != vertexGroupList.end(); iter++ )
		delete *iter;
}

/*virtual*/ bool BoxTreeLeafNode::InsertVertex( const Vertex& vertex )
{
	if( !box.ContainsPoint( vertex.point ) )
		return false;

	double eps = 1e-7;
	for( VertexGroupList::iterator iter = vertexGroupList.begin(); iter != vertexGroupList.end(); iter++ )
	{
		VertexList* vertexList = *iter;
		const Vertex& firstVertex = *vertexList->begin();
		if( c3ga::norm( firstVertex.point - vertex.point ) < eps )
		{
			vertexList->push_back( vertex );
			return true;
		}
	}

	VertexList* vertexList = new VertexList();
	vertexList->push_back( vertex );
	vertexGroupList.push_back( vertexList );
	return true;
}

/*virtual*/ void BoxTreeLeafNode::CalculateBoxTreeStats( BoxTreeStats& boxTreeStats )
{
	boxTreeStats.vertexGroupCount += ( int )vertexGroupList.size();
	
	for( VertexGroupList::iterator iter = vertexGroupList.begin(); iter != vertexGroupList.end(); iter++ )
	{
		VertexList* vertexList = *iter;

		if( IsVertexGroupSolved( *vertexList ) )
			boxTreeStats.solvedVertexGroupCount++;
	}
}

bool BoxTreeLeafNode::IsVertexGroupSolved( const VertexList& vertexList )
{
	VertexList::const_iterator iter = vertexList.cbegin();
	const Vertex& anchorVtx = *iter;
	iter++;

	double eps = 1e-7;

	while( iter != vertexList.cend() )
	{
		const Vertex& vtx = *iter;

		if( fabs( vtx.u - anchorVtx.u ) >= eps )
			return false;
		if( fabs( vtx.v - anchorVtx.v ) >= eps )
			return false;

		iter++;
	}

	return true;
}

BoxTreeNode* GenerateBoxTree( const Rectangle_& rectangle, double maxLeafArea )
{
	BoxTreeNode* node = nullptr;

	double area = rectangle.GetArea();
	if( area <= maxLeafArea )
	{
		BoxTreeLeafNode* leafNode = new BoxTreeLeafNode();

		node = leafNode;
	}
	else
	{
		BoxTreeBranchNode* branchNode = new BoxTreeBranchNode();

		Rectangle_ subRectangle[2];

		if( rectangle.GetAspectRatio() > 1.0 )
		{
			double xCenter = ( rectangle.xMax + rectangle.xMin ) / 2.0;
			subRectangle[0].xMin = rectangle.xMin;
			subRectangle[0].xMax = xCenter;
			subRectangle[0].yMin = rectangle.yMin;
			subRectangle[0].yMax = rectangle.yMax;
			subRectangle[1].xMin = xCenter;
			subRectangle[1].xMax = rectangle.xMax;
			subRectangle[1].yMin = rectangle.yMin;
			subRectangle[1].yMax = rectangle.yMax;
		}
		else
		{
			double yCenter = ( rectangle.yMax + rectangle.yMin ) / 2.0;
			subRectangle[0].xMin = rectangle.xMin;
			subRectangle[0].xMax = rectangle.xMax;
			subRectangle[0].yMin = rectangle.yMin;
			subRectangle[0].yMax = yCenter;
			subRectangle[1].xMin = rectangle.xMin;
			subRectangle[1].xMax = rectangle.xMax;
			subRectangle[1].yMin = yCenter;
			subRectangle[1].yMax = rectangle.yMax;
		}

		branchNode->node[0] = GenerateBoxTree( subRectangle[0], maxLeafArea );
		branchNode->node[1] = GenerateBoxTree( subRectangle[1], maxLeafArea );

		node = branchNode;
	}

	node->box = rectangle;

	return node;
}

// BoxTree.cpp