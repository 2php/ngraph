//*****************************************************************************
// Copyright 2017-2020 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "ngraph/op/fused/fake_quantize.hpp"
#include "pyngraph/ops/fused/fake_quantize.hpp"

namespace py = pybind11;

void regclass_pyngraph_op_FakeQuantize(py::module m)
{
    py::class_<ngraph::op::FakeQuantize, std::shared_ptr<ngraph::op::FakeQuantize>, ngraph::op::Op>
        fakequantize(m, "FakeQuantize");
    fakequantize.doc() = "ngraph.impl.op.FakeQuantize wraps ngraph::op::FakeQuantize";
    fakequantize.def(py::init<const std::shared_ptr<ngraph::Node>&,
                              const std::shared_ptr<ngraph::Node>&,
                              const std::shared_ptr<ngraph::Node>&,
                              const std::shared_ptr<ngraph::Node>&,
                              const std::shared_ptr<ngraph::Node>&,
                              std::size_t>());
}
