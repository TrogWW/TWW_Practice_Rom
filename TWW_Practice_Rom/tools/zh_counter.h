#ifndef ZH_COUNTER_H_INCLUDED
#define ZH_COUNTER_H_INCLUDED

#define ZH_DATA_SIZE 90

typedef struct zh_counter {
    // int b_press_count;
    // int total_frames;
    // int curr_b_press_average_index;
    // float b_press_averages[4];
    // // float b_press_avg;
    // int count_index;
    int curr_index;
    bool b_presses[ZH_DATA_SIZE];
    char text[40];
    J2DTextBox *display;
} zh_counter;

void zh_counter__new(zh_counter *this);
void zh_counter__draw(zh_counter *this);
#endif