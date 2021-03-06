#include "math.hpp"
#include "eigen.hpp"
#include  "class.hpp"

#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(python_example, m) {
    m.doc() = "Python example bindings";
    m.def("add", &add, "A function which adds two numbers", 
            py::arg("i"), py::arg("j"));
    m.def("subtract", &subtract);
    m.def("scale_vector_inplace", &scale_vector_inplace);
    m.def("scale_vector_return", &scale_vector_return);
    m.def("square", &square<int>);
    m.def("square", &square<double>);
    m.def("square", &square<float>);

    // expose a class to Python
    py::class_<Pet>(m, "Pet") 
        .def(py::init<const std::string &, int>())
        .def("setName", &Pet::setName, py::arg("name"))
        .def("getName", &Pet::getName)
        .def("set", (void (Pet::*)(int)) &Pet::set, "set the pet's age")
        .def("set", (void (Pet::*)(const std::string &)) &Pet::set, "Set pet's name")
        .def("__repr__", [](const Pet &a) { return "<python_example.Pet named '" + a.name + "'>"; })
        .def_readwrite("name", &Pet::name);

    // expose a derived class to python
    py::class_<Dog, Pet>(m, "Dog")
        .def(py::init<const std::string &>())
        .def("bark", &Dog::bark);
}
