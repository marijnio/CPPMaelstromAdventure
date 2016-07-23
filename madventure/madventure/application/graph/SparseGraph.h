#pragma once

// Description : Graph class using the adjacency list representation.
// Author : Mat Buckland

#include <vector>
#include <list>
#include <cassert>
#include <string>
#include <iostream>

#include "../utility/vector2D.h"
#include "../utility/mathoperations.h"
#include "NodeTypeEnumerations.h"

template <class node_type, class edge_type>
class SparseGraph {
public:

  // Typedefs for easy access
  typedef edge_type EdgeType;
  typedef node_type NodeType;
  
  typedef std::vector<node_type> NodeVector;
  typedef std::list<edge_type>   EdgeList;
  typedef std::vector<EdgeList>  EdgeListVector;

private:
  NodeVector nodes_;

  // A vector of adjacency edge lists.
  // Each node index keys into the list of edges associated with that node.
  EdgeListVector edges_;
 
  // A flag denoting whether the graph is directed or not.
  bool digraph_;

  // Index of next node to be added.
  int next_node_index_;
    
  // Returns true if an edge is not already present in the graph.
  // Used when adding edges to make sure no duplicates are created.
  bool UniqueEdge(int from, int to) const;

  // Iterates through all edges in the graph and removes any that point to
  // an invalidated node.
  void CullInvalidEdges();
  
public:
  
  SparseGraph(bool digraph) : next_node_index_(0), digraph_(digraph) {}

  // Return the node at given index.
  const NodeType& GetNode(int idx) const;
  // Non-const version.
  NodeType&  GetNode(int idx);

  // Returns the reference to an edge.
  const EdgeType& GetEdge(int from, int to) const;
  // Non-const version.
  EdgeType& GetEdge(int from, int to);

  // Retrieves the next free node index.
  int GetNextFreeNodeIndex() const { return next_node_index_; }
  
  // Adds a node to the graph and returns its index.
  int AddNode(node_type node);

  // Removes a node by setting its index to the invalid node index.
  void RemoveNode(int node);

  // Adds an edge to the graph.
  // Ensures that the edge passed as a parameter is valid before adding it.
  // If the graph is a digraph, then a similar edge connecting the nodes in the
  // opposite direction will be automatically added.
  void AddEdge(EdgeType edge);

  // Removes the edge connecting from and to from the graph (if present).
  // If a digraph then the edge connecting the nodes in the opposite direction 
  // will also be removed.
  void RemoveEdge(int from, int to);

  // Sets the cost of an edge
  void SetEdgeCost(int from, int to, double cost);

  // Returns the number of active and inactive nodes present in the graph.
  int NumNodes() const { return nodes_.size(); }
  
  // Returns the number of active nodes present in the graph
  // This method's performance could be improved greatly by caching the value.
  int NumActiveNodes() const {
    int count = 0;
    for (unsigned int n = 0; n < nodes_.size(); ++n) {
      if (nodes_[n].Index() != invalid_node_index) ++count;
    }
    return count;
  }

  // Returns the total number of edges present in the graph.
  int NumEdges() const {
    int tot = 0;
    for (EdgeListVector::const_iterator current_edge = edges_.begin();
         current_edge != edges_.end();
         ++current_edge) {
      tot += current_edge->size();
    }
    return tot;
  }

  // Returns true if the graph is directed.
  bool isDigraph() const { return digraph_; }

  // Returns true if the graph contains no nodes.
  bool isEmpty() const { return nodes_.empty(); }

  // Returns true if a node with the given index is present in the graph.
  bool isNodePresent(int nd) const;

  // Returns true if an edge connecting the nodes 'to' and 'from' is present.
  bool isEdgePresent(int from, int to) const;

  // Methods for loading and saving graphs from an open file stream or file.
  bool Save(const char* FileName) const;
  bool Save(std::ofstream& stream) const;

  bool Load(const char* FileName);
  bool Load(std::ifstream& stream);

  // Clears the graph ready for new node insertions.
  void Clear() {
    next_node_index_ = 0;
    nodes_.clear();
    edges_.clear();
  }

  void RemoveEdges() {
    for (EdgeListVector::iterator it = edges_.begin(); it != edges_.end();
         ++it) {
      it->clear();
    }
  }
  // Non-const class used to iterate through all the edges connected to
  // a specific node.
  class EdgeIterator {
  public:
    EdgeIterator(SparseGraph<node_type, edge_type>& graph, int node)
        : my_graph(graph), node_index(node) {
      // We don't need to check for an invalid node index because if the node
      // is invalid there will be no associated edges.
      current_edge = my_graph.edges_[node_index].begin();
    }

    EdgeType* begin() {
      current_edge = my_graph.edges_[node_index].begin();
      return &(*current_edge);
    }

    EdgeType* next() {
      ++current_edge;
      return &(*current_edge);
    }

    // Return true if we are at the end of the edge list.
    bool end() {
      return (current_edge == my_graph.edges_[node_index].end());
    }

  private:
    typename EdgeList::iterator current_edge;
    SparseGraph<node_type, edge_type>& my_graph;
    const int node_index;

  };

  friend class EdgeIterator;

  // Const class used to iterate through all the edges connected to
  // a specific node. 
  class ConstEdgeIterator {
  public:

    ConstEdgeIterator(const SparseGraph<node_type, edge_type>& graph,
                      int node)
        : my_graph(graph), node_index(node) {

      // We don't need to check for an invalid node index because if the node
      // is invalid there will be no associated edges.
      current_edge = my_graph.edges_[node_index].begin();
    }

    const EdgeType* begin() {        
      current_edge = my_graph.edges_[node_index].begin();
      return &(*current_edge);
    }

    const EdgeType* next() {
      ++current_edge;
      return &(*current_edge);
    }

    // Return true if we are at the end of the edge list.
    bool end() {
      return (current_edge == my_graph.edges_[node_index].end());
    }
  private:
    typename EdgeList::const_iterator current_edge;
    const SparseGraph<node_type, edge_type>& my_graph;
    const int node_index;
  };

  friend class ConstEdgeIterator;

  // Non-const class used to iterate through the nodes in the graph.
  class NodeIterator {
  public:
    NodeIterator(SparseGraph<node_type, edge_type> &graph) : my_graph(graph) {
      current_node = my_graph.nodes_.begin();
    }

    node_type* begin() {
      current_node = my_graph.nodes_.begin();
      GetNextValidNode(current_node);
      return &(*current_node);
    }

    node_type* next() {
      ++current_node;
      GetNextValidNode(current_node);
      return &(*current_node);
    }

    bool end() {
      return (current_node == my_graph.nodes_.end());
    }

  private:
    typename NodeVector::iterator current_node;
    SparseGraph<node_type, edge_type>& my_graph;

    // If a graph node is removed, it is not removed from the vector of nodes
    // (because that would mean changing all the indices of all the nodes that
    // have a higher index).
    //
    // This method takes a node iterator as a parameter and assigns
    // the next valid element to it.
    void GetNextValidNode(typename NodeVector::iterator& it) {
      if (current_node == my_graph.nodes_.end()
        || it->Index() != invalid_node_index) {
        return;
      }

      while (it->Index() == invalid_node_index) {
        ++it;
        if (current_node == my_graph.nodes_.end()) break;
      }
    }
  };
     
  friend class NodeIterator;

  // Const class used to iterate through the nodes in the graph.
  class ConstNodeIterator {
  public:
    ConstNodeIterator(const SparseGraph<node_type, edge_type> &graph)
        : my_graph(graph) {
      current_node = my_graph.nodes_.begin();
    }

    const node_type* begin() {
      current_node = my_graph.nodes_.begin();
      GetNextValidNode(current_node);
      return &(*current_node);
    }

    const node_type* next() {
      ++current_node;
      GetNextValidNode(current_node);
      return &(*current_node);
    }

    bool end() {
      return (current_node == my_graph.nodes_.end());
    }

  private:
    typename NodeVector::const_iterator current_node;
    const SparseGraph<node_type, edge_type>& my_graph;

    // If a graph node is removed, it is not removed from the vector of nodes
    // (because that would mean changing all the indices of all the nodes that
    // have a higher index).
    //
    // This method takes a node iterator as a parameter and assigns
    // the next valid element to it.
    void GetNextValidNode(typename NodeVector::const_iterator& it) {
      if (current_node == my_graph.nodes_.end()
          || it->Index() != invalid_node_index) return;

      while ((it->Index() == invalid_node_index)) {
        ++it;
        if (current_node == my_graph.nodes_.end()) break;
      }
    }
  };
  friend class ConstNodeIterator;
};

//--------------------------- isNodePresent --------------------------------
//
//  returns true if a node with the given index is present in the graph
//--------------------------------------------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isNodePresent(int nd)const
{
    if ( (nodes_[nd].Index() == invalid_node_index) || (nd >= nodes_.size()))
    {
      return false;
    }
    else return true;
}

//--------------------------- isEdgePresent --------------------------------
//
//  returns true if an edge with the given from/to is present in the graph
//--------------------------------------------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isEdgePresent(int from, int to)const
{
    if (isNodePresent(from) && isNodePresent(from))
    {
       for (EdgeList::const_iterator current_edge = edges_[from].begin();
            current_edge != edges_[from].end();
            ++current_edge)
        {
          if (current_edge->To() == to) return true;
        }

        return false;
    }
    else return false;
}
//------------------------------ GetNode -------------------------------------
//
//  const and non const methods for obtaining a reference to a specific node
//----------------------------------------------------------------------------
template <class node_type, class edge_type>
const node_type&  SparseGraph<node_type, edge_type>::GetNode(int idx)const
{
    assert( (idx < (int)nodes_.size()) &&
            (idx >=0)              &&
           "<SparseGraph::GetNode>: invalid index");

    return nodes_[idx];
}

  //non const version
template <class node_type, class edge_type>
node_type&  SparseGraph<node_type, edge_type>::GetNode(int idx)
{
    assert( (idx < (int)nodes_.size()) &&
            (idx >=0)             &&
          "<SparseGraph::GetNode>: invalid index");
    
    return nodes_[idx];
}

//------------------------------ GetEdge -------------------------------------
//
//  const and non const methods for obtaining a reference to a specific edge
//----------------------------------------------------------------------------
template <class node_type, class edge_type>
const edge_type& SparseGraph<node_type, edge_type>::GetEdge(int from, int to)const
{
  assert( (from < nodes_.size()) &&
          (from >=0)              &&
           nodes_[from].Index() != invalid_node_index &&
          "<SparseGraph::GetEdge>: invalid 'from' index");

  assert( (to < nodes_.size()) &&
          (to >=0)              &&
          nodes_[to].Index() != invalid_node_index &&
          "<SparseGraph::GetEdge>: invalid 'to' index");

  for (EdgeList::const_iterator current_edge = edges_[from].begin();
       current_edge != edges_[from].end();
       ++current_edge)
  {
    if (current_edge->To() == to) return *current_edge;
  }

  assert (0 && "<SparseGraph::GetEdge>: edge does not exist");
}

//non const version
template <class node_type, class edge_type>
edge_type& SparseGraph<node_type, edge_type>::GetEdge(int from, int to)
{
  assert( (from < nodes_.size()) &&
          (from >=0)              &&
           nodes_[from].Index() != invalid_node_index &&
          "<SparseGraph::GetEdge>: invalid 'from' index");

  assert( (to < nodes_.size()) &&
          (to >=0)              &&
          nodes_[to].Index() != invalid_node_index &&
          "<SparseGraph::GetEdge>: invalid 'to' index");

  for (EdgeList::iterator current_edge = edges_[from].begin();
       current_edge != edges_[from].end();
       ++current_edge)
  {
    if (current_edge->To() == to) return *current_edge;
  }

  assert (0 && "<SparseGraph::GetEdge>: edge does not exist");
}

//-------------------------- AddEdge ------------------------------------------
//
//  Use this to add an edge to the graph. The method will ensure that the
//  edge passed as a parameter is valid before adding it to the graph. If the
//  graph is a digraph then a similar edge connecting the nodes in the opposite
//  direction will be automatically added.
//-----------------------------------------------------------------------------
template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::AddEdge(EdgeType edge)
{
  //first make sure the from and to nodes exist within the graph 
  assert( (edge.From() < next_node_index_) && (edge.To() < next_node_index_) &&
          "<SparseGraph::AddEdge>: invalid node index");

  //make sure both nodes are active before adding the edge
  if ( (nodes_[edge.To()].Index() != invalid_node_index) && 
       (nodes_[edge.From()].Index() != invalid_node_index))
  {
    //add the edge, first making sure it is unique
    if (UniqueEdge(edge.From(), edge.To()))
    {
      edges_[edge.From()].push_back(edge);
    }

    //if the graph is undirected we must add another connection in the opposite
    //direction
    if (!digraph_)
    {
      //check to make sure the edge is unique before adding
      if (UniqueEdge(edge.To(), edge.From()))
      {
        EdgeType NewEdge = edge;

        NewEdge.SetTo(edge.From());
        NewEdge.SetFrom(edge.To());

        edges_[edge.To()].push_back(NewEdge);
      }
    }
  }
}


//----------------------------- RemoveEdge ---------------------------------
template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::RemoveEdge(int from, int to)
{
  assert ( (from < (int)nodes_.size()) && (to < (int)nodes_.size()) &&
           "<SparseGraph::RemoveEdge>:invalid node index");

  EdgeList::iterator current_edge;
  
  if (!digraph_)
  {
    for (current_edge = edges_[to].begin();
         current_edge != edges_[to].end();
         ++current_edge)
    {
      if (current_edge->To() == from){current_edge = edges_[to].erase(current_edge);break;}
    }
  }

  for (current_edge = edges_[from].begin();
       current_edge != edges_[from].end();
       ++current_edge)
  {
    if (current_edge->To() == to){current_edge = edges_[from].erase(current_edge);break;}
  }
}

//-------------------------- AddNode -------------------------------------
//
//  Given a node this method first checks to see if the node has been added
//  previously but is now innactive. If it is, it is reactivated.
//
//  If the node has not been added previously, it is checked to make sure its
//  index matches the next node index before being added to the graph
//------------------------------------------------------------------------
template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::AddNode(node_type node)
{
  if (node.Index() < (int)nodes_.size())
  {
    //make sure the client is not trying to add a node with the same ID as
    //a currently active node
    assert (nodes_[node.Index()].Index() == invalid_node_index &&
      "<SparseGraph::AddNode>: Attempting to add a node with a duplicate ID");
    
    nodes_[node.Index()] = node;

    return next_node_index_;
  }
  
  else
  {
    //make sure the new node has been indexed correctly
    assert (node.Index() == next_node_index_ && "<SparseGraph::AddNode>:invalid index");

    nodes_.push_back(node);
    edges_.push_back(EdgeList());

    return next_node_index_++;
  }
}

//----------------------- CullInvalidEdges ------------------------------------
//
//  iterates through all the edges in the graph and removes any that point
//  to an invalidated node
//-----------------------------------------------------------------------------
template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::CullInvalidEdges()
{
  for (EdgeListVector::iterator curEdgeList = edges_.begin(); curEdgeList != edges_.end(); ++curEdgeList)
  {
    for (EdgeList::iterator current_edge = (*curEdgeList).begin(); current_edge != (*curEdgeList).end(); ++current_edge)
    {
      if (nodes_[current_edge->To()].Index() == invalid_node_index || 
          nodes_[current_edge->From()].Index() == invalid_node_index)
      {
        current_edge = (*curEdgeList).erase(current_edge);
      }
    }
  }
}

  
//------------------------------- RemoveNode -----------------------------
//
//  Removes a node from the graph and removes any links to neighbouring
//  nodes
//------------------------------------------------------------------------
template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::RemoveNode(int node)                                   
{
  assert(node < (int)nodes_.size() && "<SparseGraph::RemoveNode>: invalid node index");

  //set this node's index to invalid_node_index
  nodes_[node].SetIndex(invalid_node_index);

  //if the graph is not directed remove all edges leading to this node and then
  //clear the edges leading from the node
  if (!digraph_)
  {    
    //visit each neighbour and erase any edges leading to this node
    for (EdgeList::iterator current_edge = edges_[node].begin(); 
         current_edge != edges_[node].end();
         ++current_edge)
    {
      for (EdgeList::iterator curE = edges_[current_edge->To()].begin();
           curE != edges_[current_edge->To()].end();
           ++curE)
      {
         if (curE->To() == node)
         {
           curE = edges_[current_edge->To()].erase(curE);

           break;
         }
      }
    }

    //finally, clear this node's edges
    edges_[node].clear();
  }

  //if a digraph remove the edges the slow way
  else
  {
    CullInvalidEdges();
  }
}

//-------------------------- SetEdgeCost ---------------------------------
//
//  Sets the cost of a specific edge
//------------------------------------------------------------------------
template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::SetEdgeCost(int from, int to, double NewCost)
{
  //make sure the nodes given are valid
  assert( (from < nodes_.size()) && (to < nodes_.size()) &&
        "<SparseGraph::SetEdgeCost>: invalid index");

  //visit each neighbour and erase any edges leading to this node
  for (EdgeList::iterator current_edge = edges_[from].begin(); 
       current_edge != edges_[from].end();
       ++current_edge)
  {
    if (current_edge->To() == to)
    {
      current_edge->SetCost(NewCost);
      break;
    }
  }
}

  //-------------------------------- UniqueEdge ----------------------------
//
//  returns true if the edge is not present in the graph. Used when adding
//  edges to prevent duplication
//------------------------------------------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::UniqueEdge(int from, int to)const
{
  for (EdgeList::const_iterator current_edge = edges_[from].begin();
       current_edge != edges_[from].end();
       ++current_edge)
  {
    if (current_edge->To() == to)
    {
      return false;
    }
  }

  return true;
}

//-------------------------------- Save ---------------------------------------

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::Save(const char* FileName)const
{
  //open the file and make sure it's valid
  std::ofstream out(FileName);

  if (!out)
  {
    throw std::runtime_error("Cannot open file: " + std::string(FileName));
    return false;
  }

  return Save(out);
}

//-------------------------------- Save ---------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::Save(std::ofstream& stream)const
{
  //save the number of nodes
  stream << nodes_.size() << std::endl;

  //iterate through the graph nodes and save them
  NodeVector::const_iterator current_node = nodes_.begin();
  for (current_node; current_node!=nodes_.end(); ++current_node)
  {
    stream << *current_node;
  }

  //save the number of edges
  stream << NumEdges() << std::endl;


  //iterate through the edges and save them
  for (int nodeIdx = 0; nodeIdx < nodes_.size(); ++nodeIdx)
  {
    for (EdgeList::const_iterator current_edge = edges_[nodeIdx].begin();
         current_edge!=edges_[nodeIdx].end(); ++current_edge)
    {
      stream << *current_edge;
    }  
  }

  return true;
}

//------------------------------- Load ----------------------------------------
//-----------------------------------------------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::Load(const char* FileName)
{
  //open file and make sure it's valid
  std::ifstream in(FileName);

  if (!in)
  {
    throw std::runtime_error("Cannot open file: " + std::string(FileName));
    return false;
  }

  return Load(in);
}

//------------------------------- Load ----------------------------------------
//-----------------------------------------------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::Load(std::ifstream& stream)
{
  Clear();

  //get the number of nodes and read them in
  int NumNodes, NumEdges;

  stream >> NumNodes;

  for (int n=0; n<NumNodes; ++n)
  {
    NodeType NewNode(stream);
  
    //when editing graphs it's possible to end up with a situation where some
    //of the nodes have been invalidated (their id's set to invalid_node_index). Therefore
    //when a node of index invalid_node_index is encountered, it must still be added.
    if (NewNode.Index() != invalid_node_index)
    {
      AddNode(NewNode);
    }
    else
    {
      nodes_.push_back(NewNode);

      //make sure an edgelist is added for each node
      edges_.push_back(EdgeList());
      
      ++next_node_index_;
    }
  }

  //now add the edges
  stream >> NumEdges;
  for (int e=0; e<NumEdges; ++e)
  {
    EdgeType NextEdge(stream);

    edges_[NextEdge.From()].push_back(NextEdge);
  }

  return true;
}