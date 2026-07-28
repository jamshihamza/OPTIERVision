#pragma once

#include <utility>

#include <optier/ErrorCode.h>
#include <optional>

namespace optier
{
    template<typename T>
    class [[nodiscard]] Result
    {
    public:
        Result(const T& value)
            : m_success(true)
            , m_value(value)
            , m_error(ErrorCode::None)
        {
        }

        Result(T&& value)
            : m_success(true)
            , m_value(std::move(value))
            , m_error(ErrorCode::None)
        {
        }

        explicit Result(ErrorCode error)
            : m_success(false)
            , m_value()
            , m_error(error)
        {
        }

        bool IsSuccess() const noexcept
        {
            return m_success;
        }

        bool IsFailure() const noexcept
        {
            return !m_success;
        }

        bool HasValue() const noexcept
        {
            return m_value.has_value();
        }

        const T& Value() const
        {
            return m_value.value();
        }

        T& Value()
        {
            return m_value.value();
        }

        ErrorCode Error() const
        {
            return m_error;
        }

        static Result Success(T value)
        {
            return Result(std::move(value));
        }

        static Result Failure(ErrorCode error)
        {
            return Result(error);
        }

    private:
        bool m_success;
        std::optional<T> m_value;
        ErrorCode m_error;
    };
}