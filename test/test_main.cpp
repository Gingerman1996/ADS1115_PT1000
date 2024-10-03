#include <Arduino.h>
#include <unity.h>
#include "main.h"  // Include the header file where the function is declared

// Test mapping for the minimum value (0)
void test_map_min_value() {
    uint8_t result = map_3300_to_255(0);
    TEST_ASSERT_EQUAL_UINT8(0, result);  // Expecting 0
}

// Test mapping for the midpoint (1650) - should round up to 128
void test_map_mid_value() {
    uint8_t result = map_3300_to_255(1650);
    TEST_ASSERT_EQUAL_UINT8(128, result);  // Expecting 128
}

// Test mapping for the maximum value (3300)
void test_map_max_value() {
    uint8_t result = map_3300_to_255(3300);
    TEST_ASSERT_EQUAL_UINT8(255, result);  // Expecting 255
}

// Test mapping for a value that should round down (1649 should be 127)
void test_map_round_down() {
    uint8_t result = map_3300_to_255(1649);
    TEST_ASSERT_EQUAL_UINT8(127, result);  // Expecting 127 (round down)
}

// Test mapping for a value that should round up (1651 should be 128)
void test_map_round_up() {
    uint8_t result = map_3300_to_255(1651);
    TEST_ASSERT_EQUAL_UINT8(128, result);  // Expecting 128 (round up)
}

// Test mapping for a value exceeding 3300, should be capped at 255
void test_map_exceeding_value() {
    uint8_t result = map_3300_to_255(4000);
    TEST_ASSERT_EQUAL_UINT8(255, result);  // Expecting 255
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_map_min_value);
    RUN_TEST(test_map_mid_value);
    RUN_TEST(test_map_max_value);
    RUN_TEST(test_map_round_down);
    RUN_TEST(test_map_round_up);
    RUN_TEST(test_map_exceeding_value);
    UNITY_END();
}

void loop() {
    // Empty loop for testing
}
