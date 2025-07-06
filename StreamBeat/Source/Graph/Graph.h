#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

template <class T, class A = int>
class Graph
{
private:
    struct Edge;

    struct Vertex
    {
        T data;
        std::vector<std::shared_ptr<Edge>> adjacency;

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

    std::vector<std::shared_ptr<Vertex>> vertices_;
    std::unordered_map<T, std::shared_ptr<Vertex>> index_;

public:
    Graph() = default;

    bool addVertex(const T& data)
    {
        if (index_.count(data)) return false;
        auto vertex = std::make_shared<Vertex>(data);
        vertices_.push_back(vertex);
        index_[data] = vertex;
        return true;
    }

    bool addEdge(const T& from, const T& to, const A& weight = A{})
    {
        auto itFrom = index_.find(from);
        auto itTo = index_.find(to);
        if (itFrom == index_.end() || itTo == index_.end()) return false;

        itFrom->second->adjacency.push_back(std::make_shared<Edge>(itTo->second, weight));
        return true;
    }

    const std::vector<std::shared_ptr<Vertex>>& getVertices() const
    {
        return vertices_;
    }

    std::vector<T> getAdjacency(const T& from) const
    {
        std::vector<T> result;
        auto it = index_.find(from);
        if (it == index_.end()) return result;

        for (const auto& edge : it->second->adjacency)
        {
            if (auto ptr = edge->to.lock())
                result.push_back(ptr->data);
        }
        return result;
    }

    void forEachVertex(const std::function<void(const T&)>& visit) const
    {
        for (const auto& vertex : vertices_)
        {
            visit(vertex->data);
        }
    }

    void forEachEdge(const T& from, const std::function<void(const T&, const A&)>& visit) const
    {
        auto it = index_.find(from);
        if (it == index_.end()) return;

        for (const auto& edge : it->second->adjacency)
        {
            if (auto ptr = edge->to.lock())
                visit(ptr->data, edge->weight);
        }
    }
};