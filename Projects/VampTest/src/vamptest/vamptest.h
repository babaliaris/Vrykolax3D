#ifndef VAMPTEST_VAMPTEST_H
#define VAMPTEST_VAMPTEST_H
#include <vrykolax3D/core/vx3d_std.h>
#include <vrykolax3D/core/debug/vx3d_logger.h>
#include <vrykolax3D/core/debug/vx3d_assert.h>

/**
 * @file
 * @brief A unit-testing framework for Vrykolax3D.
 * @author Bampaliaris Nikolaos
 */

 /**
  * @brief Max chars for suite or test names.
  */
#define VAMPTEST_MAX_NAME_CHARACTERS 256


/**
 * @brief The VampTest test definition.
 * @private
 */
typedef struct VampTestNode
{
    char m_test_name[VAMPTEST_MAX_NAME_CHARACTERS];
    char m_suite_name[VAMPTEST_MAX_NAME_CHARACTERS];
    char m_full_name[2 * VAMPTEST_MAX_NAME_CHARACTERS];
    char m_failed;
    struct VampTestNode *m_next;

    void (*run)(struct VampTestNode *self);

}VampTestNode;


/**
 * @brief The test function callback type.
 */
typedef void (*VampTestFunc)(VampTestNode *__vamp_test_node__);


/**
 * @brief The test application definition.
 * @private
 */
typedef struct VampTestApp
{
    int m_total_tests;
    int m_total_run;
    int m_total_fails;

    VampTestNode *m_head;
    VampTestNode *m_tail;

    void (*addTest)(struct VampTestApp *self, VampTestNode *test);
    void (*runAll)(struct VampTestApp *self);

}VampTestApp;


/**
 * @brief Creates a new test.
 * @private
 */
VampTestNode *vampCreateTest(const char *suite_name, const char *test_name, VampTestFunc func);

/**
 * @brief Destroys a test.
 * @private
 */
void vampDestroyTest(VampTestNode **user_ptr);

/**
 * @brief Creates a new app.
 * @private
 */
VampTestApp *vampCreateApp();


/**
 * @brief Destroys an app.
 * @private
 */
void vampDestroyApp(VampTestApp **user_ptr);



/**
 * @brief Simple preprocessor concatenation.
 * 
 * @param[in] suite_name The suite name where this test belongs.
 * @param[in] test_name The test name of the test.
 */
#define VAMP_CONCAT(suite_name, test_name)\
    suite_name##_##test_name


/**
 * @brief Declares a Test.
 * 
 * Use it in the main.c file where you #define VAMPTEST_MAIN
 * and implemented vampUserEntryPoint so that the linker will know
 * how to locate your tests that live in different .c files.
 * 
 * @param[in] suite_name The suite name where this test belongs.
 * @param[in] test_name The test name of the test.
 */
#define VAMP_DECLARE(suite_name, test_name)\
    void VAMP_CONCAT(suite_name, test_name)(VampTestNode *__vamp_test_node__)


/**
 * @brief Defines a Test.
 * 
 * Use this in any .c file you want to define a new test.
 * 
 * @param[in] suite_name The suite name where this test belongs.
 * @param[in] test_name The test name of the test.
 */
#define VAMP_TEST(suite_name, test_name)\
    VAMP_DECLARE(suite_name, test_name)


/**
 * @brief Register a Test.
 * 
 * Use this to Register a test in the framework.
 *
 * @param[in] app The VampTestApp object provided to you by the vampUserEntryPoint function.
 * @param[in] suite_name The suite name where this test belongs.
 * @param[in] test_name The test name of the test.
 */
#define VAMP_REGISTER(app, suite_name, test_name)\
    app->addTest(app, vampCreateTest(#suite_name, #test_name, VAMP_CONCAT(suite_name, test_name)))



/**
 * @brief Prints a message when a test passes.
 * @private
 * 
 * @param[in] test The VampTestNode object.
 */
#define VAMP_ASSERT_PASS_MSG(test)\
    {\
        const char *n = test->m_full_name;\
        vx3D_printf("[%sPASS%s] %s%s%s\n",\
            VX3D_ANSI_INFO, VX3D_ANSI_RESET, VX3D_ANSI_NOTE, n,\
            VX3D_ANSI_RESET);\
    }



/**
 * @brief Test assertion functionality.
 * 
 * Use this inside your defined tests to test your code.
 * 
 * @param[in] cond Any condition you want to check.
 */
#define VAMP_ASSERT(cond)\
    if ( !(cond) )\
    {\
        const char *n = __vamp_test_node__->m_full_name;\
        __vamp_test_node__->m_failed = 1;\
        \
        vx3D_printf("[%sFAIL%s] %s%s%s %s%s:%d%s => %s%s%s\n",\
        VX3D_ANSI_ERROR, VX3D_ANSI_RESET, VX3D_ANSI_NOTE, n,\
        VX3D_ANSI_RESET, VX3D_ANSI_WARN, __FILE__, __LINE__,\
        VX3D_ANSI_RESET, VX3D_ANSI_INFO, #cond, VX3D_ANSI_RESET);\
        return;\
    }



/**
 * @brief Prints total info before the framework terminates.
 * @private
 * 
 */
#define VAMP_PRINT_TOTAL_INFO\
    vx3D_printf("\n%sTOTAL: \t%d\n%sRUN: \t%d\n%sPASS: \t%d\n%sFAILED: %d%s\n",\
    VX3D_ANSI_TRACE, app->m_total_tests, VX3D_ANSI_NOTE, app->m_total_run,\
    VX3D_ANSI_INFO, app->m_total_tests - app->m_total_fails,\
    VX3D_ANSI_ERROR, app->m_total_fails, VX3D_ANSI_RESET)




/**
 * @brief Define this macro in ONLY one .c file!!!
 * 
 */
#ifdef VAMPTEST_MAIN

    /**
     * @brief User Entry Point Function.
     * 
     * Declare this ONLY ONCE in the same .c file
     * where you #define VAMPTEST_MAIN.
     * Use this function to register tests using the
     * macro: VAMP_REGISTER
     */
    void vampUserEntryPoint(VampTestApp *app);

    int main(int argc, char **argv)
    {
        //Create the testing framework.
        VampTestApp *app = vampCreateApp();

        //This will fail if there is not enough memory.
        VX3D_FATAL_ASSERT(app != NULL);

        //Call the users entry point.
        vampUserEntryPoint(app);

        //Run all the tests.
        app->runAll(app);

        //Print total info.
        VAMP_PRINT_TOTAL_INFO;

        //Destroy the framework.
        vampDestroyApp(&app);

        return 0;
    }
#endif

#endif
