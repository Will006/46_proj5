// Digraph.hpp
//
// ICS 46 Winter 2019
// Project #4: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph. The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <utility>


// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    //*DigraphVertex copyVertex(int vertex);
    
    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.

    std::map<int,DigraphVertex<VertexInfo, EdgeInfo>*> mainMap;
    unsigned int vertexNum =0;
    unsigned int edgeNum =0;
    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
};



// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
    //do nothing
}
/*
template<typename vertexInfo, typename EdgeInfo>
*DigraphVetex Digraph<VertexInfo, EdgeInfo>::copyVertex(int vertexIn)
{
    *DigraphVertex<VertexInfo, EdgeInfo> tempVertex = new DigraphVertex<VertexInfo, EdgeInfo>;
    temp
    return 
*/
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{
    
    for(auto it = d.mainMap.begin(); it!= d.mainMap.end(); ++it)
    {
        
        addVertex(it->first, it->second->vinfo);
        mainMap.at(it->first)->edges = it->second->edges;
    }
    edgeNum = d.edgeNum;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
{
    //std::move grabs all all the pointer values and updates the mainMap ptrs to point to
    //to the dynamic values of d
    //to prevent d from deleting all those values set all values to nullptr
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>*> emptyMap;
    mainMap = std::move(d.mainMap);
    d.mainMap = emptyMap;
    vertexNum = d.vertexNum;
    edgeNum = d.edgeNum;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
    for(auto it=mainMap.begin();it!=mainMap.end();it++)
    {
        delete it->second;
    }
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    Digraph{d};
    //Digraph(d);<-doesnt work
return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    Digraph{d};
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    std::vector<int> vertexVector = {};
    //itterate through to get the key values and push them into a vertex
    for(auto it = mainMap.begin();it!=mainMap.end(); ++it)
    {
        vertexVector.push_back(it->first);
    }
    return vertexVector;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int, int>> tempVect ={};

    for(auto it = mainMap.begin();
        it!=mainMap.end(); ++it)
    {
        //grab all the edges from the current vector
        std::vector<std::pair<int,int>> currentVector = 
        edges(it->first);
        
        //add the edges to the main vector of edges
        tempVect.insert(tempVect.end(), currentVector.begin(), currentVector.end());
    }
    return tempVect;
}

//MAY NEED TO CHECK FOR DELETED VERTEXS
template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    auto it = mainMap.find(vertex);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }
    std::vector<std::pair<int, int>> tempVect={};
    for(typename std::list<DigraphEdge<EdgeInfo>>::iterator it=mainMap.at(vertex)->edges.begin();
        it!=mainMap.at(vertex)->edges.end();++it)
    {
       tempVect.push_back(std::pair<int,int>{it->fromVertex,it->toVertex}); 
    }
    return tempVect;
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    auto it = mainMap.find(vertex);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }

    return mainMap.at(vertex)->vinfo;
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    auto it = mainMap.find(fromVertex);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }
    it = mainMap.find(toVertex);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }

    for(typename std::list<DigraphEdge<EdgeInfo>>::iterator it=mainMap.at(fromVertex)->edges.begin();
        it!=mainMap.at(fromVertex)->edges.end();++it)
    {
        if(it->fromVertex == fromVertex && it->toVertex== toVertex)
        {
            return it->einfo;
            
        }
    }
    throw DigraphException("Invalid Edge");
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertexIn, const VertexInfo& vinfoIn)
{
    mainMap.insert(std::pair(vertexIn, new DigraphVertex<VertexInfo, EdgeInfo>{.vinfo = vinfoIn}));
    vertexNum++;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertexIn, int toVertexIn, const EdgeInfo& einfoIn)
{
    auto it = mainMap.find(fromVertexIn);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }
    it = mainMap.find(toVertexIn);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }
    
   
    DigraphEdge<EdgeInfo> newEdge{.fromVertex = 
            fromVertexIn, .toVertex = toVertexIn, .einfo = einfoIn};
    mainMap.at(fromVertexIn)->edges.push_front(newEdge);
    edgeNum++;

}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    delete mainMap.at(vertex);
    for(auto currentVertex = mainMap.begin(); currentVertex!=mainMap.end(); ++currentVertex)
    {
        if(!currentVertex->second->edges.empty())
        {
            for(typename std::list<DigraphEdge<EdgeInfo>>::iterator currentEdge=currentVertex->second->edges.begin();
            currentEdge!=currentVertex->second->edges.end(); ++currentEdge)
            {
                if(currentEdge->toVertex == vertex)
                {
                    currentEdge = currentVertex->second->edges.erase(currentEdge);
                    --currentEdge;//go back one so no edge is skipped
                    edgeNum--;
                }
            }
        }

   }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    auto it = mainMap.find(fromVertex);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }
    it = mainMap.find(toVertex);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }
    
    for(typename std::list<DigraphEdge<EdgeInfo>>::iterator it=mainMap.at(fromVertex)->edges.begin(); 
    it!=mainMap.at(fromVertex)->edges.end();++it)
    {
        if(it->fromVertex == fromVertex && it->toVertex== toVertex)
        {
            mainMap.at(fromVertex)->edges.erase(it);
            edgeNum--;
            break;
        }
    }
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    return vertexNum;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    return edgeNum;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    auto it = mainMap.find(vertex);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }

    return mainMap.at(vertex)->edges.size();
}
/*
template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::breathSearch(int vertex, std::queue<int> reachable, std::queue<int> vistedIn) const
{
    for(typename std::list<DiggbraphEdge<EdgeInfo>>::iterator it=mainMap.at(fromVertex)->edges.begin(); 
    {
        reachable.push(it->toVertex);
    }
    vistedIn.push(vertex);
    breathSearch(reachable.pop(),reachable,vistedIn);
    
}
*/
template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    if(vertexNum==0 || vertexNum==1)
    {
        return true;
    }
    std::list<int> visted={};
    std::list<int> reachable ={};
    
    auto it = mainMap.begin();
    reachable.push_back(it->first);
    int currentVertex =0;
    int nextVertex=0;
    while(reachable.empty()==false)
    {
        currentVertex = reachable.front();
        reachable.pop_front();
        //add all adjacent vertex to reachable
        for(typename std::list<DigraphEdge<EdgeInfo>>::iterator currentEdge=
            mainMap.at(currentVertex)->edges.begin();
            currentEdge!=mainMap.at(currentVertex)->edges.end(); ++currentEdge)
        {
            nextVertex = currentEdge->toVertex;
            bool found =false;
            //check if it's been visted
            for(std::list<int>::iterator vistedIt = visted.begin(); vistedIt!=visted.end(); ++vistedIt)
            {
                if(*vistedIt==nextVertex)
                {
                    found=true;
                }
            }
            if(found==false)
            {
                //check if it's been seen
                for(std::list<int>::iterator reachIt = reachable.begin(); reachIt!=reachable.end(); ++reachIt)
                {
                    if(*reachIt==nextVertex)
                    {
                        found=true;
                    }
                }
                //if it has not been seen add it to reachable
                if(found==false)
                {
                    reachable.push_back(currentEdge->toVertex);
                }
            }
        }
        visted.push_back(nextVertex);
    }
    //if all vertexs were reachable
    if(visted.size()==vertexNum)
    {
        return true;
    }

    return false;
}


template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    auto it = mainMap.find(startVertex);
    if(it==mainMap.end())
    {
        throw DigraphException("Invalid Vertex");
    }
    return std::map<int, int>{};
}



#endif // DIGRAPH_HPP

