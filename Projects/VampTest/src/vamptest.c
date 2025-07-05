#define VAMPTEST_MAIN
#include <vamptest/vamptest.h>

VAMP_TEST(math, add)
{
    VAMP_ASSERT(1 + 1 == 2)
}


VAMP_TEST(math, sub)
{
    VAMP_ASSERT(1 - 1 == -10)
}

void vampUserEntryPoint(VampTestApp *app)
{
    VAMP_REGISTER(app, math, add);
    VAMP_REGISTER(app, math, sub);
}
