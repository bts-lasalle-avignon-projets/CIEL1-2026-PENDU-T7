// Tests unitaires

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h" // https://github.com/doctest/doctest

int main(int argc, char** argv)
{
    doctest::Context context(argc, argv);
    return context.run();
}
