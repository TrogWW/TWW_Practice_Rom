#ifndef DVDTHD_PHASE_HANDLER_H_INCLUDED
#define DVDTHD_PHASE_HANDLER_H_INCLUDED

typedef struct DvdThd_PhaseHandlerList{
    JSUPtrList list;
} DvdThd_PhaseHandlerList;

typedef struct DvdThd_PhaseHandler {
	 void *data;
	 request_of_phase_process_class request_of_phase; 
     bool complete;
	 void *object;
     int (**phase_list)(void *);
} DvdThd_PhaseHandler;
DvdThd_PhaseHandlerList__append(DvdThd_PhaseHandlerList *this, DvdThd_PhaseHandler *phase_handler);
DvdThd_PhaseHandlerList__execute(DvdThd_PhaseHandlerList *this);

DvdThd_PhaseHandler__new(DvdThd_PhaseHandler *this, int (*phase_list[])(void *), void *object);


#endif