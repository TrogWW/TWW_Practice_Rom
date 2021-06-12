#pragma region _input_defines
    #ifndef _WW_DEFINES_H
        #define _WW_DEFINES_H "../WW_Hacking_API/vanilla_defines/ww_defines.h"
        #include _WW_DEFINES_H
    #endif
    #ifndef _WW_FUNCTIONS_H
        #define _WW_FUNCTIONS_H "../WW_Hacking_API/vanilla_defines/ww_functions.h"
        #include _WW_FUNCTIONS_H
    #endif
#pragma endregion _input_defines

#include "settings.h"
#include "input.h"
#include "menu/load_menu_context.c"
#include "menu/menu_pane.c"
#include "DvdThd_PhaseHandler.c"
#include "tools/wiird_loader_context.c"


void _menu_exec(Settings* settings){

    if(code_list.load_wiird_code_handler.object == 0){
        DvdThd_PhaseHandler__new(&code_list.load_wiird_code_handler,&wiird_loader_phases, &code_list);
        //DvdThd_PhaseHandlerList__append(&PHASE_HANDLER_LIST, &code_list.load_wiird_code_handler);
    }
    // else{     
    //     if(code_list.load_wiird_code_handler.complete){
    //         wiird__execute();
    //     }
    // }
    // if(memcard.memcard_handler.object == 0){
    //     DvdThd_PhaseHandler__new(&memcard.memcard_handler,&memcard_boot, &memcard);
    //     DvdThd_PhaseHandlerList__append(&PHASE_HANDLER_LIST, &memcard.memcard_handler);
    // }
    if(load_menu_arc_handler.object == 0){
        OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: loading menu\n"));
        DvdThd_PhaseHandler__new(&load_menu_arc_handler,&load_menu_arc_phases, &load_menu_arc_handler);
        DvdThd_PhaseHandlerList__append(&PHASE_HANDLER_LIST, &load_menu_arc_handler);
    }
    else{
        if(load_menu_arc_handler.complete){
            if(main_pane.active == false){
                if(Two_Inputs_Pressed(&DIGITAL_INPUTS[X], &DIGITAL_INPUTS[D_PAD_LEFT])){
                    menu_pane__open(&main_pane);
                    WATCHES_DISPLAY_UI.base.vptr->close(&WATCHES_DISPLAY_UI); 
                }
            }
            else{
                if(DIGITAL_INPUTS[B].pressed){                
                    menu_pane__close(&main_pane);
                }
            }
            if(main_pane.active){
                menu_pane__update_dDlst(&main_pane);
            }
            else{
                if(WATCHES_DISPLAY_UI.watches_list.mCount > 0){
                   watches_display_pane__update_dDlst(&WATCHES_DISPLAY_UI); 
                }
                
                //watches_display_pane__draw(&WATCHES_DISPLAY_UI);
            }
            // else{
            //     void *savedata = (void *)0x803C4C08;
            //     int savedata_len = 23828;
            //     if(DIGITAL_INPUTS[Z].pressed){
            //         //memcard_context__save_data(&memcard, test_data, MSL_C_PPCEABI_bare_H__strlen(test_data),0);
            //         memcard_context__save_data(&memcard, &memcard_savestate_data_list);
            //     }
            //     else if(DIGITAL_INPUTS[R].pressed){
            //         memcard_context__read_data(&memcard, &memcard_savestate_data_list);
            //     }
            // }
        }
    }

}




// card_errors read_from_memcard(card_file *file, void *data, uint len, uint offset){
//     uint buffer_size = 0x2000;
//     //cLib_memSet(&m_Do_MemCardRWmng__sTmpBuf,0,0x2000); //clear buffer
//     if(offset + buffer_size > len){
//         buffer_size = len - offset;
//     }
    
//     card_errors card_read_status = card__CARDRead(file,&m_Do_MemCardRWmng__sTmpBuf2,buffer_size,offset);

//     void * read_address = (void *)(((int)data) + offset);
//     OSReport(MSL_C_PPCEABI_bare_H__printf("read_from_memcard: card_read_status %X | len = %d | buffer_size = %d | offset = %d | read_address = %X\n", card_read_status, len, buffer_size,offset, read_address));
//     copy_bytes(read_address, &m_Do_MemCardRWmng__sTmpBuf2,buffer_size);

//     if(card_read_status == card_errors__CARD_ERROR_READY){
//         uint new_offset = buffer_size + offset;
//         if(new_offset < len){
//             return read_from_memcard(file, data, len, new_offset);
//         }
//     }
//     return card_read_status;
    
// }
// //CARD_Write(card_file *file,void *buffer,u32 len
// card_errors write_to_memcard(card_file *file, void *data, uint len, uint offset){
//     uint buffer_size = 0x2000;
//     //cLib_memSet(&m_Do_MemCardRWmng__sTmpBuf,0,0x2000); //clear buffer
//     if(offset + buffer_size > len){
//         buffer_size = len - offset;
//     }
//     void * write_address = (void *)(((int)data) + offset);
//     copy_bytes(&m_Do_MemCardRWmng__sTmpBuf2,write_address,buffer_size);

//     //card_errors card_mount_status = card__CARDMount(SAVESTATE_MEMCARD, MemCardWorkArea0, 0);


//     // int *param_data[2];
//     // card_errors control_block_status = card____CARDGetControlBlock(SAVESTATE_MEMCARD, param_data); 
//     // OSReport(MSL_C_PPCEABI_bare_H__printf("write_to_memcard: CONTROL_BLOCK_STATUS = %X\n", control_block_status));

//     // if(control_block_status == card_errors__CARD_ERROR_NOFILE || control_block_status == card_errors__CARD_ERROR_NOCARD){
//     //     card_errors card_create_status = card__CARDCreate(SAVESTATE_MEMCARD,CARD_NAME,0x18000,file);
//     //     OSReport(MSL_C_PPCEABI_bare_H__printf("write_to_memcard: card_create_status = %X | file = %X\n",card_create_status, file));
//     //     if(card_create_status == card_errors__CARD_ERROR_EXIST){
//     //         card_errors card_open_status = card__CARDOpen(SAVESTATE_MEMCARD, CARD_NAME, file);
//     //         OSReport(MSL_C_PPCEABI_bare_H__printf("write_to_memcard: card_open_status = %X | file = %X\n",card_open_status, file));
//     //     }
//     //     return write_to_memcard(file,data,len,offset);
//     // }

//     card_errors card_create_status = card__CARDCreate(SAVESTATE_MEMCARD,CARD_NAME,0x18000,file);
//     OSReport(MSL_C_PPCEABI_bare_H__printf("write_to_memcard: card_create_status = %X | file = %X\n",card_create_status, file));
//     if(card_create_status == card_errors__CARD_ERROR_EXIST){
//         card_errors card_open_status = card__CARDOpen(SAVESTATE_MEMCARD, CARD_NAME, file);
//         OSReport(MSL_C_PPCEABI_bare_H__printf("write_to_memcard: card_open_status = %X | file = %X\n",card_open_status, file));
//     }
    
//     card_errors card_write_status = card__CARDWrite(file,&m_Do_MemCardRWmng__sTmpBuf2,buffer_size,offset);//sizeof(daPy_lk_c),sizeof(daPy_lk_c));

//     OSReport(MSL_C_PPCEABI_bare_H__printf("write_to_memcard: card_mount_status = %X | card_open_status = %X | card_write_status = %X | len = %d | buffer_size = %d | offset = %d | write_address = %X\n",0, 0, card_write_status, len, buffer_size,offset,write_address));
//     if(card_write_status == card_errors__CARD_ERROR_READY){
//         uint new_offset = buffer_size + offset;
//         if(new_offset < len){
//             return write_to_memcard(file, data, len, new_offset);
//         }
//     }
//     return card_write_status;
// }

                
// if(run_once == false && g_dComIfG_gameInfo.mPlay.mpLinkActor != 0){
//                     //card_errors card_status1 = card__CARDMount(SAVESTATE_MEMCARD, (void *)0x803a99a0, 0);
                    
//                     //cVar1 = card::CARDCheck((uint)*(byte *)&this->mCardSlot);

//                     if(format_once == false){
//                         card__CARDMount(SAVESTATE_MEMCARD, MemCardWorkArea0, 0);
//                         card__CARDInit();
//                         card_errors card_format_status = card__CARDFormat(SAVESTATE_MEMCARD);
//                         if(card_format_status != card_errors__CARD_ERROR_READY){
//                             return;
//                         }
//                         else{
//                             format_once = true;
//                         }
//                     }
//                     card_errors card_check_status = card__CARDCheck(SAVESTATE_MEMCARD);
//                     if(card_check_status != card_errors__CARD_ERROR_READY){
//                         OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: CHECK NOT READY card_check_status = %X\n", card_check_status));
//                         return;
//                     }


                    
//                     card_errors card_probe_status = card__CARDProbe(SAVESTATE_MEMCARD);
//                     OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: card_probe_status = %X\n", card_probe_status));
                    
//                     if(card_probe_status != card_errors__CARD_ERROR_UNLOCKED){
//                         OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: NOT UNLOCKED card_probe_status = %X\n", card_probe_status));
//                         return;
//                     }

//                     card_errors card_open_status = card__CARDOpen(SAVESTATE_MEMCARD, CARD_NAME, &file);

//                     if(card_open_status == card_errors__CARD_ERROR_NOFILE){
//                         //card_errors card::CARDCreate(int card_slot,char *filename,int size,card_file *file)
//                         //card_errors card__CARDCreate(int card_slot, char * filename, int size, card_file * file);
//                         card_errors card_create_status = card__CARDCreate(SAVESTATE_MEMCARD,CARD_NAME,0x18000,&file);
//                         OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: card_open_status = %X | card_create_status = %X | file = %X\n",card_open_status,card_create_status, &file));
//                     }
//                     if(card_open_status == card_errors__CARD_ERROR_READY){
//                         card_errors card_write_status2 = card__CARDWrite(&file, &m_Do_MemCardRWmng__sTmpBuf2,0x2000,0);
//                     //card_errors card_free_blocks_status = card__CARDFreeBlocks(1, &file, &blocks);

//                         OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: card_write_status2 = %X | card_open_status = %X | file = %X\n", card_write_status2, card_open_status, &file));
//                         run_once = true;
//                         // card__CARDUnmount(SAVESTATE_MEMCARD);
//                         //card__CARDClose(&file);
//                     }
//                 }
//                 else if(DIGITAL_INPUTS[D_PAD_DOWN].pressed && g_dComIfG_gameInfo.mPlay.mpLinkActor != 0){

//                     //card_errors card____CARDGetControlBlock(int param_1, int * * param_2);

//                     //card__CARDMount(SAVESTATE_MEMCARD, MemCardWorkArea0, 0);
                    
//                     card_errors card_write_status = write_to_memcard(&file,&g_dComIfG_gameInfo.mPlay.mpLinkActor->parent.parent,sizeof(fopAc_ac_c),0);
                    
//                     if(card_write_status == card_errors__CARD_ERROR_READY){
//                         // card__CARDUnmount(SAVESTATE_MEMCARD);
//                         // card__CARDClose(&file);
//                         //card_errors card_close_status = card__CARDClose(&file);
//                         //OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: card_close_status = %X | file = %X\n",card_close_status, &file));
//                     }
//                 }
//                 else if(DIGITAL_INPUTS[D_PAD_UP].pressed && g_dComIfG_gameInfo.mPlay.mpLinkActor != 0){
//                     //card__CARDMount(SAVESTATE_MEMCARD, MemCardWorkArea0, 0);
//                     card_errors card_open_status = card__CARDOpen(SAVESTATE_MEMCARD, CARD_NAME, &file);
//                     card_errors card_read_status = read_from_memcard(&file,&g_dComIfG_gameInfo.mPlay.mpLinkActor->parent.parent,sizeof(fopAc_ac_c),0);
                    
//                     if(card_read_status == card_errors__CARD_ERROR_READY){
//                         // card__CARDUnmount(SAVESTATE_MEMCARD);
//                         // card__CARDClose(&file);
//                         //card_errors card_close_status = card__CARDClose(&file);
//                         //OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: card_close_status = %X | file = %X\n",card_close_status, &file));
//                     }
//                 }





                        //cLib_memSet(&m_Do_MemCardRWmng__sTmpBuf,0,0x2000);


                        // card_errors card_read_status = card__CARDRead(&file,&m_Do_MemCardRWmng__sTmpBuf,0x2000,0x2000);
                        // return;


                        //m_Do_MemCardRWmng__mDoMemCdRWm_BuildHeader(&m_Do_MemCardRWmng__sTmpBuf);
                        
                        //card::CARDWrite(param_1,&sTmpBuf,0x2000,0x2000)
                        //card_errors card__CARDWrite(undefined4 file, undefined4 buffer, uint len, uint offset);
                        //dComIfG_inf_c g_dComIfG_gameInfo;

                        //size_t hello_size = MSL_C_PPCEABI_bare_H__strlen(hello);
                        //OSReport(MSL_C_PPCEABI_bare_H__printf("hello size = %d\n",hello_size));
                        //MSL_C_PPCEABI_bare_H__memcmp(&m_Do_MemCardRWmng__sTmpBuf, hello, hello_size);


                                                //copy_bytes(sTmpBuf2,g_dComIfG_gameInfo.mPlay.mpLinkActor,0x2000);
                        //card_errors card_write_status2 = card__CARDWrite(&file,sTmpBuf2,0x4000,0x2000);//sizeof(daPy_lk_c),sizeof(daPy_lk_c));


                                                //card_errors card_read_status = card__CARDRead(&file,&m_Do_MemCardRWmng__sTmpBuf,0x2000,0);

                        //copy_bytes(&m_Do_MemCardRWmng__sTmpBuf,g_dComIfG_gameInfo.mPlay.mpLinkActor,0x2000);

                        //card_errors card_write_status2 = card__CARDWrite(&file,&m_Do_MemCardRWmng__sTmpBuf,0x4000,0x2000);//sizeof(daPy_lk_c),sizeof(daPy_lk_c));
                        //card_read_status = card__CARDRead(&file,&m_Do_MemCardRWmng__sTmpBuf,0x4000,0x2000);


                                            //card_errors card::CARDFreeBlocks(int card_slot,int *param_2,int *param_3)
                    //undefined card__CARDFreeBlocks(int card_slot, undefined4 param_2, undefined4 param_3);

                    //card_errors card__CARDOpen(int card_slot, char * filename, card_file * file);


                    //  MSL_C_PPCEABI_bare_H__sprintf(&m_Do_MemCardRWmng__sTmpBuf, "Hello World");
                    //     OSReport(MSL_C_PPCEABI_bare_H__printf("hello AFTER COPY = %s | sizeof(daPy_lk_c) = %d\n",&m_Do_MemCardRWmng__sTmpBuf,sizeof(daPy_lk_c)));
                    //     //m_Do_MemCardRWmng__sTmpBuf = "Hello World";
                    //     card_errors card_write_status = card__CARDWrite(&file,&m_Do_MemCardRWmng__sTmpBuf,0x2000,0x2000);//sizeof(daPy_lk_c),sizeof(daPy_lk_c));

                    //     card_errors card_read_status = card__CARDRead(&file,&m_Do_MemCardRWmng__sTmpBuf,0x2000,0x2000);

                    //     card_errors card_close_status = card__CARDClose(&file);
                    //     card__CARDUnmount(1);

                    //     OSReport(MSL_C_PPCEABI_bare_H__printf("_menu_exec: writing m_Do_MemCardRWmng__sTmpBuf = %X | card_write_status = %X | card_write_status2 = %X | card_read_status = %X\n",&m_Do_MemCardRWmng__sTmpBuf, card_write_status, 0, card_read_status));