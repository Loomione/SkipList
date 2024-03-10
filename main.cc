#include "skip_list.hh"
#include <vector>
#include <assert.h>
#include <algorithm>
#include <cstdlib>
#include <sys/types.h>

int main() {
  SkipList skip_list;
  const int num_elements = 200000;
  std::vector<int> elements(num_elements);
  for (int j = 0; j < num_elements; ++j) elements[j] = j;
  std::random_shuffle(elements.begin(), elements.end());

  for (int j = 0; j < num_elements; ++j) skip_list.Insert(elements[j]);
  for (int j = 0; j < num_elements; ++j) assert(skip_list.Contains(j));
  for (int j = num_elements; j < num_elements * 2; ++j)
    assert(!skip_list.Contains(j));
  return 0;
}