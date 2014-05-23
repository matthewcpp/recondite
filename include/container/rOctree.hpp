#ifndef R_OCTREE_HPP
#define R_OCTREE_HPP

#include <vector>
#include <map>
#include <set>
#include <iterator>

#include "rAlignedBox3.hpp"
#include "rVector3.hpp"
#include "rSphere.hpp"
#include "rLine3.hpp"


enum rOctreeError{
	rOCTREE_ERROR_NONE,
	rOCTREE_ERROR_NOT_INIT,
	rOCTREE_ERROR_ITEM_NOT_FOUND,
	rOCTREE_ERROR_ITEM_ALREADY_IN_TREE,
	rOCTREE_ERROR_ITEM_DOES_NOT_FIT
};

template <class T>
struct rOctreeNode_t{
	rOctreeNode_t(const rAlignedBox3& volume, size_t depth);

	void InsertItem(const T& item);
	void RemoveItem(const T& item);

	rAlignedBox3 m_volume;
	size_t m_depth;
	std::set<T> m_items;
	std::vector <rOctreeNode_t<T>*> m_children;
};

template <class T>
rOctreeNode_t<T>::rOctreeNode_t(const rAlignedBox3& volume, size_t depth){
	m_volume = volume;
	m_depth = depth;
	m_children.resize(8);
	memset(&m_children[0] , 0 , sizeof(rOctreeNode_t<T>*) * 8);
}

template <class T>
void rOctreeNode_t<T>::InsertItem(const T& item){
	m_items.insert(item);
}

template <class T>
void rOctreeNode_t<T>::RemoveItem(const T& item){
	m_items.erase(item);
}


template <class T>
class rOctree{
public:
	typedef T value_type;

	typedef rVector3 point_type;
	typedef rAlignedBox3 box_type;
	typedef rSphere sphere_type;
	typedef rRay3 ray_type;

	typedef rOctreeNode_t<T> node_type;
	typedef std::set<T> result_type;
	typedef std::vector<const node_type*> node_list;
	typedef std::map < value_type , node_type* > map_type;

public:
	rOctree();
	rOctree(const box_type& volume , size_t maxDepth);
	~rOctree();

	rOctreeError InsertItemWithPoint(const T& item, const point_type& p);
	rOctreeError InsertItemWithBox(const T& item, const box_type& b);
	rOctreeError InsertItemWithSphere(const T& item, const sphere_type& s);

	rOctreeError UpdateItemWithPoint(T& item, const point_type& p);
	rOctreeError UpdateItemWithBox(T& item, const box_type& b);
	rOctreeError UpdateItemWithSphere(T& item, const sphere_type& s);

	void QueryItemsWithPoint(const point_type& p , result_type& result);
	void QueryItemsWithBox(const box_type& b , result_type& result);
	void QueryItemsWithSphere(const sphere_type& s, result_type& result);
	void QueryItemsWithRay(const ray_type& r , result_type& result);

	void QueryNodesWithBox(const box_type& b , node_list& result);

	bool ContainsItem(const T& item);
	int ItemDepth(const T& item);
	bool RemoveItem(const T& item);

	void Init(const box_type& Volume , size_t maxDepth);
	void Clear();
	void Trim();
	
	size_t ItemDepth(const T& item) const;

	size_t MaxDepth() const;
	size_t NumNodes() const;
	size_t NumItems() const;
	box_type GetVolume() const;

private:
	node_type* InsertItemWithPointRec(const T& item, const point_type& p, node_type* node);
	node_type* InsertItemWithBoxRec(const T& item, const box_type& n, node_type* node);
	node_type* InsertItemWithSphereRec(const T& item, const sphere_type& s, node_type* node);

	void QueryItemsWithPointRec(const point_type& p , result_type& result,  node_type* node);
	void QueryItemsWithBoxRec(const box_type& b , result_type& result,  node_type* node);
	void QueryItemsWithSpehereRec(const sphere_type& s , result_type& result , node_type* node);
	void QueryItemsWithRayRec(const ray_type& r , result_type& result , node_type* node);

	void QueryNodesWithBoxRec(const box_type& b , node_list& result,  node_type* node);

	void Uninit();
	void ClearRec(node_type* node);
	bool TrimRec(node_type* node);

	static void DeleteNodes(node_type* node);
	static void SubdivideVolume(const box_type& box , box_type boxArray []);
	static void AddNodeItemsToResultSet(node_type* node , result_type& result);

private:
	size_t m_maxDepth;
	size_t m_numNodes;

	map_type m_items;
	node_type* m_root;
};

template <class T>
rOctree<T>::rOctree(){
	m_root = NULL;
	m_maxDepth = 0;
	m_numNodes = 0;
}

template <class T>
rOctree<T>::rOctree(const box_type& volume , size_t maxDepth){
	m_root = NULL;
	Init(volume , maxDepth);
}

template <class T>
rOctree<T>::~rOctree(){
	Uninit();
}

template <class T>
size_t rOctree<T>::NumItems() const{
	return m_items.size();
}

template <class T>
size_t rOctree<T>::MaxDepth() const{
	return m_maxDepth;
}

template <class T>
size_t rOctree<T>::NumNodes() const{
	return m_numNodes;
}

template <class T>
void rOctree<T>::Init(const box_type& volume , size_t maxDepth){
	Uninit();

	m_root = new node_type(volume, 0);
	m_numNodes = 1;

	m_maxDepth = maxDepth;
}

template <class T>
void rOctree<T>::Uninit(){
	m_items.clear();

	if (m_root)
		DeleteNodes(m_root);

	m_root = NULL;

	m_numNodes = 0;
}

template <class T>
void rOctree<T>::DeleteNodes(node_type* node){
	for (size_t i =0; i < node->m_children.size(); i++){
		
		if (node->m_children[i] )
			DeleteNodes(node->m_children[i]);
		
	}
	
	delete node;
}


template <class T>
void rOctree<T>::Clear(){
	if (!m_root)
		return;

	m_root->m_items.clear();
	ClearRec(m_root);

	m_items.clear();
}

template <class T>
void rOctree<T>::ClearRec(node_type* node){
	for (size_t i =0; i < node->m_children.size(); i++){

		if (node->m_children[i])
			ClearRec(node->m_children[i]);
	}

	node->m_items.clear();
}

template <class T>
typename rOctree<T>::box_type rOctree<T>::GetVolume() const{
	if (m_root)
		return m_root->m_volume;
	else
		return rAlignedBox3::NullBox;
}

template <class T>
void rOctree<T>::Trim(){
	if (m_root)
		TrimRec(m_root);
}

template <class T>
bool rOctree<T>::TrimRec(node_type* node){
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
size_t rOctree<T>::ItemDepth(const T& item) const{
	typename map_type::const_iterator it = m_items.find(item);

	if (it == m_items.end())
		return -1;

	return it->second->m_depth;
}

template <class T>
bool rOctree<T>::ContainsItem(const T& item){
	return m_items.find(item) != m_items.end();
}

template <class T>
int rOctree<T>::ItemDepth(const T& item){
	typename rOctree<T>::map_type::iterator it = m_items.find(item);

	if (it == m_items.end())
		return -1;

	return it->second->m_depth;
}


template <class T>
bool rOctree<T>::RemoveItem(const T& item){
	typename rOctree<T>::map_type::iterator result = m_items.find(item);

	if (result ==  m_items.end())
		return false;

	result->second->RemoveItem(item);
	m_items.erase(item);

	return true;
}

template <class T>
void rOctree<T>::SubdivideVolume(const box_type& box , box_type boxArray []){
	rVector3 center = box.Center();

	boxArray[0].Set(box.max , center);

	boxArray[1].max.Set(center.x , box.max.y , box.max.z);
	boxArray[1].min.Set(box.min.x , center.y , center.z);

	boxArray[2].max.Set(center.x , box.max.y , center.z);
	boxArray[2].min.Set(box.min.x , center.y , box.min.z);

	boxArray[3].max.Set(box.max.x , box.max.y , center.z);
	boxArray[3].min.Set(center.x , center.y , box.min.z);



	boxArray[4].max.Set(box.max.x , center.y , box.max.z);
	boxArray[4].min.Set(center.x , box.min.y , center.z);

	boxArray[5].max.Set(center.x , center.y , box.max.z);
	boxArray[5].min.Set(box.min.x , box.min.y , center.z);

	boxArray[6].Set( center , box.min);

	boxArray[7].max.Set(box.max.x , center.y , center.z);
	boxArray[7].min.Set(center.x , box.min.y , box.min.z);
}

template <class T>
void rOctree<T>::AddNodeItemsToResultSet(node_type* node , result_type& result){
	std::copy (node->m_items.begin(), node->m_items.end(), std::inserter(result,result.begin()));
}

template <class T>
rOctreeError rOctree<T>::InsertItemWithPoint(const T& item, const point_type& p){
	if (! m_root)
		return rOCTREE_ERROR_NOT_INIT;

	if ( ContainsItem(item))
		return rOCTREE_ERROR_ITEM_ALREADY_IN_TREE;

	if (!m_root->m_volume.ContainsPoint(p))
		return rOCTREE_ERROR_ITEM_DOES_NOT_FIT;

	typename rOctree<T>::node_type* target = InsertItemWithPointRec(item , p , m_root);
	m_items[item] = target;


	return rOCTREE_ERROR_NONE;
}

template <class T>
typename rOctree<T>::node_type* rOctree<T>::InsertItemWithPointRec(const T& item, const point_type& p, node_type* node){
	if (node->m_depth + 1< m_maxDepth){

		box_type volumes[8];
		SubdivideVolume(node->m_volume , volumes);

			for (size_t i =0; i < node->m_children.size(); i++){

				if (volumes[i].ContainsPoint(p)){
					if (!node->m_children[i]){
						node->m_children[i] = new node_type(volumes[i], node->m_depth + 1);
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
rOctreeError rOctree<T>::InsertItemWithBox(const T& item, const box_type& b){
	if (! m_root)
		return rOCTREE_ERROR_NOT_INIT;

	if ( ContainsItem(item))
		return rOCTREE_ERROR_ITEM_ALREADY_IN_TREE;

	if (!m_root->m_volume.ContainsBox(b))
		return rOCTREE_ERROR_ITEM_DOES_NOT_FIT;

	typename rOctree<T>::node_type* target = InsertItemWithBoxRec(item , b , m_root);
	m_items[item] = target;


	return rOCTREE_ERROR_NONE;
}


template <class T>
typename rOctree<T>::node_type* rOctree<T>::InsertItemWithBoxRec(const T& item, const box_type& b, node_type* node){
	if (node->m_depth + 1< m_maxDepth){

		box_type volumes[8];
		SubdivideVolume(node->m_volume , volumes);

		for (size_t i =0; i < node->m_children.size(); i++){

				if (volumes[i].ContainsBox(b)){
					if (!node->m_children[i]){
						node->m_children[i] = new node_type(volumes[i], node->m_depth + 1);
						m_numNodes++;
					}

					return InsertItemWithBoxRec(item , b, node->m_children[i] );
				}
			}

	}

	node->InsertItem(item);
	return node;
}

template <class T>
rOctreeError rOctree<T>::InsertItemWithSphere(const T& item, const sphere_type& s){
	if (! m_root)
		return rOCTREE_ERROR_NOT_INIT;

	if ( ContainsItem(item))
		return rOCTREE_ERROR_ITEM_ALREADY_IN_TREE;

	if (!rIntersection::AlignedBoxContainsSphere(m_root->m_volume , s))
		return rOCTREE_ERROR_ITEM_DOES_NOT_FIT;

	typename rOctree<T>::node_type* target =InsertItemWithSphereRec(item , s , m_root);
	m_items[item] = target;


	return rOCTREE_ERROR_NONE;
}

template <class T>
typename rOctree<T>::node_type* rOctree<T>::InsertItemWithSphereRec(const T& item, const sphere_type& s, node_type* node){
	if (node->m_depth + 1< m_maxDepth){

		box_type volumes[8];
		SubdivideVolume(node->m_volume , volumes);

		for (size_t i =0; i < node->m_children.size(); i++){

				if (rIntersection::AlignedBoxContainsSphere(volumes[i] , s)){
					if (!node->m_children[i]){
						node->m_children[i] = new node_type(volumes[i], node->m_depth + 1);
						m_numNodes++;
					}

					return InsertItemWithSphereRec(item , s, node->m_children[i] );
				}
			}

	}

	node->InsertItem(item);
	return node;
}

template <class T>
void rOctree<T>::QueryItemsWithPoint(const point_type& p , result_type& result){
	result.clear();

	if (! m_root || ! m_root->m_volume.ContainsPoint(p))
		return;

	AddNodeItemsToResultSet( m_root,result);
	QueryItemsWithPointRec(p , result, m_root);
}

template <class T>
void rOctree<T>::QueryItemsWithPointRec(const point_type& p , result_type& result,  node_type* node){
	for (size_t i =0; i < node->m_children.size(); i++){

		if (node->m_children[i] && node->m_children[i]->m_volume.ContainsPoint(p)){
			AddNodeItemsToResultSet(node->m_children[i],result);
			QueryItemsWithPointRec(p , result, node->m_children[i]);
			return;
		}
	}
}

template <class T>
void rOctree<T>::QueryItemsWithBox(const box_type& b , result_type& result){
	result.clear();

	if (! m_root || ! m_root->m_volume.IntersectsBox(b))
		return;

	AddNodeItemsToResultSet( m_root,result);
	QueryItemsWithBoxRec(b , result , m_root);
}

template <class T>
void rOctree<T>::QueryItemsWithBoxRec(const box_type& b , result_type& result,  node_type* node){
	for (size_t i =0; i < node->m_children.size(); i++){

		if (node->m_children[i] && node->m_children[i]->m_volume.IntersectsBox(b)){
			AddNodeItemsToResultSet(node->m_children[i],result);
			QueryItemsWithBoxRec(b , result, node->m_children[i]);
		}
	}
}

template <class T>
void rOctree<T>::QueryItemsWithSphere(const sphere_type& s, result_type& result){
	result.clear();

	if (! m_root || ! rIntersection::AlignedBoxIntersectsSphere(m_root->m_volume , s))
		return;

	AddNodeItemsToResultSet( m_root,result);
	QueryItemsWithSpehereRec(s , result , m_root);
}

template <class T>
void rOctree<T>::QueryItemsWithSpehereRec(const sphere_type& s , result_type& result , node_type* node){
	for (size_t i =0; i < node->m_children.size(); i++){
			if (node->m_children[i] && rIntersection::AlignedBoxIntersectsSphere(node->m_children[i]->m_volume , s)){
				AddNodeItemsToResultSet(node->m_children[i],result);
				QueryItemsWithSpehereRec(s , result , node->m_children[i]);
			}
	}
}

template <class T>
void rOctree<T>::QueryItemsWithRay(const ray_type& r , result_type& result){
	result.clear();

	if (! m_root || !rIntersection::RayIntersectsAlignedBox(r , m_root->m_volume))
		return;

	AddNodeItemsToResultSet( m_root,result);
	QueryItemsWithRayRec(r , result, m_root);
}

template <class T>
void rOctree<T>::QueryItemsWithRayRec(const ray_type& r , result_type& result , node_type* node){
	for (size_t i =0; i < node->m_children.size(); i++){
			if (node->m_children[i] && rIntersection::RayIntersectsAlignedBox(r,node->m_children[i]->m_volume)){
				AddNodeItemsToResultSet(node->m_children[i],result);
				QueryItemsWithRayRec(r , result , node->m_children[i]);
			}
	}
}

template <class T>
rOctreeError rOctree<T>::UpdateItemWithPoint(T& item, const point_type& p){
	if (! m_root)
		return rOCTREE_ERROR_NOT_INIT;

	if ( !ContainsItem(item))
		return rOCTREE_ERROR_ITEM_NOT_FOUND;

	if (!m_root->m_volume.ContainsPoint(p))
		return rOCTREE_ERROR_ITEM_DOES_NOT_FIT;

	m_items[item]->RemoveItem(item);

	typename rOctree<T>::node_type* target = InsertItemWithPointRec(item , p , m_root);
	m_items[item] = target;

	return rOCTREE_ERROR_NONE;
}

template <class T>
rOctreeError rOctree<T>::UpdateItemWithBox(T& item, const box_type& b){
	if (! m_root)
		return rOCTREE_ERROR_NOT_INIT;

	if ( !ContainsItem(item))
		return rOCTREE_ERROR_ITEM_NOT_FOUND;

	if (!m_root->m_volume.ContainsBox(b))
		return rOCTREE_ERROR_ITEM_DOES_NOT_FIT;

	m_items[item]->RemoveItem(item);

	typename rOctree<T>::node_type* target = InsertItemWithBoxRec(item , b , m_root);
	m_items[item] = target;

	return rOCTREE_ERROR_NONE;
}

template <class T>
rOctreeError rOctree<T>::UpdateItemWithSphere(T& item, const sphere_type& s){
	if (! m_root)
		return rOCTREE_ERROR_NOT_INIT;

	if ( !ContainsItem(item))
		return rOCTREE_ERROR_ITEM_NOT_FOUND;

	if (!rIntersection::AlignedBoxContainsSphere(m_root->m_volume , s))
		return rOCTREE_ERROR_ITEM_DOES_NOT_FIT;

	m_items[item]->RemoveItem(item);

	typename rOctree<T>::node_type* target = InsertItemWithSphereRec(item , s , m_root);
	m_items[item] = target;

	return rOCTREE_ERROR_NONE;
}

template <class T>
void rOctree<T>::QueryNodesWithBox(const box_type& b , node_list& result){
	result.clear();

	if (! m_root || ! m_root->m_volume.IntersectsBox(b))
		return;

	result.push_back(m_root);
	QueryNodesWithBoxRec(b , result , m_root);
}

template <class T>
void rOctree<T>::QueryNodesWithBoxRec(const box_type& b , node_list& result,  node_type* node){
		for (size_t i =0; i < node->m_children.size(); i++){

			if (node->m_children[i] && node->m_children[i]->m_volume.IntersectsBox(b)){
				result.push_back(node->m_children[i]);
				QueryNodesWithBoxRec(b , result, node->m_children[i]);
			}
		}
}

#endif