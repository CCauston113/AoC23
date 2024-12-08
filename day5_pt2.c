#include "tools.h"

static int seeds_length = 0;
static int num_seeds_soil = 0;
static int num_soil_fertiliser = 0;
static int num_fertiliser_water = 0;
static int num_water_light = 0;
static int num_light_temp = 0;
static int num_temp_humidity = 0;
static int num_humidity_location = 0;

struct map
{
  long int dest_start;
  long int src_start;
  long int range_length;
};

long int use_map(struct map map_array[], int map_length, long int num_to_convert)
{
  for (int i = 0; i < map_length; i++)
  {
    if (num_to_convert >= map_array[i].src_start && num_to_convert < map_array[i].src_start + map_array[i].range_length)
    {
      long int diff = num_to_convert - map_array[i].src_start;
      return map_array[i].dest_start + diff;
    }
  }
  return num_to_convert;
}

void read_maps(FILE *file, long int seeds[], struct map seeds_soil[], struct map soil_fertiliser[], struct map fertiliser_water[], struct map water_light[], struct map light_temp[], struct map temp_humidity[], struct map humidity_location[])
{
  long int temp_map[3];

  uint8_t line[210];
  fgets(line, 210, file);
  pull_long_nums_to_array(line, 0, seeds, seeds_length);

  fgets(line, 210, file);
  fgets(line, 210, file);

  for (int i = 0; i < num_seeds_soil; i++)
  {
    fgets(line, 210, file);
    pull_long_nums_to_array(line, 0, temp_map, 3);
    seeds_soil[i].dest_start = temp_map[0];
    seeds_soil[i].src_start = temp_map[1];
    seeds_soil[i].range_length = temp_map[2];
  }

  fgets(line, 210, file);
  fgets(line, 210, file);

  for (int i = 0; i < num_soil_fertiliser; i++)
  {
    fgets(line, 210, file);
    pull_long_nums_to_array(line, 0, temp_map, 3);
    soil_fertiliser[i].dest_start = temp_map[0];
    soil_fertiliser[i].src_start = temp_map[1];
    soil_fertiliser[i].range_length = temp_map[2];
  }

  fgets(line, 210, file);
  fgets(line, 210, file);

  for (int i = 0; i < num_fertiliser_water; i++)
  {
    fgets(line, 210, file);
    pull_long_nums_to_array(line, 0, temp_map, 3);
    fertiliser_water[i].dest_start = temp_map[0];
    fertiliser_water[i].src_start = temp_map[1];
    fertiliser_water[i].range_length = temp_map[2];
  }

  fgets(line, 210, file);
  fgets(line, 210, file);

  for (int i = 0; i < num_water_light; i++)
  {
    fgets(line, 210, file);
    pull_long_nums_to_array(line, 0, temp_map, 3);
    water_light[i].dest_start = temp_map[0];
    water_light[i].src_start = temp_map[1];
    water_light[i].range_length = temp_map[2];
  }

  fgets(line, 210, file);
  fgets(line, 210, file);

  for (int i = 0; i < num_light_temp; i++)
  {
    fgets(line, 210, file);
    pull_long_nums_to_array(line, 0, temp_map, 3);
    light_temp[i].dest_start = temp_map[0];
    light_temp[i].src_start = temp_map[1];
    light_temp[i].range_length = temp_map[2];
  }

  fgets(line, 210, file);
  fgets(line, 210, file);

  for (int i = 0; i < num_temp_humidity; i++)
  {
    fgets(line, 210, file);
    pull_long_nums_to_array(line, 0, temp_map, 3);
    temp_humidity[i].dest_start = temp_map[0];
    temp_humidity[i].src_start = temp_map[1];
    temp_humidity[i].range_length = temp_map[2];
  }

  fgets(line, 210, file);
  fgets(line, 210, file);

  for (int i = 0; i < num_humidity_location; i++)
  {
    fgets(line, 210, file);
    pull_long_nums_to_array(line, 0, temp_map, 3);
    humidity_location[i].dest_start = temp_map[0];
    humidity_location[i].src_start = temp_map[1];
    humidity_location[i].range_length = temp_map[2];
  }
}

void count_maps(FILE *file, uint8_t *line)
{
  fgets(line, 210, file);
  while (fgets(line, 210, file))
  {
    if (memcmp(line, "\n", 1) == 0)
    {
      break;
    }
    else
    {
      num_seeds_soil++;
    }
  }

  fgets(line, 210, file);
  while (fgets(line, 210, file))
  {
    if (memcmp(line, "\n", 1) == 0)
    {
      break;
    }
    else
    {
      num_soil_fertiliser++;
    }
  }

  fgets(line, 210, file);
  while (fgets(line, 210, file))
  {
    if (memcmp(line, "\n", 1) == 0)
    {
      break;
    }
    else
    {
      num_fertiliser_water++;
    }
  }

  fgets(line, 210, file);
  while (fgets(line, 210, file))
  {
    if (memcmp(line, "\n", 1) == 0)
    {
      break;
    }
    else
    {
      num_water_light++;
    }
  }

  fgets(line, 210, file);
  while (fgets(line, 210, file))
  {
    if (memcmp(line, "\n", 1) == 0)
    {
      break;
    }
    else
    {
      num_light_temp++;
    }
  }

  fgets(line, 210, file);
  while (fgets(line, 210, file))
  {
    if (memcmp(line, "\n", 1) == 0)
    {
      break;
    }
    else
    {
      num_temp_humidity++;
    }
  }

  fgets(line, 210, file);
  while (fgets(line, 210, file))
  {
    if (memcmp(line, "\n", 1) == 0)
    {
      break;
    }
    else
    {
      num_humidity_location++;
    }
  }
}

int main()
{
  FILE *file = fopen("day5_input.txt", "r");
  if (file != NULL)
  {
    uint8_t line[210];
    fgets(line, 210, file);
    int pos = 0;
    while (line[pos] != '\n')
    {
      if (line[pos] == ' ')
      {
        seeds_length++;
      }
      pos++;
    }
    printf("There are %d seeds to check\r\n", seeds_length);

    fgets(line, 210, file);

    count_maps(file, line);

    fclose(file);
    // printf("Num seed soil maps = %d\r\n", num_seeds_soil);
    // printf("Num soil fertiliser maps = %d\r\n", num_soil_fertiliser);
    // printf("Num fertiliser water maps = %d\r\n", num_fertiliser_water);
    // printf("Num water light maps = %d\r\n", num_water_light);
    // printf("Num light temp maps = %d\r\n", num_light_temp);
    // printf("Num temp humidity maps = %d\r\n", num_temp_humidity);
    // printf("Num humidity location maps = %d\r\n", num_humidity_location);
  }

  long int seeds[seeds_length];
  struct map seeds_soil[num_seeds_soil];
  struct map soil_fertiliser[num_soil_fertiliser];
  struct map fertiliser_water[num_fertiliser_water];
  struct map water_light[num_water_light];
  struct map light_temp[num_light_temp];
  struct map temp_humidity[num_temp_humidity];
  struct map humidity_location[num_humidity_location];

  file = fopen("day5_input.txt", "r");
  if (file != NULL)
  {
    read_maps(file, seeds, seeds_soil, soil_fertiliser, fertiliser_water, water_light, light_temp, temp_humidity, humidity_location);
    fclose(file);
  }

  long int lowest_location = INT_MAX;
  for (int pair = 0; pair < seeds_length / 2; pair++)
  {
    //printf("seeds[pair * 2] = %ld, seeds[pair * 2] + 1 = %ld\r\n", seeds[pair * 2], seeds[pair * 2 + 1]);
    for (long int i = seeds[pair * 2]; i < seeds[pair * 2] + seeds[pair * 2 + 1]; i++)
    {
      //printf("Check seed %ld\r\n", i);
      long int soil = use_map(seeds_soil, num_seeds_soil, i);
      long int fertiliser = use_map(soil_fertiliser, num_soil_fertiliser, soil);
      long int water = use_map(fertiliser_water, num_fertiliser_water, fertiliser);
      long int light = use_map(water_light, num_water_light, water);
      long int temp = use_map(light_temp, num_light_temp, light);
      long int humidity = use_map(temp_humidity, num_temp_humidity, temp);
      long int location = use_map(humidity_location, num_humidity_location, humidity);
      //printf("Seed %ld = soil %ld = fertiliser %ld = water %ld = light %ld = temp %ld = humidity %ld = location %ld\r\n", i, soil, fertiliser, water, light, temp, humidity, location);
      if (location < lowest_location)
      {
        lowest_location = location;
      }
    }
  }
  printf("Lowest location = %ld\r\n", lowest_location);
}