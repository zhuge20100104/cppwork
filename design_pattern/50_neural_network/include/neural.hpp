#ifndef _FREDRIC_NEURAL_HPP_
#define _FREDRIC_NEURAL_HPP_
#include <vector>

template <typename Self>
struct SomeNeurons {
    // From类型和to类型必须支持range-based for loop
    template <typename T>
    void connect_to(T& other) {
        for(auto& from: *static_cast<Self*>(this)) {
            for(auto& to: other) {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

struct Neuron: SomeNeurons<Neuron> {
    std::vector<Neuron*> in, out;
    unsigned int id;

    Neuron() {
        static int g_id = 1;
        this->id = g_id++;
    }
    
    Neuron* begin() {
        return this;
    }

    Neuron* end() {
        return this + 1;
    }

    friend std::ostream& operator<<(std::ostream& os, Neuron const& obj) {
        for(Neuron* n: obj.in) {
            os << n->id << "\t--> \t[" << obj.id << "]\n";
        }

        for(Neuron* n: obj.out) {
            os << obj.id << "\t--> \t[" << n->id << "]\n";
        }
        return os;
    }
};

struct NeuronLayer: SomeNeurons<NeuronLayer> {
    std::vector<Neuron> neurons;

    NeuronLayer(int count) {
        while (count-- > 0)
            neurons.emplace_back(Neuron{});
    }

    friend std::ostream& operator<<(std::ostream& os, NeuronLayer const& obj) {
        for(auto& n: obj) os << n;
        return os;
    }

    std::vector<Neuron>::const_iterator begin() const { return neurons.begin(); }
    std::vector<Neuron>::const_iterator end() const { return neurons.end(); }

    std::vector<Neuron>::iterator begin() { return neurons.begin(); }
    std::vector<Neuron>::iterator end() { return neurons.end(); }
};
#endif