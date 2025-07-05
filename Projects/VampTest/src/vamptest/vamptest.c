#include "vamptest.h"

VampTestNode *vampCreateTest(const char *suite_name, const char *test_name, VampTestFunc func)
{
    VX3D_FATAL_ASSERT(vx3D_strlen(suite_name) < VAMPTEST_MAX_NAME_CHARACTERS);
    VX3D_FATAL_ASSERT(vx3D_strlen(test_name) < VAMPTEST_MAX_NAME_CHARACTERS);
    VX3D_FATAL_ASSERT(func != NULL);

    VampTestNode *new_test = (VampTestNode *)vx3D_malloc(VX3D_SIZEOF(VampTestNode));

    if (!new_test)
    {
        VX3D_WARN("Out of memory.");
        return NULL;
    }

    vx3D_strcpy(new_test->m_suite_name, suite_name);
    vx3D_strcpy(new_test->m_test_name, test_name);

    vx3D_strcpy(new_test->m_full_name, suite_name);
    vx3D_strcat(new_test->m_full_name, "_");
    vx3D_strcat(new_test->m_full_name, test_name);

    new_test->m_failed  = 0;
    new_test->m_next    = NULL;
    new_test->run       = func;

    return new_test;
}


void vampDestroyTest(VampTestNode **user_ptr)
{
    VX3D_FATAL_ASSERT(user_ptr != NULL);
    VX3D_FATAL_ASSERT(*user_ptr != NULL);

    vx3D_free(*user_ptr);

    *user_ptr = NULL;
}



static void addTestImpl(VampTestApp *self, VampTestNode *test)
{
    VX3D_FATAL_ASSERT(self != NULL);
    VX3D_FATAL_ASSERT(test != NULL);

    //First element in the list.
    if (self->m_head == NULL && self->m_tail == NULL)
    {
        self->m_head = test;
        self->m_tail = test;
    }

    //Append at the end of the list.
    else
    {
        VX3D_FATAL_ASSERT(
            (self->m_head == NULL && self->m_tail == NULL) ||
            (self->m_head != NULL && self->m_tail != NULL)
        );

        self->m_tail->m_next = test;

        self->m_tail = test;
    }

    self->m_total_tests++;
}


static void runAllTestsImpl(VampTestApp *self)
{
    VX3D_FATAL_ASSERT(self != NULL);

    VampTestNode *currentTest = self->m_head;

    while (currentTest)
    {
        currentTest->run(currentTest);

        self->m_total_run++;

        if (currentTest->m_failed)
        {
            self->m_total_fails++;
        }

        else
            VAMP_ASSERT_PASS_MSG(currentTest)

        currentTest = currentTest->m_next;
    }
}


VampTestApp *vampCreateApp()
{
    VampTestApp *new_app = (VampTestApp *)vx3D_malloc(VX3D_SIZEOF(VampTestApp));

    if (!new_app)
    {
        VX3D_WARN("Out of memory.");
        return NULL;
    }

    new_app->m_total_tests  = 0;
    new_app->m_total_run    = 0;
    new_app->m_total_fails  = 0;
    new_app->m_head         = NULL;
    new_app->m_tail         = NULL;
    new_app->addTest        = addTestImpl;
    new_app->runAll         = runAllTestsImpl;

    return new_app;
}


void vampDestroyApp(VampTestApp **user_ptr)
{
    VX3D_FATAL_ASSERT(user_ptr != NULL);
    VX3D_FATAL_ASSERT(*user_ptr != NULL);

    //-------------Delete all the tests-------------//
    VampTestNode *currentTest = (*user_ptr)->m_head;
    VampTestNode *tempTest;
    while (currentTest)
    {
        tempTest    = currentTest;
        currentTest = currentTest->m_next;
        vampDestroyTest(&tempTest);
    }
    //-------------Delete all the tests-------------//

    vx3D_free(*user_ptr);

    *user_ptr = NULL;
}
