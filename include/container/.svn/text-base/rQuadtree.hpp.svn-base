#ifndef R_QUADTREE_HPP
#define R_QUADTREE_HPP

#include <vector>
#include <map>
#include <set>
#include <iterator>

#include "math/rMath2.hpp"

enum rQuadtreeError{
	rQUADTREE_ERROR_NONE,
	rQUADTREE_ERROR_NOT_INIT,
	rQUADTREE_ERROR_ITEM_NOT_FOUND,
	rQUADTREE_ERROR_ITEM_ALREADY_IN_TREE,
	rQUADTREE_ERROR_ITEM_DOES_NOT_FIT
};

template <class T>
struct rQuadtreeNode_t{
	rQuadtreeNode_t(const rRectangle2& region, size_t depth);
	void InsertItem(T item);
	void RemoveItem(T item);

	rRectangle2 m_region;
	size_t m_depth;
	std::set<T> m_items;
	std::vector <rQuadtreeNode_t<T>*> m_children;

};

template <class T>
rQuadtreeNode_t<T>::rQuadtreeNode_t(const rRectangle2& region, size_t depth){
	m_region = region;
	m_depth = depth;
	m_children.resize(4);
	memset(&m_children[0] , 0 , sizeof(rQuadtreeNode_t<T>*) * 4);
}

template <class T>
void rQuadtreeNode_t<T>::InsertItem(T item){
	m_items.insert(item);
}

template <class T>
void rQuadtreeNode_t<T>::RemoveItem(T item){
	m_items.erase(item);
}


template <class T>
class rQuadtree{

public:
typedef T value_type;

typedef rVector2 point_type;
typedef rRectangle2 rect_type;
typedef rCircle2 circle_type;

typedef rQuadtreeNode_t<T> node_type;
typedef std::set<T> result_type;
typedef std::vector<const node_type*> node_list;
typedef std::map < value_type , node_type* > map_type;

public:
	rQuadtree();
	rQuadtree(const rect_type& region , size_t maxDepth);
	~rQuadtree();

	rQuadtreeError InsertItemWithPoint(const T& item, const point_type& p);
	rQuadtreeError InsertItemWithRect(const T& item , const rect_type& r);
	rQuadtreeError InsertItemWithCircle(const T& item , const circle_type& c);

	rQuadtreeError UpdateItemWithPoint(const T& item, const point_type& p);
	rQuadtreeError UpdateItemWithRect(const T& item , const rect_type& r);
	rQuadtreeError UpdateItemWithCircle(const T& item , const circle_type& c);

	void QueryItemsWithPoint(const point_type& p , result_type& result);
	void QueryItemsWithRect(const rect_type& r , result_type& result);
	void QueryItemsWithCircle(const circle_type& c, result_type& result);

	void QueryNodesWithRect(const rect_type& r, node_list& result);

	bool ContainsItem(const T& item);
	int ItemDepth(const T& item);
	bool RemoveItem(const T& item);

	void Init(const rect_type& region , size_t maxDepth);
	void Clear();
	void Trim();

	size_t MaxDepth() const;
	size_t NumItems() const;
	size_t NumNodes() const;
	rect_type GetArea() const;

private:

	void Uninit();
	void ClearRec(node_type* node);
	bool TrimRec(node_type* node);

	static void AddNodeItemsToResultSet(node_type* node , result_type& result);
	static void SubdivideRegion(const rect_type& r , rect_type rectArray []);
	static void DeleteNodes(node_type* node);

	node_type* InsertItemWithPointRec(const T& item, const point_type& p, node_type* node);
	node_type* InsertItemWithRectRec(const T& item, const rect_type& r, node_type* node);
	node_type* InsertItemWithCircleRec(const T& item, const circle_type& c, node_type* node);

	void QueryItemsWithPointRec(const point_type& p , result_type& result,  node_type* node);
	void QueryItemsWithRectRec(const rect_type& r , result_type& result,  node_type* node);
	void QueryItemsWithCircleRec(const circle_type& c, result_type& result,  node_type* node);

	void QueryNodesWithRectRec(const rect_type& r, node_list& result,  node_type* node);

	

private:
	size_t m_maxDepth;
	size_t m_numNodes;

	map_type m_items;
	node_type* m_root;
};

template <class T>
rQuadtree<T>::rQuadtree(){
	m_root = NULL;
	m_maxDepth = 0;
	m_numNodes = 0;
}

template <class T>
rQuadtree<T>::rQuadtree(const rect_type& region , size_t maxDepth){
	m_root = NULL;
	Init(region , maxDepth);
}

template <class T>
void rQuadtree<T>::Init(const rect_type& region , size_t maxDepth){
	Uninit();

	m_root = new node_type(region, 0);
	m_numNodes = 1;

	m_maxDepth = maxDepth;
}

template <class T>
rQuadtree<T>::~rQuadtree(){
	Uninit();
}

template <class T>
void rQuadtree<T>::Uninit(){
	m_items.clear();

	if (m_root)
		DeleteNodes(m_root);

	m_root = NULL;

	m_numNodes = 0;
}

template <class T>
void rQuadtree<T>::Clear(){
	if (!m_root)
		return;

	m_root->m_items.clear();
	ClearRec(m_root);

	m_items.clear();
}

template <class T>
void rQuadtree<T>::ClearRec(node_type* node){
	for (size_t i =0; i < node->m_children.size(); i++){

		if (node->m_children[i])
			ClearRec(node->m_children[i]);
	}

	node->m_items.clear();
}

template <class T>
size_t rQuadtree<T>::NumItems() const{
	return m_items.size();
}

template <class T>
size_t rQuadtree<T>::MaxDepth() const{
	return m_maxDepth;
}

template <class T>
typename rQuadtree<T>::rect_type rQuadtree<T>::GetArea() const{
	if (m_root)
		return m_root->m_region;
	else
		return rRectangle2::NullRectangle;
}

template <class T>
size_t rQuadtree<T>::NumNodes() const{
	return m_numNodes;
}

template <class T>
bool rQuadtree<T>::ContainsItem(const T& item){
	return m_items.find(item) != m_items.end();
}

template <class T>
int rQuadtree<T>::ItemDepth(const T& item){
	typename map_type::iterator it = m_items.find(item);

	if (it == m_items.end())
		return -1;

	return it->second->m_depth;
}


template <class T>
bool rQuadtree<T>::RemoveItem(const T& item){
	typename map_type::iterator result = m_items.find(item);

	if (result ==  m_items.end())
		return false;

	result->second->RemoveItem(item);
	m_items.erase(item);

	return true;
}

template <class T>
void rQuadtree<T>::AddNodeItemsToResultSet(node_type* node , result_type& result){
	std::copy (node->m_items.begin(), node->m_items.end(), std::inserter(result,result.begin()));
}

template <class T>
void rQuadtree<T>::SubdivideRegion(const rect_type& r , rect_type rectArray []){
	rVector2 tl = r.TopLeft();
	rVector2 br = r.Center();
	rectArray[0].Set(tl , br);

	tl = r.TopCenter();
	br = r.RightCenter();
	rectArray[1].Set(tl , br);

	tl = r.LeftCenter();
	br = r.BottomCenter();
	rectArray[2].Set(tl , br);

	tl = r.Center();
	br = r.BottomRight();
	rectArray[3].Set(tl , br);
}

template <class T>
void rQuadtree<T>::DeleteNodes(node_type* node){
	for (size_t i =0; i < node->m_children.size(); i++){

		if (node->m_children[i] )
			DeleteNodes(node->m_children[i]);

	}
	
	delete node;
}

template <class T>
void rQuadtree<T>::Trim(){
	if (m_root)
		TrimRec(m_root);
}

template <class T>
bool rQuadtree<T>::TrimRec(node_type* node){
	bool shouldTrim = true;

	for (size_t i =0; i < node->m_children.size(); i++){

		if (!node->m_children[i])
			continue;

		if (TrimRec(node->m_children[i])){
			delete node->m_children[i];
			node->m_children[i] = NULL;
			m_numNodes--;
		}
		else
			shouldTrim = false;

	}

	return shouldTrim && node->m_items.size() == 0;
}

template <class T>
rQuadtreeError rQuadtree<T>::InsertItemWithPoint(const T& item, const point_type& p){
	if (! m_root)
		return rQUADTREE_ERROR_NOT_INIT;

	if ( ContainsItem(item))
		return rQUADTREE_ERROR_ITEM_ALREADY_IN_TREE;

	if (!m_root->m_region.ContainsPoint(p))
		return rQUADTREE_ERROR_ITEM_DOES_NOT_FIT;

	typename rQuadtree<T>::node_type* target = InsertItemWithPointRec(item , p , m_root);
	m_items[item] = target;


	return rQUADTREE_ERROR_NONE;
}

template <class T>
typename rQuadtree<T>::node_type* rQuadtree<T>::InsertItemWithPointRec(const T& item, const point_type& p, node_type* node ){
	if (node->m_depth + 1< m_maxDepth){

		rect_type regions[4];
		SubdivideRegion(node->m_region , regions);

			for (int i = 0; i < 4; i ++){

				if (regions[i].ContainsPoint(p)){
					if (!node->m_children[i]){
						node->m_children[i] = new node_type(regions[i], node->m_depth + 1);
						m_numNodes++;
					}

					return InsertItemWithPointRec(item , p, node->m_children[i] );
				}
			}

	}

	node->InsertItem(item);
	return node;
	
}

template <class T>
rQuadtreeError rQuadtree<T>::InsertItemWithRect(const T& item , const rect_type& r){

	if (! m_root)
		return rQUADTREE_ERROR_NOT_INIT;

	if ( ContainsItem(item))
		return rQUADTREE_ERROR_ITEM_ALREADY_IN_TREE;

	if (!m_root->m_region.ContainsRectangle(r))
		return rQUADTREE_ERROR_ITEM_DOES_NOT_FIT;

	typename rQuadtree<T>::node_type* target = InsertItemWithRectRec(item , r , m_root);
	m_items[item] = target;

	return rQUADTREE_ERROR_NONE;
}

template <class T>
typename rQuadtree<T>::node_type* rQuadtree<T>::InsertItemWithRectRec(const T& item, const rect_type& r, node_type* node){
	if (node->m_depth + 1< m_maxDepth){

		rect_type regions[4];
		SubdivideRegion(node->m_region , regions);

			for (int i = 0; i < 4; i ++){

				if (regions[i].ContainsRectangle(r)){
					if (!node->m_children[i]){
						node->m_children[i] = new node_type(regions[i], node->m_depth + 1);
						m_numNodes++;
					}

					return InsertItemWithRectRec(item , r, node->m_children[i] );
				}
			}

	}

	node->InsertItem(item);
	return node;
}

template <class T>
rQuadtreeError rQuadtree<T>::InsertItemWithCircle(const T& item , const circle_type& c){
	if (! m_root)
		return rQUADTREE_ERROR_NOT_INIT;

	if ( ContainsItem(item))
		return rQUADTREE_ERROR_ITEM_ALREADY_IN_TREE;

	if (! rCollision2::RectangleContainsCircle(m_root->m_region , c))
		return rQUADTREE_ERROR_ITEM_DOES_NOT_FIT;

	typename rQuadtree<T>::node_type* target = InsertItemWithCircleRec(item , c , m_root);
	m_items[item] = target;

	return rQUADTREE_ERROR_NONE;
}

template <class T>
typename rQuadtree<T>::node_type* rQuadtree<T>::InsertItemWithCircleRec(const T& item, const circle_type& c, node_type* node){
	if (node->m_depth + 1< m_maxDepth){

		rect_type regions[4];
		SubdivideRegion(node->m_region , regions);

			for (int i = 0; i < 4; i ++){

				if (rCollision2::RectangleContainsCircle(regions[i], c)){
					if (!node->m_children[i]){
						node->m_children[i] = new node_type(regions[i], node->m_depth + 1);
						m_numNodes++;
					}

					return InsertItemWithCircleRec(item , c, node->m_children[i] );
				}
			}

	}

	node->InsertItem(item);
	return node;
}

template <class T>
void rQuadtree<T>::QueryItemsWithPoint(const point_type& p , result_type& result){
	result.clear();

	if (! m_root || ! m_root->m_region.ContainsPoint(p))
		return;

	AddNodeItemsToResultSet( m_root,result);
	QueryItemsWithPointRec(p , result, m_root);
}

template <class T>
void rQuadtree<T>::QueryItemsWithPointRec(const point_type& p , result_type& result,  node_type* node){
	
	for (size_t i =0; i < node->m_children.size(); i++){

		if (node->m_children[i] && node->m_children[i]->m_region.ContainsPoint(p)){
			AddNodeItemsToResultSet(node->m_children[i],result);
			QueryItemsWithPointRec(p , result, node->m_children[i]);
			return;
		}
	}

}

template <class T>
void rQuadtree<T>::QueryItemsWithRect(const rect_type& r , result_type& result){
	result.clear();

	if (! m_root || ! m_root->m_region.IntersectsRectangle(r))
		return;

	AddNodeItemsToResultSet( m_root,result);
	QueryItemsWithRectRec( r , result , m_root);
}

template <class T>
void rQuadtree<T>::QueryItemsWithRectRec(const rect_type& r , result_type& result,  node_type* node){

	for (size_t i =0; i < node->m_children.size(); i++){

		if (node->m_children[i] && node->m_children[i]->m_region.IntersectsRectangle(r)){
			AddNodeItemsToResultSet(node->m_children[i],result);
			QueryItemsWithRectRec(r , result, node->m_children[i]);
		}
	}
	
}

template <class T>
void rQuadtree<T>::QueryItemsWithCircle(const circle_type& c, result_type& result){
	result.clear();

	if (! m_root || !rCollision2::RectangleInstersectsCircle(m_root->m_region , c))
		return;

	AddNodeItemsToResultSet( m_root,result);
	QueryItemsWithCircleRec( c , result , m_root);
}

template <class T>
void rQuadtree<T>::QueryItemsWithCircleRec(const circle_type& c, result_type& result,  node_type* node){
		
	for (size_t i =0; i < node->m_children.size(); i++){

		if (node->m_children[i] && rCollision2::RectangleInstersectsCircle(node->m_children[i]->m_region,c)){
			AddNodeItemsToResultSet(node->m_children[i],result);
			QueryItemsWithCircleRec(c , result, node->m_children[i]);
		}
	}
}

template <class T>
void rQuadtree<T>::QueryNodesWithRect(const rect_type& r, node_list& result){
	result.clear();

	if (! m_root || ! m_root->m_region.IntersectsRectangle(r))
		return;

	result.push_back(m_root);
	QueryNodesWithRectRec(r , result , m_root);
}

template <class T>
void rQuadtree<T>::QueryNodesWithRectRec(const rect_type& r, node_list& result,  node_type* node){
		for (size_t i =0; i < node->m_children.size(); i++){

			if (node->m_children[i] && node->m_children[i]->m_region.IntersectsRectangle(r)){
				result.push_back(node->m_children[i]);
				QueryNodesWithRectRec(r , result, node->m_children[i]);
			}
		}
}

template <class T>
rQuadtreeError rQuadtree<T>::UpdateItemWithPoint(const T& item, const point_type& p){
	if (! m_root)
		return rQUADTREE_ERROR_NOT_INIT;

	if ( !ContainsItem(item))
		return rQUADTREE_ERROR_ITEM_NOT_FOUND;

	if (!m_root->m_region.ContainsPoint(p))
		return rQUADTREE_ERROR_ITEM_DOES_NOT_FIT;

	m_items[item]->RemoveItem(item);

	typename rQuadtree<T>::node_type* target = InsertItemWithPointRec(item , p , m_root);
	m_items[item] = target;

	return rQUADTREE_ERROR_NONE;
}

template <class T>
rQuadtreeError rQuadtree<T>::UpdateItemWithRect(const T& item , const rect_type& r){
	if (! m_root)
		return rQUADTREE_ERROR_NOT_INIT;

	if ( !ContainsItem(item))
		return rQUADTREE_ERROR_ITEM_NOT_FOUND;

	if (!m_root->m_region.ContainsRectangle(r))
		return rQUADTREE_ERROR_ITEM_DOES_NOT_FIT;

	m_items[item]->RemoveItem(item);

	typename rQuadtree<T>::node_type* target = InsertItemWithRectRec(item , r , m_root);
	m_items[item] = target;

	return rQUADTREE_ERROR_NONE;
}

template <class T>
rQuadtreeError rQuadtree<T>::UpdateItemWithCircle(const T& item , const circle_type& c){
	if (! m_root)
		return rQUADTREE_ERROR_NOT_INIT;

	if ( !ContainsItem(item))
		return rQUADTREE_ERROR_ITEM_NOT_FOUND;

	if (! rCollision2::RectangleContainsCircle(m_root->m_region , c))
		return rQUADTREE_ERROR_ITEM_DOES_NOT_FIT;

	m_items[item]->RemoveItem(item);

	typename rQuadtree<T>::node_type* target = InsertItemWithCircleRec(item , c , m_root);
	m_items[item] = target;

	return rQUADTREE_ERROR_NONE;
}

#endif