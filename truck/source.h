
// Cargo: what the truck is carrying
struct cargo {
    const char *title;
    int quantity;
    double weight;
};

// Define the truck structure here
struct truck{
  // Have truck data
  char name[31];
  double length;
  double weight;
  struct cargo crg;
};

struct truck create_truck(const char *name, double length, double weight,
			    struct cargo crg);

void print_truck(const struct truck *car);
