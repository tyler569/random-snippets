
#include <vector>
using std::vector;
#include <cstdio>

int created_count = 0;
int destroyed_count = 0;

struct nontrivial {
    int value = 0;
    int move_count = 0;
    int copy_count = 0;
    int copied_from = 0;
    int moved_from = 0;
    nontrivial(int v) {
        created_count += 1;
        printf("created %i\n", v);
        value = v;
    }
    nontrivial(const nontrivial& o) {
        value = o.value;
        move_count = o.move_count;
        copy_count = o.copy_count + 1;
        printf("copyed %i\n", value);
        const_cast<nontrivial&>(o).copied_from += 1;
    }
    nontrivial(nontrivial&& o) {
        value = o.value;
        copy_count = o.copy_count;
        move_count = o.move_count + 1;
        printf("moved %i\n", value);
        o.moved_from += 1;
    }
    ~nontrivial() {
        printf("destroyed % 2i - % 4i % 4i % 4i % 4i\n", 
                value, move_count, copy_count, moved_from, copied_from);
        destroyed_count += 1;
    }
};

vector<nontrivial> x = { 1, 2, 3 };

int main() {
    printf("         |  id |  m |  c | mf | cf\n");

    x.push_back(4);
    x.push_back(5);
    x.push_back(6);
    printf("%i : %i\n", created_count, destroyed_count);
}

