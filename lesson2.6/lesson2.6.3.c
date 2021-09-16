#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

enum move_dir { MD_UP, MD_RIGHT, MD_DOWN, MD_LEFT, MD_NONE };

struct move_callback_node {
   void (*func)(enum move_dir);
   struct move_callback_node* next;
};

struct move_callback_node* move_callback_node_create( void (*func)(enum move_dir) ) {
  struct move_callback_node* node = malloc(sizeof(struct move_callback_node));
    if (node) {
        node->func = func;
        node->next = NULL;
    }
    return node;
}

void move_callback_node_add_front(struct move_callback_node** old, void (*func)(enum move_dir) ) {
    struct move_callback_node* new_node = move_callback_node_create(func);
    if (new_node) {
        new_node->next = *old;
        *old = new_node;
    }
}

size_t move_callback_chain_length(const struct move_callback_node* list ) {
    size_t len = 0;
    while(list != NULL) {
        ++len;
        list = list->next;
    }
    return len;
}

struct move_callback_node* move_callback_chain_get_pre_last(struct move_callback_node* list) {
    struct move_callback_node* pre_last = NULL;
    struct move_callback_node* last = NULL;
    while(list != NULL) {
        pre_last = last;
        last = list;
        list = list->next;
    }
    return pre_last;
}

void move_callback_chain_destroy_last(struct move_callback_node** list) {
    struct move_callback_node* pre_last = move_callback_chain_get_pre_last(*list);
    if (pre_last != NULL) {
        free(pre_last->next);
        pre_last->next = NULL;
    } else {
        free(*list);
        *list = NULL;
    }
}

void move_callback_chain_destroy( struct move_callback_node* list ) {
    while(list != NULL) {
        move_callback_chain_destroy_last(&list);
    }
}

struct move_callback_node* move_callback_chain_last(struct move_callback_node* list) {
    struct move_callback_node* last = NULL;
    while(list != NULL) {
        last = list;
        list = list->next;
    }
    return last;
}

void move_callback_chain_add_back( struct move_callback_node** old, void (*func)(enum move_dir) ) {
    struct move_callback_node* last_node = move_callback_chain_last(*old);
    struct move_callback_node* new_node = move_callback_node_create(func);
    if (last_node != NULL)
        last_node->next = new_node;
    else
        *old = new_node;
}

void move_callback_chain_run(struct move_callback_node* node, enum move_dir direction) {
  while(node != NULL) {
    node->func(direction);
    node = node->next;
  }
}

// Робот и его callback'и
// callback'ов может быть неограниченное количество
struct robot {
  const char* name;
  struct move_callback_node* move_callbacks;
};

// Добавить callback к роботу, чтобы он вызывался при движении
// В callback будет передаваться направление движения
void register_callback(struct robot* robot, void (*new_cb)(enum move_dir)) {
  struct move_callback_node** chain_start = &(robot->move_callbacks);
  move_callback_node_add_front(chain_start, new_cb);
}

// Отменить все подписки на события.
// Это нужно чтобы освободить зарезервированные ресурсы
// например, выделенную в куче память
void unregister_all_callbacks(struct robot* robot) {
    move_callback_chain_destroy(robot->move_callbacks);
}

// Вызывается когда робот движется
// Эта функция должна вызвать все обработчики событий
void move(struct robot* robot, enum move_dir dir) {
  struct move_callback_node* chain_start = robot->move_callbacks;
  move_callback_chain_run(chain_start, dir);
}