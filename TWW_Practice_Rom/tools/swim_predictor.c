#ifndef SWIM_PREDICTOR_C_INCLUDED
#define SWIM_PREDICTOR_C_INCLUDED

#include "swim_predictor.h"

swim_predictor SWIM_PREDICTOR;
float predict_text_width = 300.0f;
float predict_text_xOffset = 350.0f;
float predict_text_yOffset = 170.0f;
float predict_text_font_size = 0.8f;
bool swim_predictor_initialized = false;
void swim_predictor__new(swim_predictor *this){
    this->title = (J2DTextBox *)JKernel__operator_new(sizeof(J2DTextBox));
    this->current_air_prediction_display = (J2DTextBox *)JKernel__operator_new(sizeof(J2DTextBox));
    this->max_air_prediction_display = (J2DTextBox *)JKernel__operator_new(sizeof(J2DTextBox));

    J2DTextBox__J2DTextBox(this->title,"rock_24_20_4i_usa.bfn", "Swim Predictor");
    J2DTextBox__J2DTextBox(this->current_air_prediction_display,"rock_24_20_4i_usa.bfn", &this->current_air_prediction);
    J2DTextBox__J2DTextBox(this->max_air_prediction_display,"rock_24_20_4i_usa.bfn", &this->max_air_prediction);

    swim_predictor_initialized = true;
}
void swim_predictor__draw(swim_predictor *this){
    if(swim_predictor_initialized == false || g_dComIfG_gameInfo.mPlay.mpLinkActor == 0){
        return;
    }
    int link_state = g_dComIfG_gameInfo.mPlay.mpLinkActor->mCurProc;
    if(link_state < 51 || link_state > 55){ //if not swimming
        return;
    }
    float velocity = g_dComIfG_gameInfo.mPlay.mpLinkActor->field_0x35bc;
    if(velocity < -10.0f){      //do not display tool if not superswimming fast enough
        float animation_frame = g_dComIfG_gameInfo.mPlay.mpLinkActor->field_0x302c[0].mCurrentTime;
        int air_meter = g_dComIfG_gameInfo.mPlay.field_0x48c4;
        
        velocity = velocity * -1.0f;

        float predicted_swim_distance = predict_max_swim_distance(velocity, animation_frame, air_meter) / 100000.0f;
        float predicted_swim_distance_max_air = predict_max_swim_distance(velocity, animation_frame, 900) / 100000.0f;

        //OSReport(MSL_C_PPCEABI_bare_H__printf("swim_predictor__draw: animation_frame = %f, air_meter = %d, velocity = %f\n",animation_frame, air_meter,velocity));

        MSL_C_PPCEABI_bare_H__sprintf(&this->current_air_prediction, "Distance: %f", predicted_swim_distance);
        MSL_C_PPCEABI_bare_H__sprintf(&this->max_air_prediction, "Distance (Max air): %f", predicted_swim_distance_max_air);

        //OSReport(MSL_C_PPCEABI_bare_H__printf("swim_predictor__draw: current_air_prediction = %f, %s | max_air_prediction = %f, %s\n",predicted_swim_distance, &this->current_air_prediction, predicted_swim_distance_max_air,&this->max_air_prediction));
        
        J2DTextBox__setString(this->current_air_prediction_display, &this->current_air_prediction);
        J2DTextBox__setString(this->max_air_prediction_display, &this->max_air_prediction);

        SetTextboxScale(this->title, 1.0f);
        SetTextboxScale(this->current_air_prediction_display, predict_text_font_size);
        SetTextboxScale(this->max_air_prediction_display, predict_text_font_size);

        text_color_pallete *pallete = &TEXT_PALLETE_WHITE;
        SetTextboxPallete(this->title, pallete);
        SetTextboxPallete(this->current_air_prediction_display, pallete);
        SetTextboxPallete(this->max_air_prediction_display, pallete);

        J2DTextBox__draw(this->title, predict_text_xOffset, predict_text_yOffset, predict_text_width,2); //2 = hbinding left
        J2DTextBox__draw(this->current_air_prediction_display, predict_text_xOffset, predict_text_yOffset + 15.0f, predict_text_width,2); //2 = hbinding left
        J2DTextBox__draw(this->max_air_prediction_display, predict_text_xOffset, predict_text_yOffset + 30.0f, predict_text_width,2); //2 = hbinding left
    }

}

//approximate total distance to swim assuming perfect ess
float predict_max_swim_distance(float velocity, float animation_frame, int air_meter){
    float total_distance = 0.0f;
    float ess_accel_rate = 1.0f/6.0f;
    while(air_meter > 0)
    {
        float true_v = calc_true_velocity(velocity, animation_frame, air_meter);
        total_distance += true_v;
        velocity -= ess_accel_rate; //get next velocity
        air_meter -= 1;
        if(velocity < 0){
            break;
        }
        float animation_increment = calc_animation_frame_increment(velocity,air_meter);
        //calc next animation frame
        animation_frame += animation_increment;
        if(animation_frame >= 23.0f){
            animation_frame -= 23.0f;
        }      
    }
    return total_distance;
}

//calculate animation frame based on speed + air
float calc_animation_frame_increment(float velocity, int air){
    float p1 = MSL_C_PPCEABI_bare_H__abs(velocity) / 36.0f;
    float p2 = 0.6f; //3/5
    float p3 = ((float)(air + 1)) / 900.0f;
    return p1 + p2 + 1.0f - p3;
}

//calculate actual displacement in water
float calc_true_velocity(float velocity, float animation_frame, int air){
    float true_v = calc_v_loss_from_animation_frame(velocity, animation_frame);
    return calc_v_loss_from_air(true_v, air);
}

//calculate amount drag from animation frame with head lower in water from animation
float calc_v_loss_from_animation_frame(float velocity, float animation_frame){
    float p1 = ((2.0 * velocity) / 5.0);
    float p2 = MSL_C_PPCEABI_bare_H__cosf((PI * animation_frame) / 23.0);
    if(p2 < 0.0f){
        p2 = p2 * -1.0f;
    }
    float p3 = ((3.0 * velocity) / 5.0);
    return p1 * p2 + p3;
}

//calculate amount of drag from link lower head in water from air meter
float calc_v_loss_from_air(float velocity, int air){
    return ((-17994.0 / 7.0) * velocity) / ((float)air - 3471.0 + (3.0 / 7.0));
}

#endif