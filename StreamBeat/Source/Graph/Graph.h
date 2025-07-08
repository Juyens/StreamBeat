#pragma once

#include "List.h"
#include "HashTable.h"

#include <memory>
#include <functional>

template <class T, class A = int>
class Graph
{
private:
    struct Edge;

    struct Vertex
    {
        T data;
        List<std::shared_ptr<Edge>> adjacency;

        explicit Vertex(const T& data)
            : data(data) {}
    };

    struct Edge
    {
        std::weak_ptr<Vertex> to;
        A weight;

        Edge(std::shared_ptr<Vertex> destination, const A& weight = A{})
            : to(destination), weight(weight) {}
    };

    List<std::shared_ptr<Vertex>> vertices_;
    HashTable<T, std::shared_ptr<Vertex>> index_;

public:
    Graph() = default;

    bool addVertex(const T& data)
    {
        if (index_.find(data))
            return false;

        auto vertex = std::make_shared<Vertex>(data);
        vertices_.push_back(vertex);
        index_.insert(data, vertex);
        return true;
    }

    bool addEdge(const T& from, const T& to, const A& weight = A{})
    {
        auto* fromPtr = index_.find(from);
        auto* toPtr = index_.find(to);

        if (!fromPtr || !toPtr)
            return false;

        fromPtr->get()->adjacency.push_back(std::make_shared<Edge>(*toPtr, weight));
        return true;
    }

    const List<std::shared_ptr<Vertex>>& getVertices() const
    {
        return vertices_;
    }

    List<T> getAdjacency(const T& from) const
    {
        List<T> result;
        auto* fromPtr = index_.find(from);

        if (!fromPtr)
            return result;

        for (const auto& edge : fromPtr->get()->adjacency)
        {
            if (auto toVertex = edge->to.lock())
                result.push_back(toVertex->data);
        }

        return result;
    }

    void forEachVertex(const std::function<void(const T&)>& visit) const
    {
        for (uint i = 0; i < vertices_.size(); ++i)
            visit(vertices_[i]->data);
    }

    void forEachEdge(const T& from, const std::function<void(const T&, const A&)>& visit) const
    {
        auto* fromPtr = index_.find(from);

        if (!fromPtr)
            return;

        for (uint i = 0; i < fromPtr->get()->adjacency.size(); ++i)
        {
            auto& edge = fromPtr->get()->adjacency[i];
            if (auto toVertex = edge->to.lock())
                visit(toVertex->data, edge->weight);
        }
    }
};