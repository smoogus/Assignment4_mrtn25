#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index);
void free_items(Item *item_list, int size);
double average_price(Item *item_list, int size);
void print_items(Item *item_list, int size);

void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index)
{
  item_list[index].price = price;

  //* +1 for the null terminator *
  item_list[index].sku = malloc(strlen(sku) + 1);
  strcpy(item_list[index].sku, sku);

  item_list[index].category = malloc(strlen(category) + 1);
  strcpy(item_list[index].category, category);

  item_list[index].name = malloc(strlen(name) + 1);
  strcpy(item_list[index].name, name);
}

void print_items(Item *item_list, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("###############\n");
    printf("item name = %s\n", item_list[i].name);
    printf("item sku = %s\n", item_list[i].sku);
    printf("item category = %s\n", item_list[i].category);
    printf("item price = %f\n", item_list[i].price);
  }
}

double average_price(Item *item_list, int size)
{
  double total = 0.0;
  for (int i = 0; i < size; i++)
  {
    total += item_list[i].price;
  }
  return total / size;
}

//* Frees each string inside every Item, then the array itself.
void free_items(Item *item_list, int size)
{
  for (int i = 0; i < size; i++)
  {
    free(item_list[i].sku);
    free(item_list[i].category);
    free(item_list[i].name);
  }
  free(item_list);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s <sku>\n", argv[0]);
    return 1;
  }
  char *sku = argv[1];

  int size = 5;
  Item *item_list = malloc(size * sizeof(Item));

  add_item(item_list, 5.00, "19282", "breakfast", "reese's cereal", 0);
  add_item(item_list, 3.95, "79862", "dairy", "milk", 1);
  add_item(item_list, 2.49, "14512", "produce", "bananas", 2);
  add_item(item_list, 4.25, "33901", "bakery", "sourdough bread", 3);
  add_item(item_list, 7.80, "50126", "meat", "chicken breast", 4);

  print_items(item_list, size);
  printf("###############\n");
  printf("average price of items = %f\n", average_price(item_list, size));

  // Step 4: search by SKU. Bounds check comes FIRST (short-circuit). 
  int ct = 0;
  while (ct < size && strcmp(item_list[ct].sku, sku) != 0)
  {
    ct++;
  }

  printf("\nSearching for SKU %s...\n", sku);
  if (ct < size)
  {
    printf("###############\n");
    printf("item name = %s\n", item_list[ct].name);
    printf("item sku = %s\n", item_list[ct].sku);
    printf("item category = %s\n", item_list[ct].category);
    printf("item price = %f\n", item_list[ct].price);
  }
  else
  {
    printf("item not found\n");
  }

  free_items(item_list, size);
  return 0;
}

