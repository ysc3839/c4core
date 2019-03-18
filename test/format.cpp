#include "c4/std/string.hpp"
#include "c4/std/vector.hpp"
#include "c4/test.hpp"
#include "c4/format.hpp"

namespace c4 {

TEST(cat, vars)
{
    char buf[256];
    substr sp(buf);
    csubstr result;
    size_t sz;

    sz = cat(buf, 1, ' ', 2, ' ', 3, ' ', 4);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 2 3 4");
}

#ifdef C4_TUPLE_TO_STR
TEST(cat, tuple)
{
    char buf[256];
    substr sp(buf);
    csubstr result;
    size_t sz;

    sz = cat(buf, std::forward_as_tuple(1, ' ', 2, ' ', 3, ' ', 4));
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 2 3 4");
}
#endif // C4_TUPLE_TO_STR

TEST(uncat, vars)
{
    size_t sz;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;

    sz = uncat("1 2 3 4", v1, v2, v3, v4);
    EXPECT_NE(sz, csubstr::npos);
    EXPECT_EQ(sz, 7);
    EXPECT_EQ(v1, 1);
    EXPECT_EQ(v2, 2);
    EXPECT_EQ(v3, 3);
    EXPECT_EQ(v4, 4);
}

#ifdef C4_TUPLE_TO_STR
TEST(uncat, tuple)
{
    size_t sz;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;

    auto tp = std::forward_as_tuple(v1, v2, v3, v4);
    sz = uncat("1 2 3 4", tp);
    EXPECT_NE(sz, csubstr::npos);
    EXPECT_EQ(sz, 7);
    EXPECT_EQ(v1, 1);
    EXPECT_EQ(v2, 2);
    EXPECT_EQ(v3, 3);
    EXPECT_EQ(v4, 4);
}
#endif // C4_TUPLE_TO_STR

TEST(catsep, vars)
{
    char buf[256];
    substr sp(buf);
    csubstr result;
    size_t sz;

    sz = catsep(buf, ' ', 1, 2);
    EXPECT_EQ(sz, 3);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 2");

    sz = catsep(buf, '/', 1, 2);
    EXPECT_EQ(sz, 3);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1/2");

    sz = catsep(buf, ' ', 1, 2, 3, 4);
    EXPECT_EQ(sz, 7);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 2 3 4");

    sz = catsep(buf, '/', 1, 2, 3, 4);
    EXPECT_EQ(sz, 7);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1/2/3/4");
}

#ifdef C4_TUPLE_TO_STR
TEST(catsep, tuple)
{
    char buf[256];
    substr sp(buf);
    csubstr result;
    size_t sz;

    sz = catsep(buf, ' ', std::forward_as_tuple(1, 2));
    EXPECT_EQ(sz, 3);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 2");

    sz = catsep(buf, '/', std::forward_as_tuple(1, 2));
    EXPECT_EQ(sz, 3);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1/2");

    sz = catsep(buf, ' ', std::forward_as_tuple(1, 2, 3, 4));
    EXPECT_EQ(sz, 7);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 2 3 4");

    sz = catsep(buf, '/', std::forward_as_tuple(1, 2, 3, 4));
    EXPECT_EQ(sz, 7);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1/2/3/4");
}
#endif // C4_TUPLE_TO_STR

TEST(uncatsep, vars)
{
    size_t sz;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    char sep;

    sz = uncatsep("1 2 3 4", sep, v1, v2, v3, v4);
    EXPECT_EQ(sz, 7);
    EXPECT_EQ(v1, 1);
    EXPECT_EQ(v2, 2);
    EXPECT_EQ(v3, 3);
    EXPECT_EQ(v4, 4);
}

#ifdef C4_TUPLE_TO_STR
TEST(uncatsep, tuple)
{
    size_t sz;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    char sep;

    auto tp = std::forward_as_tuple(v1, v2, v3, v4);
    sz = uncatsep("1 2 3 4", sep, tp);
    EXPECT_EQ(sz, 7);
    EXPECT_EQ(v1, 1);
    EXPECT_EQ(v2, 2);
    EXPECT_EQ(v3, 3);
    EXPECT_EQ(v4, 4);
}
#endif // C4_TUPLE_TO_STR

TEST(format, vars)
{
    char buf[256];
    substr sp(buf);
    csubstr result;
    size_t sz;

    sz = format(buf, "{} and {} and {} and {}", 1, 2, 3, 4);
    EXPECT_EQ(sz, 19);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and 2 and 3 and 4");

    sz = format(buf, "{} and {} and {} and {}", 1, 2, 3, 4, 5, 6, 7);
    EXPECT_EQ(sz, 19);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and 2 and 3 and 4");

    sz = format(buf, "{} and {} and {} and {}", 1, 2, 3);
    EXPECT_EQ(sz, 20);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and 2 and 3 and {}");

    sz = format(buf, "{} and {} and {} and {}", 1, 2);
    EXPECT_EQ(sz, 21);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and 2 and {} and {}");

    sz = format(buf, "{} and {} and {} and {}", 1);
    EXPECT_EQ(sz, 22);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and {} and {} and {}");

    sz = format(buf, "{} and {} and {} and {}");
    EXPECT_EQ(sz, 23);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "{} and {} and {} and {}");
}

#ifdef C4_TUPLE_TO_STR
TEST(format, tuple)
{
    char buf[256];
    substr sp(buf);
    csubstr result;
    size_t sz;

    sz = format(buf, "{} and {} and {} and {}", std::forward_as_tuple(1, 2, 3, 4));
    EXPECT_EQ(sz, 19);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and 2 and 3 and 4");

    sz = format(buf, "{} and {} and {} and {}", std::forward_as_tuple(1, 2, 3, 4, 5, 6, 7));
    EXPECT_EQ(sz, 19);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and 2 and 3 and 4");

    sz = format(buf, "{} and {} and {} and {}", std::forward_as_tuple(1, 2, 3));
    EXPECT_EQ(sz, 20);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and 2 and 3 and {}");

    sz = format(buf, "{} and {} and {} and {}", std::forward_as_tuple(1, 2));
    EXPECT_EQ(sz, 21);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and 2 and {} and {}");

    sz = format(buf, "{} and {} and {} and {}", std::forward_as_tuple(1));
    EXPECT_EQ(sz, 22);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "1 and {} and {} and {}");

    sz = format(buf, "{} and {} and {} and {}");
    EXPECT_EQ(sz, 23);
    result = sp.left_of(sz);
    EXPECT_EQ(result, "{} and {} and {} and {}");
}
#endif // C4_TUPLE_TO_STR

TEST(unformat, vars)
{
    size_t sz;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;

    sz = unformat("1 and 2 and 3 and 4", "{} and {} and {} and {}", v1, v2, v3, v4);
    EXPECT_EQ(sz, 19);
    EXPECT_EQ(v1, 1);
    EXPECT_EQ(v2, 2);
    EXPECT_EQ(v3, 3);
    EXPECT_EQ(v4, 4);
}

#ifdef C4_TUPLE_TO_STR
TEST(unformat, tuple)
{
    size_t sz;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;

    auto tp = std::forward_as_tuple(v1, v2, v3, v4);
    sz = unformat("1 and 2 and 3 and 4", "{} and {} and {} and {}", tp);
    EXPECT_EQ(sz, 19);
    EXPECT_EQ(v1, 1);
    EXPECT_EQ(v2, 2);
    EXPECT_EQ(v3, 3);
    EXPECT_EQ(v4, 4);
}
#endif // C4_TUPLE_TO_STR


TEST(printf, basic)
{
    char bufc[128];
    substr buf = bufc;
    size_t ret;

    memset(buf.str, 0, buf.len);
    ret = sprintf(buf, "hello world");
    EXPECT_EQ(buf.first(ret), "hello world");

    memset(buf.str, 0, buf.len);
    ret = sprintf(buf, "%d %d %d %d", 1, 2, 3, 4);
    EXPECT_EQ(buf.first(ret), "1 2 3 4");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
TEST(catrs, basic)
{
    std::vector<char> buf;

    catrs(&buf, 1, 2, 3, 4);
    EXPECT_EQ(to_csubstr(buf), "1234");
    catrs(&buf, 5, 6, 7, 8);
    EXPECT_EQ(to_csubstr(buf), "5678");
}

TEST(catrs, basic_append)
{
    std::vector<char> buf;

    catrs(append, &buf, 1, 2, 3, 4);
    EXPECT_EQ(to_csubstr(buf), "1234");
    catrs(append, &buf, 5, 6, 7, 8);
    EXPECT_EQ(to_csubstr(buf), "12345678");
    catrs(append, &buf, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8);
    EXPECT_EQ(to_csubstr(buf), "123456789012345678");
}

TEST(catseprs, basic)
{
    std::vector<char> buf;

    catseprs(&buf, ' ', 1, 2, 3, 4);
    EXPECT_EQ(to_csubstr(buf), "1 2 3 4");
    catseprs(&buf, ' ', 5, 6, 7, 8);
    EXPECT_EQ(to_csubstr(buf), "5 6 7 8");

    catseprs(&buf, ',', 1, 2, 3, 4);
    EXPECT_EQ(to_csubstr(buf), "1,2,3,4");
    catseprs(&buf, ',', 5, 6, 7, 8);
    EXPECT_EQ(to_csubstr(buf), "5,6,7,8");

    catseprs(&buf, '/', 1, 2, 3, 4);
    EXPECT_EQ(to_csubstr(buf), "1/2/3/4");
    catseprs(&buf, '/', 5, 6, 7, 8);
    EXPECT_EQ(to_csubstr(buf), "5/6/7/8");

    catseprs(&buf, "///", 1, 2, 3, 4);
    EXPECT_EQ(to_csubstr(buf), "1///2///3///4");
    catseprs(&buf, "///", 5, 6, 7, 8);
    EXPECT_EQ(to_csubstr(buf), "5///6///7///8");
}

TEST(catseprs, basic_append)
{
    std::vector<char> buf;

    catseprs(append, &buf, ' ', 1, 2, 3, 4);
    EXPECT_EQ(to_csubstr(buf), "1 2 3 4");
    catseprs(append, &buf, ' ', 5, 6, 7, 8);
    EXPECT_EQ(to_csubstr(buf), "1 2 3 45 6 7 8");
    catseprs(append, &buf, ' ', 9, 0, 1, 2, 3, 4, 5, 6, 7, 8);
    EXPECT_EQ(to_csubstr(buf), "1 2 3 45 6 7 89 0 1 2 3 4 5 6 7 8");
}

TEST(formatrs, basic)
{
    std::vector<char> buf;

    formatrs(&buf, "{} goes with food, {} goes with heat, {} anytime", "wine", "beer", "coffee");
    EXPECT_EQ(to_csubstr(buf), "wine goes with food, beer goes with heat, coffee anytime");
}

TEST(formatrs, basic_append)
{
    std::vector<char> buf;

    formatrs(append, &buf, "{} goes with food", "wine");
    EXPECT_EQ(to_csubstr(buf), "wine goes with food");
    formatrs(append, &buf, ", {} goes with heat", "beer");
    EXPECT_EQ(to_csubstr(buf), "wine goes with food, beer goes with heat");
    formatrs(append, &buf, ", {} anytime", "coffee");
    EXPECT_EQ(to_csubstr(buf), "wine goes with food, beer goes with heat, coffee anytime");

    formatrs(append, &buf, ". And water. {} glass of {}cl in the morning clears you up for the day", 1, 40);
    EXPECT_EQ(to_csubstr(buf), "wine goes with food, beer goes with heat, coffee anytime. And water. 1 glass of 40cl in the morning clears you up for the day");
}

} // namespace c4