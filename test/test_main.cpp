#include <Arduino.h>
#include <unity.h>
#include "main.h"  // Include ฟังก์ชันที่ต้องการทดสอบ

// ทดสอบการ map ค่าต่ำสุด (0)
void test_map_min_value() {
    uint8_t result = map_3300_to_255(0);
    TEST_ASSERT_EQUAL_UINT8(0, result);  // คาดหวังผลลัพธ์เป็น 0
}

// ทดสอบการ map ค่ากลาง (1650)
void test_map_mid_value() {
    uint8_t result = map_3300_to_255(1650);
    TEST_ASSERT_EQUAL_UINT8(127, result);  // คาดหวังผลลัพธ์เป็น 127
}

// ทดสอบการ map ค่าสูงสุด (3300)
void test_map_max_value() {
    uint8_t result = map_3300_to_255(3300);
    TEST_ASSERT_EQUAL_UINT8(255, result);  // คาดหวังผลลัพธ์เป็น 255
}

// ทดสอบค่าเกิน (4000 ควรจะถูก cap ที่ 3300)
void test_map_exceeding_value() {
    uint8_t result = map_3300_to_255(4000);
    TEST_ASSERT_EQUAL_UINT8(255, result);  // คาดหวังผลลัพธ์เป็น 255
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_map_min_value);
    RUN_TEST(test_map_mid_value);
    RUN_TEST(test_map_max_value);
    RUN_TEST(test_map_exceeding_value);
    UNITY_END();
}

void loop() {
    // ไม่มีอะไรต้องทำใน loop
}
