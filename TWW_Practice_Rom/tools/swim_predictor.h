#ifndef SWIM_PREDICTOR_H_INCLUDED   //outputs a display for predicting max possible distance to travel
#define SWIM_PREDICTOR_H_INCLUDED

#define DECCELERATION_RATE 2.0
#define PI 3.1415926

typedef struct swim_predictor {
    J2DTextBox *title;

    char current_air_prediction[80];
    J2DTextBox *current_air_prediction_display;

    char max_air_prediction[80];
    J2DTextBox *max_air_prediction_display;
} swim_predictor;

void swim_predictor__new(swim_predictor *this);
void swim_predictor__draw(swim_predictor *this);

float predict_max_swim_distance(float velocity, float animation_frame, int air_meter);
float calc_animation_frame_increment(float velocity, int air);
float calc_true_velocity(float velocity, float animation_frame, int air);
float calc_v_loss_from_animation_frame(float velocity, float animation_frame);
float calc_v_loss_from_air(float velocity, int air);

#endif