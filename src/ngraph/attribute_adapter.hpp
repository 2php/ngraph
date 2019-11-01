//*****************************************************************************
// Copyright 2017-2019 Intel Corporation
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

#pragma once

#include "ngraph/enum_names.hpp"
#include "ngraph/type.hpp"

namespace ngraph
{
    template <typename T>
    class ValueAdapter
    {
    public:
        virtual ~ValueAdapter() {}
        virtual const DiscreteTypeInfo& get_type_info() const = 0;
        /// Returns the value
        virtual const T& get() = 0;
        /// Sets the value
        virtual void set(const T& value) = 0;

    protected:
        T m_buffer;
        bool m_buffer_valid{false};
    };

    template <>
    class ValueAdapter<void>
    {
    public:
        virtual const DiscreteTypeInfo& get_type_info() const = 0;
    };

    template <typename Type>
    class TypeAdapter
    {
    public:
        operator Type&() const { return m_value; }
    protected:
        TypeAdapter(Type& value)
            : m_value(value)
        {
        }
        Type& m_value;
    };

    template <typename Type>
    class EnumAdapter : public TypeAdapter<Type>, public ValueAdapter<std::string>
    {
    public:
        EnumAdapter(Type& value)
            : TypeAdapter<Type>(value)
        {
        }
        static const DiscreteTypeInfo type_info;
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::string& get() override { return as_string(TypeAdapter<Type>::m_value); }
        void set(const std::string& value) override
        {
            TypeAdapter<Type>::m_value = as_enum<Type>(value);
        }
    };

    template <typename Type>
    class ObjectAdapter : public TypeAdapter<Type>, public ValueAdapter<void>
    {
    public:
        ObjectAdapter(Type& value)
            : TypeAdapter<Type>(value)
        {
        }
        static const DiscreteTypeInfo type_info;
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
    };

    template <typename T>
    class IntegralVectorAdapter : public TypeAdapter<std::vector<T>>,
                                  public ValueAdapter<std::vector<int64_t>>
    {
    public:
        IntegralVectorAdapter(const std::vector<T>& value)
            : TypeAdapter<std::vector<T>>(value)
        {
        }
        static const DiscreteTypeInfo type_info;
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::vector<int64_t>& get() override;
        void set(const std::vector<int64_t>& value) override;
    };

    class Shape;
    template <>
    class ObjectAdapter<Shape> : public TypeAdapter<Shape>,
                                 public ValueAdapter<std::vector<int64_t>>
    {
    public:
        ObjectAdapter<Shape>(Shape& value)
            : TypeAdapter<Shape>(value)
        {
        }
        static constexpr DiscreteTypeInfo type_info{"ObjectAdapter<Shape>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::vector<int64_t>& get() override;
        void set(const std::vector<int64_t>& value) override;
    };

    class Strides;
    template <>
    class ObjectAdapter<Strides> : public TypeAdapter<Strides>,
                                   public ValueAdapter<std::vector<int64_t>>
    {
    public:
        ObjectAdapter<Strides>(Strides& value)
            : TypeAdapter<Strides>(value)
        {
        }
        static constexpr DiscreteTypeInfo type_info{"ObjectAdapter<Strides>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::vector<int64_t>& get() override;
        void set(const std::vector<int64_t>& value) override;
    };

    class AxisSet;
    template <>
    class ObjectAdapter<AxisSet> : public TypeAdapter<AxisSet>,
                                   public ValueAdapter<std::vector<int64_t>>
    {
    public:
        ObjectAdapter<AxisSet>(AxisSet& value)
            : TypeAdapter<AxisSet>(value)
        {
        }
        static constexpr DiscreteTypeInfo type_info{"ObjectAdapter<AxisSet>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::vector<int64_t>& get() override;
        void set(const std::vector<int64_t>& value) override;
    };

    class PartialShape;
    template <>
    class ObjectAdapter<PartialShape> : public TypeAdapter<PartialShape>, public ValueAdapter<void>
    {
    public:
        ObjectAdapter<PartialShape>(PartialShape& value)
            : TypeAdapter<PartialShape>(value)
        {
        }
        static constexpr DiscreteTypeInfo type_info{"ObjectAdapter<PartialShape>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
    };

    namespace element
    {
        class Type;
    }

    template <>
    class ObjectAdapter<element::Type> : public TypeAdapter<element::Type>,
                                         public ValueAdapter<void>
    {
    public:
        ObjectAdapter<element::Type>(element::Type& value)
            : TypeAdapter<element::Type>(value)
        {
        }
        static constexpr DiscreteTypeInfo type_info{"ObjectAdapter<element::Type>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
    };
}
