#ifndef VAMPTEST_VAMPTEST_H
#define VAMPTEST_VAMPTEST_H

#define VAMPTEST_MAX_NAME_CHARACTERS 32

typedef struct VampTestNode
{
    char m_test_name[VAMPTEST_MAX_NAME_CHARACTERS];
    char m_suite_name[VAMPTEST_MAX_NAME_CHARACTERS];
    char m_failed;
    struct VampTestNode *m_next;

    void (*run)(struct VampTestNode *self);

}VampTestNode;

VampTestNode *vampCreateTest(const char *suite_name, const char *test_name);
void vampDestroyTest(VampTestNode **user_ptr);

typedef struct VampTestApp
{
    int m_total_tests;
    int m_total_fails;

    VampTestNode *m_head;
    VampTestNode *m_tail;

    void (*addTest)(struct VampTestApp *self, VampTestNode *test);
    void (*runAll)(struct VampTestApp *self);

}VampTestApp;


VampTestNode *vampCreateTest(const char *suite_name, const char *test_name);
void vampDestroyTest(VampTestNode **user_ptr);

VampTestApp *vampCreateApp();
void vampDestroyApp(VampTestApp **user_ptr);


#ifdef VAMPTEST_MAIN
    void vampUserEntryPoint(VampTestApp *app);

    int main(int argc, char **argv)
    {
        VampTestApp *app = vampCreateApp();

        vampUserEntryPoint(app);

        app->runAll(app);

        vampDestroyApp(&app);

        return 0;
    }
#endif

#endif