/*
*
*   Thanks to: https://github.com/pritamzope/OS ;) 
*
*/

#include "ahas.h"

void init_parts(uint16 main_x, uint16 main_y, uint16 current_direction, int parts_count, uint16 * parts_x, uint16 * parts_y, uint16 * parts_direction) {
    uint16 temp_x = 0;
    uint16 temp_y = 0;

    temp_x = main_x;
    temp_y = main_y;

    for (int n = 0; n < parts_count; n++) {
        parts_x[n] = temp_x;
        parts_y[n] = temp_y;
        parts_direction[n] = current_direction;
        temp_y += BOX_SIZE;
    }
}

void ahas_run() {
    uint8 b = 0;
    uint16 main_x = 100;
    uint16 main_y = 100;
    int duration = 5;
    int parts_count = 10;
    int is_ok = FALSE;
    uint16 lowerx1 = 0;
    uint16 lowery1 = 0;
    uint16 lowerx2 = 0;
    uint16 lowery2 = 0;
    uint16 current_direction = 2;
    int faster = 0;
    // 0 - down
    // 1 - left
    // 2 - up
    // 3 - right

    uint16 parts_x[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    uint16 parts_y[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    uint16 parts_direction[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    uint16 last_part_x = 0;
    uint16 last_part_y = 0;
    uint16 last_part_direction = 0;

    uint16 temp_parts_x[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    uint16 temp_parts_y[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    uint16 temp_parts_direction[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    int current_food = 0;
    uint16 food_x[20] = { 200, 15, 100, 300, 80, 60, 95, 250, 45, 210, 25, 70, 120, 65 };
    uint16 food_y[20] = { 150, 80, 100, 190, 30, 65, 180, 95, 70, 45, 25, 110, 15, 130 };

    fill_rect(0, 0, VGA_MAX_WIDTH, VGA_MAX_HEIGHT, CYAN);
    draw_string(108, 60, MAGENTA, "LARONG AHAS");
    draw_string(150, 75, RED, "NI");
    draw_string(92, 90, BLACK, "FERDINAND SILVA");
    draw_rect(4, 4, 311, 191, BRIGHT_RED);
    draw_rect(6, 6, 307, 187, BRIGHT_RED);
    draw_string(70, 150, RED, "PRESS SPACE TO START");

    while (1) {
        b = get_input_keycode();
        sleep(5);
        if (b == KEY_SPACE)
            break;
        b = 0;
    }
    clear_screen();

    init_parts(main_x, main_y, current_direction, parts_count, parts_x, parts_y, parts_direction);    

    while (1) {
        clear_screen();
        b = 0;
        is_ok = FALSE;

        //draw food
        fill_rect(food_x[current_food], food_y[current_food], BOX_SIZE, BOX_SIZE, YELLOW);

        //draw parts
        for (int n = 0; n < parts_count; n++) {
            fill_rect(parts_x[n], parts_y[n], BOX_SIZE, BOX_SIZE, BRIGHT_CYAN);
        }   
        //end of draw parts

        //slither
        switch(current_direction) {
            case 1:
                main_x -= BOX_SIZE;
            break;
            case 2:
                main_y -= BOX_SIZE;
            break;
            case 3:
                main_x += BOX_SIZE;
            break;
            default:
                main_y += BOX_SIZE;
        }

        for (int n = 0; n < parts_count; n++) {
            temp_parts_x[n] = parts_x[n];
            temp_parts_y[n] = parts_y[n];
            temp_parts_direction[n] = parts_direction[n];
        }

        parts_x[0] = main_x;
        parts_y[0] = main_y;
        parts_direction[0] = current_direction;

        for (int n = 0; n < (parts_count - 1); n++) {
            parts_x[n+1] = temp_parts_x[n];
            parts_y[n+1] = temp_parts_y[n];
            parts_direction[n+1] = temp_parts_direction[n];
        }

        if (main_y + BOX_SIZE > 0 && main_y < VGA_MAX_HEIGHT && main_x + BOX_SIZE > 0 && main_x < VGA_MAX_WIDTH) {
            is_ok = TRUE;

            //check collision with parts below
            for (int n = 0; n < parts_count; n++) {
                if (n > 2) {
                    lowerx1 = parts_x[n] + BOX_SIZE - 1;
                    lowery1 = parts_y[n] + BOX_SIZE - 1;
                    lowerx2 = parts_x[0] + BOX_SIZE - 1;
                    lowery2 = parts_y[0] + BOX_SIZE - 1;

                    if (!((lowerx1 < parts_x[0]) || (parts_x[n] > lowerx2) || (lowery1 < parts_y[0]) || (parts_y[n] > lowery2))) {
                        is_ok = FALSE;
                        break;
                    }
                }
            }
            //end 

            if(is_ok) {
                //check collision with food

                lowerx1 = food_x[current_food] + BOX_SIZE - 1;
                lowery1 = food_y[current_food] + BOX_SIZE - 1;
                lowerx2 = parts_x[0] + BOX_SIZE - 1;
                lowery2 = parts_y[0] + BOX_SIZE - 1;

                if (!((lowerx1 < parts_x[0]) || (food_x[current_food] > lowerx2) || (lowery1 < parts_y[0]) || (food_y[current_food] > lowery2))) {
                    current_food++;
                    last_part_x = parts_x[parts_count - 1];
                    last_part_y = parts_y[parts_count - 1];
                    last_part_direction = parts_direction[parts_count - 1];

                    switch(last_part_direction) {
                        case 1:
                            last_part_x -= BOX_SIZE;
                        break;
                        case 2:
                            last_part_y -= BOX_SIZE;
                        break;
                        case 3:
                            last_part_x += BOX_SIZE;
                        break;
                        default:
                            last_part_y += BOX_SIZE;
                    }

                    parts_x[parts_count] = last_part_x;
                    parts_y[parts_count] = last_part_y;
                    parts_direction[parts_count] = last_part_direction;
                    parts_count++;
                    faster++;

                    if (faster == 3) {
                        faster = 0;
                        duration--;
                    }
                }

                //end
            }
        }

        if (!is_ok) {
            break;
        }

        //end of slither

        b = get_input_keycode();

        if (b == KEY_DOWN) {
            if (current_direction != 2) {
                current_direction = 0;
            }
        } else if (b == KEY_LEFT) {
            if (current_direction != 3) {
                current_direction = 1;
            }
        } else if (b == KEY_UP) {
            if (current_direction != 0) {
                current_direction = 2;
            }
        } else if (b == KEY_RIGHT) {
            if (current_direction != 1) {
                current_direction = 3;
            }
        }

        sleep(duration);
    }
}