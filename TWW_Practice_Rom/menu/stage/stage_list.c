#ifndef STAGE_LIST_C_INCLUDED
#define STAGE_LIST_C_INCLUDED


#include "stage_list.h"
#include "../../helpers/stringhelpers.c"
#include "stage.c"

void stage_list__new(stage_list *this){
    JSUPtrList__JSUPtrList(&this->stages,true);
}
void stage_list__loadFromDVD(stage_list *this){

    int directory[5];
    int directory_info[12];
    bool stageDir = (bool)dvd__DVDOpenDir("/res/Stage",&directory);

    bool readDir = true;
    int i = 0;

    char* stage_directory_base = "/res/Stage/";
    char stage_directory[25];

    while(readDir == true){
        readDir = (bool)dvd__DVDReadDir(directory, &directory_info);


        char* stage_name = (char*)directory_info[2];

        stage *s = (stage *)JKernel__operator_new(sizeof(stage));
        stage__new(s, stage_name);

        MSL_C_PPCEABI_bare_H__strcpy(stage_directory, stage_directory_base);
        MSL_C_PPCEABI_bare_H__strcat(stage_directory, stage_name);

        //OSReport(MSL_C_PPCEABI_bare_H__printf("load_stages: i: %d | stage_directory %s\n",i, stage_directory));
        int sub_directory[5];
        int sub_directory_info[12];
        char file_name[25];
        //char room_no[25];

        bool sub_directory_read = (bool)dvd__DVDOpenDir(stage_directory,&sub_directory);
        while(sub_directory_read == true){
            sub_directory_read = (bool)dvd__DVDReadDir(sub_directory, &sub_directory_info);

            MSL_C_PPCEABI_bare_H__strcpy(file_name, (char*)sub_directory_info[2]);
            if(str_starts_with("Room",file_name)){
                char *room_no = str_extract_int(file_name);
                if(room_no){
                    //int room_number_int = atoi(room_no);
                    //OSReport(MSL_C_PPCEABI_bare_H__printf("VALID_ROOM_NUMBER %s | room_number_int: %d\n", room_no, room_number_int));
                    stage_append_room(s, room_no);
                }    
                else{
                    //OSReport(MSL_C_PPCEABI_bare_H__printf("INVALID ROOM NUMBER!!\n"));
                } 
            }           
      
        }
        //OSReport(MSL_C_PPCEABI_bare_H__printf("stage_name: %s | room_count: %d\n", s->stage_name, s->rooms.mCount));
        //rooms found for stage, add to stage list
        if(s->rooms.mCount > 0){
            stage_list__append_stage(this, s);
        }

        dvd__DVDCloseDir(&sub_directory);
    }
    dvd__DVDCloseDir(&directory);
    //OSReport(MSL_C_PPCEABI_bare_H__printf("this->stages.mCount: %d\n", this->stages.mCount));
}
void stage_list__append_stage(stage_list *this, stage *s){
    JSUPtrLink *stage_item = (JSUPtrLink *)JKernel__operator_new(sizeof(JSUPtrLink));
    JSUPtrLink__JSUPtrLink(stage_item, s);
    JSUPtrList__append(&this->stages,stage_item);
}

#endif