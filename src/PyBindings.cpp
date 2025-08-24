#include <pybind11/pybind11.h>
#include <pybind11/stl.h>       // For std::optional support (pybind11 will map it to Python's None)
#include <pybind11/operators.h> // Useful for operator overloading, though not strictly needed here

#include <ta-lib/ADX.hpp>
#include <ta-lib/ATR.hpp>
#include <ta-lib/ChaikinMoneyFlow.hpp>
#include <ta-lib/Correlation.hpp>
#include <ta-lib/Covariance.hpp>
#include <ta-lib/Diff.hpp>
#include <ta-lib/EMA.hpp>
#include <ta-lib/MACD.hpp>
#include <ta-lib/Median.hpp>
#include <ta-lib/PctChange.hpp>
#include <ta-lib/Quantile.hpp>
#include <ta-lib/RSI.hpp>
#include <ta-lib/Shift.hpp>
#include <ta-lib/SMA.hpp>
#include <ta-lib/StdDev.hpp>
#include <ta-lib/Variance.hpp>
#include <ta-lib/Zscore.hpp>

namespace py = pybind11;

PYBIND11_MODULE(mw_ta_lib, m) {
    m.doc() = "technical analysis library.";

    py::class_<talib::ADX::Value>(m, "ADXValue")
        .def(py::init<>())
        .def_readwrite("adx", &talib::ADX::Value::adx)
        .def_readwrite("pdi", &talib::ADX::Value::pdi)
        .def_readwrite("mdi", &talib::ADX::Value::mdi);
    py::class_<talib::ADX>(m, "ADX")
        .def(py::init<uint32_t>(), py::arg("period") = 14)
        .def("next_val", &talib::ADX::nextVal, py::arg("close"), py::arg("low"), py::arg("high"));

    py::class_<talib::ATR>(m, "ATR")
        .def(py::init<uint32_t>(), py::arg("period") = 14)
        .def("next_val", &talib::ATR::nextVal, py::arg("close"), py::arg("low"), py::arg("high"));

    py::class_<talib::ChaikinMoneyFlow>(m, "ChaikinMoneyFlow")
        .def(py::init<uint32_t>(), py::arg("period") = 14)
        .def("next_val", &talib::ChaikinMoneyFlow::nextVal, py::arg("high"), py::arg("low"), py::arg("close"), py::arg("volume"));

    py::class_<talib::Correlation>(m, "Correlation")
        .def(py::init<uint32_t>(), py::arg("period"))
        .def("next_val", &talib::Correlation::nextVal, py::arg("x"), py::arg("y"));

    py::class_<talib::Covariance>(m, "Covariance")
        .def(py::init<uint32_t>(), py::arg("period"))
        .def("next_val", &talib::Covariance::nextVal, py::arg("x"), py::arg("y"));

    py::class_<talib::Diff>(m, "Diff")
        .def(py::init<uint32_t>(), py::arg("period") = 1)
        .def("next_val", &talib::Diff::nextVal, py::arg("value"));

    py::class_<talib::EMA>(m, "EMA")
        .def(py::init<uint32_t>(), py::arg("period"))
        .def("next_val", &talib::EMA::nextVal, py::arg("value"));

    py::class_<talib::MACD::Value>(m, "MACDValue")
        .def(py::init<>())
        .def_readwrite("macd", &talib::MACD::Value::macd)
        .def_readwrite("signal", &talib::MACD::Value::signal);
    py::class_<talib::MACD>(m, "MACD")
        .def(py::init<uint32_t, uint32_t, uint32_t>(), py::arg("short") = 12, py::arg("long") = 26, py::arg("signal") = 9)
        .def("next_val", &talib::MACD::nextVal, py::arg("value"));

    py::class_<talib::Median>(m, "Median")
        .def(py::init<uint32_t>(), py::arg("period"))
        .def("next_val", &talib::Median::nextVal, py::arg("value"));

    py::class_<talib::PctChange>(m, "PctChange")
        .def(py::init<uint32_t>(), py::arg("period") = 1)
        .def("next_val", &talib::PctChange::nextVal, py::arg("value"));

    py::class_<talib::RSI>(m, "RSI")
        .def(py::init<uint32_t>(), py::arg("period") = 14)
        .def("next_val", &talib::RSI::nextVal, py::arg("value"));

    py::class_<talib::Shift>(m, "Shift")
        .def(py::init<uint32_t>(), py::arg("period") = 1)
        .def("next_val", &talib::Shift::nextVal, py::arg("value"));

    py::class_<talib::StdDev>(m, "StdDev")
        .def(py::init<uint32_t>(), py::arg("period"))
        .def("next_val", &talib::StdDev::nextVal, py::arg("value"));

    py::class_<talib::SMA>(m, "SMA")
        .def(py::init<uint32_t>(), py::arg("period"))
        .def("next_val", &talib::SMA::nextVal, py::arg("value"));

    py::class_<talib::Variance>(m, "Variance")
        .def(py::init<uint32_t>(), py::arg("period"))
        .def("next_val", &talib::Variance::nextVal, py::arg("value"));

    py::class_<talib::Zscore>(m, "Zscore")
        .def(py::init<uint32_t>(), py::arg("period"))
        .def("next_val", &talib::Zscore::nextVal, py::arg("value"));

}
