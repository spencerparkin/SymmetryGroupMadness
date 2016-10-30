// BoxTree.h

#pragma once

#include "Rectangle.h"
#include "Container.h"

struct BoxTreeStats
{
	int vertexGroupCount;
	int solvedVertexGroupCount;
};

class BoxTreeNode
{
public:

	BoxTreeNode( void );
	virtual ~BoxTreeNode( void );

	virtual bool InsertVertex( const Vertex& vertex ) = 0;
	virtual void CalculateBoxTreeStats( BoxTreeStats& boxTreeStats ) = 0;

	Rectangle_ box;
};

class BoxTreeBranchNode : public BoxTreeNode
{
public:

	BoxTreeBranchNode( void );
	virtual ~BoxTreeBranchNode( void );

	virtual bool InsertVertex( const Vertex& vertex ) override;
	virtual void CalculateBoxTreeStats( BoxTreeStats& boxTreeStats ) override;

	BoxTreeNode* node[2];
};

class BoxTreeLeafNode : public BoxTreeNode
{
public:

	BoxTreeLeafNode( void );
	virtual ~BoxTreeLeafNode( void );

	virtual bool InsertVertex( const Vertex& vertex ) override;
	virtual void CalculateBoxTreeStats( BoxTreeStats& boxTreeStats ) override;

	bool IsVertexGroupSolved( const VertexList& vertexList );

	typedef std::list< VertexList* > VertexGroupList;
	VertexGroupList vertexGroupList;
};

BoxTreeNode* GenerateBoxTree( const Rectangle_& rectangle, double maxLeafArea );

// BoxTree.h
