#include <ctest.h>

#include <field.h>

CTEST(endgame_check_suite, dead_field_test) {
    // Given
    unsigned int i;

    char **test_table = malloc(4 * sizeof(char*));

    for (i = 0; i < 4; i++) {
        test_table[i] = malloc(4 * sizeof(char));
    }

    test_table = {{0}, {0}, {0}, {0},
                  {0}, {0}, {0}, {0}
                  {0}, {0}, {0}, {0}
                  {0}, {0}, {0}, {0}}

    field *test_field = field_create(4);
    table_set(test_field, table_set);

    // When
    const unsigned int result = field_endgame_check(test_field);

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

    test_table = {{0}, {0}, {0}, {0},
                  {0}, {1}, {1}, {0}
                  {0}, {1}, {1}, {0}
                  {0}, {0}, {0}, {0}}

    field *test_field = field_create(4);
    table_set(test_field, table_set);

    // When
    const unsigned int result = field_endgame_check(test_field);

    // Then
    const unsigned int expected_result = 1;

    ASSERT_EQUAL(expected_result, result);
}