#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/time.h"

typedef struct item {
  float weight;
  float normalized_weight;
  char *name;
} item;

int main(int argc, char** argv) {
  if (argc <= 1) {
    fprintf(stderr, "You must pass arguments $weight:$name e.g. %s 1:rare 2:not-rare 10:super-common\n", argv[0]);
    return 1;
  } else {
    int count_of_drops = argc - 1;
    item** drop_tables = (item **)malloc(sizeof(item *) * (count_of_drops));
    float sum_of_weights = 0.0;
    int i = 0;

    for (i=0; i<count_of_drops; i++) {
      char *weight = strtok(argv[i + 1], ":");
      char *name = strtok(NULL, ":");
      if (weight && name) {
        drop_tables[i] = (item *)malloc(sizeof(item *));
        drop_tables[i]->weight = atof(weight);
        drop_tables[i]->normalized_weight = 0.0;
        drop_tables[i]->name = name;

        sum_of_weights += drop_tables[i]->weight;
      }
    }

    for (i=0; i<count_of_drops; i++) {
      drop_tables[i]->normalized_weight = drop_tables[i]->weight / sum_of_weights;
    }

    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);

    float random_drop = (float)rand() / RAND_MAX;

    int dropped = -1;
    float cursor = 0.0;

    for (i=0; i<count_of_drops; i++) {
      if (i == (count_of_drops - 1)) {
        dropped = i;
        break;
      } else {
        if ((random_drop >= cursor) && random_drop < (cursor + drop_tables[i]->normalized_weight)) {
          dropped = i;
          break;
        }

        cursor += drop_tables[i]->normalized_weight;
      }
    }

    printf("dice-role: %f, you just got of %d %s %f %f\n", random_drop, dropped, drop_tables[dropped]->name, drop_tables[dropped]->weight, drop_tables[dropped]->normalized_weight);

    return 0;
  }
}
