/*! \file ********************************************************************
 *
 *  \brief      Testing app for CharRing
 *  \author     Dan Fekete <thefekete@gmail.com>
 *  \date       March 10, 2015
 *
 *  \copyright  Copyright 2015, Dan Fekete <thefekete@gmail.com>
 *              LICENSE
 *
 *  Tests functionality of CharRing module
 *
 *****************************************************************************/
#include <glib.h>
#include <stdio.h>
#include "../charring.h"


#define BUF_LEN 1024


typedef struct {
    CharRingBuf *buf;
} Fixture;


void setup(Fixture *f, gconstpointer test_data)
{
    f->buf = CharRing_new(BUF_LEN);
}

void teardown(Fixture *f, gconstpointer test_data)
{
    CharRing_free(f->buf);
}

void test_new(Fixture *f, gconstpointer ignored)
{
    g_assert(f->buf);  // not null ptr
}

void test_empty(Fixture *f, gconstpointer ignored)
{
    g_assert(CharRing_empty(f->buf));
    g_assert_cmpint(CharRing_getchar(f->buf), == , '\0'); // buffer is empty
}

void test_full(Fixture *f, gconstpointer ignored)
{
    for (int i = 0; i < BUF_LEN; i++) {
        g_assert(!CharRing_full(f->buf));
        CharRing_putchar(f->buf, 'A' + i);
    }
    g_assert(CharRing_full(f->buf));
}

void test_available(Fixture *f, gconstpointer ignored)
{
    g_assert_cmpint(CharRing_available(f->buf), == , 0);
    for (int i = 0; i < BUF_LEN; i++) {
        CharRing_putchar(f->buf, 'A' + i);
        g_assert_cmpint(CharRing_available(f->buf), == , i + 1);
    }
}

void test_free_space(Fixture *f, gconstpointer ignored)
{
    g_assert_cmpint(CharRing_free_space(f->buf), == , BUF_LEN);
    for (int i = 0; i < BUF_LEN; i++) {
        CharRing_putchar(f->buf, 'A' + i);
        g_assert_cmpint(CharRing_free_space(f->buf), == , BUF_LEN - (i + 1));
    }
}

void test_put_get(Fixture *f, gconstpointer ignored)
{
    CharRing_putchar(f->buf, 'a');
    CharRing_putchar(f->buf, 'b');
    CharRing_putchar(f->buf, 'c');
    CharRing_putchar(f->buf, 'd');
    g_assert_cmpint(CharRing_getchar(f->buf), == , 'a');
    g_assert_cmpint(CharRing_getchar(f->buf), == , 'b');
    g_assert_cmpint(CharRing_getchar(f->buf), == , 'c');
    g_assert_cmpint(CharRing_getchar(f->buf), == , 'd');
}

void test_circular(Fixture *f, gconstpointer ignored)
{
    // loop buffer twice and add two more
    for (int i = 0; i < (BUF_LEN*2 + 2); i++) {
        CharRing_putchar(f->buf, i);
    }

    for (int i = 0; i < BUF_LEN; i++) {
        g_assert_cmpint(CharRing_getchar(f->buf), ==, (char) (i+BUF_LEN+2));
    }
}



/** \brief Run tests for charring module */
int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);

    g_test_add("/charring/new", Fixture, NULL,
            setup, test_new, teardown);
    g_test_add("/charring/empty", Fixture, NULL,
            setup, test_empty, teardown);
    g_test_add("/charring/full", Fixture, NULL, setup,
            test_full, teardown);
    g_test_add("/charring/available", Fixture, NULL,
            setup, test_available, teardown);
    g_test_add("/charring/free_space", Fixture, NULL,
            setup, test_free_space, teardown);
    g_test_add("/charring/put_get", Fixture, NULL,
            setup, test_put_get, teardown);
    g_test_add("/charring/circular", Fixture, NULL,
            setup, test_circular, teardown);

    return g_test_run();
}
