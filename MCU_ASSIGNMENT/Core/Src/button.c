/*
 * button.c
 *
 * Created on: Dec 6, 2025
 * Author: Sang
 */

#include "button.h"

// Biến cờ báo nút nhấn đã được xử lý chưa
int button_buffer[4] = {0, 0, 0, 0};

// Biến đếm thời gian nhấn giữ cho từng nút
int button_long_press_counter[4] = {0, 0, 0, 0};

// Cấu hình phần cứng
GPIO_TypeDef *BUTTON_PORT[4] = {
    BUTTON1_GPIO_Port, BUTTON2_GPIO_Port, BUTTON3_GPIO_Port, BUTTON4_GPIO_Port
};
uint16_t BUTTON_PIN[4] = {
    BUTTON1_Pin,       BUTTON2_Pin,       BUTTON3_Pin,       BUTTON4_Pin
};

// Các thanh ghi chống rung (Debounce registers)
static int button_Register0[4] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
static int button_Register1[4] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
static int button_Register2[4] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
static int button_Register3[4] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE}; // Trạng thái ổn định trước đó

// Hàm nội bộ: Đánh dấu nút đã được nhấn
void subKeyProcess(int button) {
   button_buffer[button] = 1;
}

// Hàm khởi tạo trạng thái ban đầu
void button_init(void) {
   for (int i = 0; i < 4; ++i) {
        int v = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);
        button_Register0[i] = v;
        button_Register1[i] = v;
        button_Register2[i] = v;
        button_Register3[i] = v;
        button_buffer[i]   = 0;
        button_long_press_counter[i] = 0;
    }
}

// Hàm kiểm tra nút nhấn (được gọi bởi FSM)
// Trả về 1 nếu nút được nhấn (hoặc auto-repeat), sau đó tự xóa cờ
int isButtonPressed(int button) {
    if (button < 0 || button >= 4) return 0;

    if (button_buffer[button] == 1) {
        button_buffer[button] = 0; // Xóa cờ sau khi đọc để tránh xử lý lặp lại sai logic
        return 1;
    }
    return 0;
}

// Hàm đọc tín hiệu nút nhấn (được gọi bởi Timer Interrupt mỗi 10ms)
void getKeyInput(int button) {
   if (button < 0 || button >= 4) return;

   // 1. Dịch bit để chống rung
   button_Register0[button] = button_Register1[button];
   button_Register1[button] = button_Register2[button];
   button_Register2[button] = HAL_GPIO_ReadPin(BUTTON_PORT[button], BUTTON_PIN[button]);

   if ((button_Register0[button] == button_Register1[button]) &&
        (button_Register1[button] == button_Register2[button]))
   {
        int stable_now = button_Register2[button];
        if (button_Register3[button] != stable_now) {
            button_Register3[button] = stable_now; // Cập nhật trạng thái

            if (stable_now == PRESSED_STATE) {
                subKeyProcess(button); // Báo nhấn nút
                button_long_press_counter[button] = 0; // Reset đếm nhấn giữ
            }
        }

        // --- XỬ LÝ NHẤN GIỮ (AUTO REPEAT) ---
        if (stable_now == PRESSED_STATE) {
            // Tăng biến đếm thời gian giữ
            button_long_press_counter[button]++;

            // Nếu giữ quá thời gian quy định (ví dụ 3s)
            if (button_long_press_counter[button] >= LONG_PRESS_TIME) {

                // Cứ mỗi AUTO_REPEAT_TIME (200ms) thì kích hoạt lại nút một lần
                if ((button_long_press_counter[button] - LONG_PRESS_TIME) % AUTO_REPEAT_TIME == 0) {
                    subKeyProcess(button); // Tự động kích hoạt lại hành động nhấn
                }
            }
        }
        else {
             // Nếu nhả nút, reset bộ đếm
             button_long_press_counter[button] = 0;
        }
   }
}
