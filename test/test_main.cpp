#include <Arduino.h>
#include <unity.h>

#include "main.h"  // Include the header file where the function is declared

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// Test mapping for the minimum value (0)
void test_map_min_value_3300_to_255() {
  uint8_t result = map_3300_to_255(0);
  TEST_ASSERT_EQUAL_UINT8(0, result);  // Expecting 0
}

// Test mapping for the midpoint (1650) - should round up to 128
void test_map_mid_value_3300_to_255() {
  uint8_t result = map_3300_to_255(1650);
  TEST_ASSERT_EQUAL_UINT8(128, result);  // Expecting 128
}

// Test mapping for the maximum value (3300)
void test_map_max_value_3300_to_255() {
  uint8_t result = map_3300_to_255(3300);
  TEST_ASSERT_EQUAL_UINT8(255, result);  // Expecting 255
}

// Test mapping for a value that should round down (1649 should be 127)
void test_map_round_down_3300_to_255() {
  uint8_t result = map_3300_to_255(1649);
  TEST_ASSERT_EQUAL_UINT8(127, result);  // Expecting 127 (round down)
}

// Test mapping for a value that should round up (1651 should be 128)
void test_map_round_up_3300_to_255() {
  uint8_t result = map_3300_to_255(1651);
  TEST_ASSERT_EQUAL_UINT8(128, result);  // Expecting 128 (round up)
}

// Test mapping for a value exceeding 3300, should be capped at 255
void test_map_exceeding_value_3300_to_255() {
  uint8_t result = map_3300_to_255(4000);
  TEST_ASSERT_EQUAL_UINT8(255, result);  // Expecting 255
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// Test mapping for the minimum value (0)
void test_map_min_value_255_to_3300() {
  float result = map_255_to_3300(0);
  TEST_ASSERT_FLOAT_WITHIN(0.1, 0.0, result);  // Expect result to be 0.0
}

// Test mapping for the midpoint value (127)
void test_map_mid_value_255_to_3300() {
  float result = map_255_to_3300(127);
  TEST_ASSERT_FLOAT_WITHIN(0.1, 1643.52,
                           result);  // Expect result to be approximately 1645.0
}

// Test mapping for the maximum value (255)
void test_map_max_value_255_to_3300() {
  float result = map_255_to_3300(255);
  TEST_ASSERT_FLOAT_WITHIN(0.1, 3300.0, result);  // Expect result to be 3300.0
}

// Test mapping for exceeding value (e.g., 300 should be capped at 255)
void test_map_exceeding_value_255_to_3300() {
  float result = map_255_to_3300(300);
  TEST_ASSERT_FLOAT_WITHIN(
      0.1, 569.41, result);  // Expect result to be 3300.0 (capped at 255)
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_map_min_value_3300_to_255);
  RUN_TEST(test_map_mid_value_3300_to_255);
  RUN_TEST(test_map_max_value_3300_to_255);
  RUN_TEST(test_map_round_down_3300_to_255);
  RUN_TEST(test_map_round_up_3300_to_255);
  RUN_TEST(test_map_exceeding_value_3300_to_255);

  RUN_TEST(test_map_min_value_255_to_3300);        // Test value 0
  RUN_TEST(test_map_mid_value_255_to_3300);        // Test value 127
  RUN_TEST(test_map_max_value_255_to_3300);        // Test value 255
  RUN_TEST(test_map_exceeding_value_255_to_3300);  // Test exceeding value (300)
  UNITY_END();
}

void loop() {
  // Empty loop for testing
}
