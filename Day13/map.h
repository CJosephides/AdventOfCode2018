#ifndef _H_MAP
#define _H_MAP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAPSIZE 175
#define MAXCART 30

enum boolean { false, true };
enum orientation { north, east, south, west };
enum intersection { left, straight, right };

typedef struct cart {
    int i;
    int j;
    enum orientation direction; 
    enum boolean moved;
    enum intersection turn;

} Cart, *CartPtr;

void read_input(FILE *fp, char **map, CartPtr *carts);
void print_map(char **map);
void print_mapcarts(char **map, CartPtr *carts);
CartPtr next_cart(CartPtr *carts);
CartPtr collision(CartPtr cart, CartPtr *carts);
void update(char **map, CartPtr *carts);

#endif
