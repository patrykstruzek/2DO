#pragma once

#include <iostream>
#include <optional>

namespace twodo
{
    enum class ErrorCode
    {
        ok,
        panic,
        invalid_input,
        incorrect_nickname,
        already_existing_name,
        incorrect_password,
        not_match_regex,
        cin_failure,
    };

    template<typename T>
    struct Result 
    {
    public:
        std::optional<T> m_value;
        ErrorCode m_err{ ErrorCode::ok };
    };

    template<>
    struct Result<void>
    {
    public:
        ErrorCode m_err{ ErrorCode::ok };
    };
}