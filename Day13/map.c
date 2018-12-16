#include "map.h"

/* Read the input line by line and populate map and carts. */
void read_input(FILE *fp, char **map, CartPtr *carts)
{
    int i, j, k = 0;
    char c;
    
    for (i = 0; i < MAPSIZE; i++) {
        for (j = 0; j < MAPSIZE; j++) {
            c = fgetc(fp);

            /* End of line. */
            if (c == '\n' || c == EOF)
                break;

            /* Cart. */
            if (c == '^' || c == '>' || c == 'v' || c == '<') {
                carts[k] = malloc(sizeof(Cart));
                carts[k]->i = i;
                carts[k]->j = j;
                carts[k]->moved = false;
                carts[k]->turn = left;
                switch (c)
                {
                    case '^':
                    carts[k]->direction = north;
                    break;
                    case '>':
                    carts[k]->direction = east;
                    break;
                    case 'v':
                    carts[k]->direction = south;
                    break;
                    case '<':
                    carts[k]->direction = west;
                    break;
                }

                k++;

                /* Put underlying map section. */
                if (c == '^' || c == 'v')
                    map[i][j] = '|';
                if (c == '>' || c == '<')
                    map[i][j] = '-';
            }

            /* Map section. */
            if (c == '|' || c == '/' || c == '-' || c == '\\' || c == '+') {
                map[i][j] = c;
            }
        }
    }

    fclose(fp);
}


void print_map(char **map)
{
    int i, j;
    for (i = 0; i < MAPSIZE; i++) {
        for (j = 0; j < MAPSIZE; j++) {
            putc(map[i][j], stdout);
        }
        putc('\n', stdout);
    }
}


void print_mapcarts(char **map, CartPtr *carts)
{
    int i, j, k;

    char **temp_map = calloc(MAPSIZE, sizeof(char *));
    for (i = 0; i < MAPSIZE; i++) {
        temp_map[i] = calloc(MAPSIZE, sizeof(char));
        strcpy(temp_map[i], map[i]);
    }

    char direction;
    CartPtr cart;
    k = 0;
    while ((cart = carts[k]) != NULL) {
        switch (cart->direction)
        {
            case north:
                direction = '^';
                break;
            case east:
                direction = '>';
                break;
            case south:
                direction = 'v';
                break;
            case west:
                direction = '<';
                break;
        }
        temp_map[cart->i][cart->j] = direction;
        k++;
    }

    for (i = 0; i < MAPSIZE; i++) {
        for (j = 0; j < MAPSIZE; j++) {
            putc(temp_map[i][j], stdout);
        }
        putc('\n', stdout);
    }

}

/* Returns pointer to the next available cart. Carts move in order
 * starting from the topmost, then leftmost. If no available cart
 * remains to move, return null pointer. */
CartPtr next_cart(CartPtr *carts)
{
    CartPtr min_cart = NULL;
    int min_i = MAPSIZE;
    int min_j = MAPSIZE;

    CartPtr cart;
    int k = 0;
    while ((cart = carts[k]) != NULL) {
        if (cart->moved != true) {

            if (cart->i < min_i) {
                min_cart = cart;
                min_i = cart->i;
                min_j = cart->j;
            } else if (cart->i == min_i) {
                if (cart->j < min_j) {
                    min_cart = cart;
                    min_i = cart->i;
                    min_j = cart->j;
                }
            }
        }
        k++;
    }
    return min_cart;
}

/* Returns a pointer to the cart that is present in the same
 * location as the target cart; NULL otherwise. */
CartPtr collision(CartPtr cart, CartPtr *carts)
{
    int k;
    CartPtr other_cart;
    
    for (k = 0; k < MAXCART && carts[k] != NULL; k++) {
        if (carts[k] != cart) {
            if ((carts[k]->i == cart->i) && (carts[k]->j == cart->j))
                return carts[k];
        }
    }
    return NULL;
}

/* Advances carts by one tick. */
void update(char **map, CartPtr *carts)
{

    int i, j, k;
    CartPtr cart;

    /* Refresh all cart movements. */
    for (k = 0; k < MAXCART && carts[k] != NULL; k++) {
        carts[k]->moved = false;
    }

    while ((cart = next_cart(carts)) != NULL) {

        /* Move cart according to its orientation. */
        switch (cart->direction)
        {
            case north:
                cart->i--;
                break;
            case east:
                cart->j++;
                break;
            case south:
                cart->i++;
                break;
            case west:
                cart->j--;
                break;
        }
        
        /* Check for collisions first. */
        if (collision(cart, carts) != NULL) {
            printf("Detected collision at X = %d, Y = %d.\n", cart->j, cart->i);
            break;
        }

        /* Re-orient, if we are at a bend. */
        if (map[cart->i][cart->j] == '/') {
            switch (cart->direction)
            {
                case north:
                    cart->direction = east;
                    break;
                case east:
                    cart->direction = north;
                    break;
                case south:
                    cart->direction = west;
                    break;
                case west:
                    cart->direction = south;
                    break;
            }
        } else if (map[cart->i][cart->j] == '\\') {
            switch (cart->direction)
            {
                case north:
                    cart->direction = west;
                    break;
                case east:
                    cart->direction = south;
                    break;
                case south:
                    cart->direction = east;
                    break;
                case west:
                    cart->direction = north;
                    break;
            }
        }

        /* Choose next direction, if we are at an intersection. */
        if (map[cart->i][cart->j] == '+') {
            switch (cart->turn)
            {
                case left:
                    cart->direction = (cart->direction - 1) % 4;
                    break;
                case straight:
                    break;
                case right:
                    cart->direction = (cart->direction + 1) % 4;
                    break;
            }

            /* Increment turn order. */
            cart->turn = (cart->turn + 1) % 3;
        }

        /* Finally, mark as moved. */
        cart->moved = true;
    }
    
}
