#ifndef INVENTORY_BASE_H_INCLUDED
#define INVENTORY_BASE_H_INCLUDED

typedef struct inventory_base inventory_base;
typedef struct inventory_base_vtbl inventory_base_vtbl;

struct inventory_base {
    inventory_base_vtbl *vptr;
    base_pane *parent;
    int item_index;
    int item_count;
    int *items;
    J2DPicture *pictures;

    float x_offset;
    float y_offset;
};

struct inventory_base_vtbl {
    void (*init)(inventory_base *this, base_pane *pane);
    void (*update_data)(inventory_base *this);
    void (*update_inventory)(inventory_base *this);
    void (*draw)(inventory_base *this, float scale);
    void (*execute)(inventory_base *this);
};

void inventory_base__init(inventory_base *this, base_pane *pane);
void inventory_base__update_data(inventory_base *this);
void inventory_base__update_inventory(inventory_base *this);
void inventory_base__draw(inventory_base *this, float scale);
void inventory_base__execute(inventory_base *this);
char* inventory_base__getIconFilenameByIndex(inventory_base *this, int index);
char* inventory_base__getIconFilename(inventory_base *this);

#endif
