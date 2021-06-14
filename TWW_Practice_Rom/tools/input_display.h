#ifndef INPUT_DISPLAY_H_INCLUDED
#define INPUT_DISPLAY_H_INCLUDED

#define INPUT_SIZE 12

typedef struct input_display {
    void (*init[INPUT_SIZE])();
    void (*draw[INPUT_SIZE])();
} input_display;

void input_display__new(input_display *this);
void input_display__draw(input_display *this);

void stick_display_init();
void stick_display_draw();


void d_pad_left_display_init();
void d_pad_left_display_draw();

void d_pad_right_display_init();
void d_pad_right_display_draw();

void d_pad_down_display_init();
void d_pad_down_display_draw();

void d_pad_up_display_init();
void d_pad_up_display_draw();

void z_display_init();
void z_display_draw();

void r_display_init();
void r_display_draw();

void l_display_init();
void l_display_draw();

void x_display_init();
void x_display_draw();

void y_display_init();
void y_display_draw();

void a_display_init();
void a_display_draw();

void b_display_init();
void b_display_draw();

void start_display_init();
void start_display_draw();

#endif