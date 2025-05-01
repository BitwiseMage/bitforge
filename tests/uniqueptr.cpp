#include "core/uniqueptr.h"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("UniquePtr lifetime handling", "[uniqueptr]")
{
    char* raw = new char('A');
    char* raw2 = new char('B');
    {
        UniquePtr<char> char_unique_ptr(raw);
        REQUIRE(char_unique_ptr.GetRawPtr() == raw);

        char_unique_ptr = nullptr;
        REQUIRE(char_unique_ptr.GetRawPtr() == nullptr);

        UniquePtr<char> char_unique_ptr_moved(raw2);
        REQUIRE(char_unique_ptr_moved.GetRawPtr() == raw2);

        UniquePtr<char> acquired_char_unique_ptr(std::move(char_unique_ptr_moved));
        REQUIRE(char_unique_ptr_moved.GetRawPtr() == nullptr);
        REQUIRE(acquired_char_unique_ptr.GetRawPtr() == raw2);
    }

    REQUIRE(*raw != 'A');
    REQUIRE(*raw2 != 'B');
}