#include <ctest.h>

#include <field.h>

CTEST(endgame_check_suite, dead_field_test) {
    // Given
    unsigned int i;

    char **test_table = malloc(4 * sizeof(char*));

    for (i = 0; i < 4; i++) {
        test_table[i] = malloc(4 * sizeof(char));
    }

    {
        test_table[0][0] = 0;
        test_table[0][1] = 0;
        test_table[0][2] = 0;
        test_table[0][3] = 0;
        test_table[1][0] = 0;
        test_table[1][1] = 0;
        test_table[1][2] = 0;
        test_table[1][3] = 0;
        test_table[2][0] = 0;
        test_table[2][1] = 0;
        test_table[2][2] = 0;
        test_table[2][3] = 0;
        test_table[3][0] = 0;
        test_table[3][1] = 0;
        test_table[3][2] = 0;
        test_table[3][3] = 0;
    }

    field *test_field = field_create(4);
    table_set(test_field, test_table);

    // When
    const unsigned int result = field_endgame_check(test_field);
    field_delete(test_field);
    table_delete(test_table, 4);

    // Then
    const unsigned int expected_result = 1;

    ASSERT_EQUAL(expected_result, result);
}

CTEST(endgame_check_suite, static_field_test) {
    // Given
    unsigned int i;

    char **test_table = malloc(4 * sizeof(char*));

    for (i = 0; i < 4; i++) {
        test_table[i] = malloc(4 * sizeof(char));
    }

    {
        test_table[0][0] = 0;
        test_table[0][1] = 0;
        test_table[0][2] = 0;
        test_table[0][3] = 0;
        test_table[1][0] = 0;
        test_table[1][1] = 1;
        test_table[1][2] = 1;
        test_table[1][3] = 0;
        test_table[2][0] = 0;
        test_table[2][1] = 1;
        test_table[2][2] = 1;
        test_table[2][3] = 0;
        test_table[3][0] = 0;
        test_table[3][1] = 0;
        test_table[3][2] = 0;
        test_table[3][3] = 0;
    }

    field *test_field = field_create(4);
    table_set(test_field, test_table);

    // When
    const unsigned int result = field_endgame_check(test_field);
    field_delete(test_field);
    table_delete(test_table, 4);

    // Then
    const unsigned int expected_result = 1;

    ASSERT_EQUAL(expected_result, result);
}