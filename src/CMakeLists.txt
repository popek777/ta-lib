set(ta_lib_sources
  ADX.cpp
  ATR.cpp
  ChaikinMoneyFlow.cpp
  Correlation.cpp
  Covariance.cpp
  Diff.cpp
  EMA.cpp
  MACD.cpp
  Median.cpp
  PctChange.cpp
  Quantile.cpp
  RSI.cpp
  Shift.cpp
  SMA.cpp
  StdDev.cpp
  Variance.cpp
  Zscore.cpp

  RangeCache.cpp
  SortedWindow.cpp
  TaLibUtils.cpp
  )

add_library(ta-lib SHARED
  ${ta_lib_sources}
  )

#
# prerequisits:
# pip install pybind11
# Or, if using conda:
# conda install -c conda-forge pybind11
#
find_package(Python COMPONENTS Interpreter Development)
set(pybind11_DIR ${Python_SITELIB}/pybind11/share/cmake/pybind11)
message(info " pybind11 dir: ${pybind11_DIR}")
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(mw_ta_lib
  ${ta_lib_sources}
  PyBindings.cpp
  )

add_executable(test
  ${ta_lib_sources}
  test.cpp
  )

set_target_properties(ta-lib mw_ta_lib test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
