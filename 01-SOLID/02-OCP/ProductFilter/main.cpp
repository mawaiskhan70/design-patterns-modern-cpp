#include <iostream>
#include <vector>

#include "product.h"
#include "betterfilter.h"
#include "colorspecification.h"
#include "sizespecification.h"
#include "andspecification.h"

using namespace std;

int main() {

    // ── Create Products ──
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    const vector<Product*> all { &apple, &tree, &house };

    // ── Create Filter (OCP: works with ANY specification) ──
    BetterFilter bf;

    // ── Filter by Color ──
    cout << "=== Green Products ===" << endl;
    ColorSpecification green(Color::green);
    for (auto& x : bf.filter(all, green)) {
        cout << "  " << x->name << " is green" << endl;
    }

    // ── Filter by Size ──
    cout << "\n=== Large Products ===" << endl;
    SizeSpecification large(Size::large);
    for (auto& x : bf.filter(all, large)) {
        cout << "  " << x->name << " is large" << endl;
    }

    // ── Filter by Color AND Size ──
    cout << "\n=== Green AND Large Products ===" << endl;
    auto green_and_large = green && large;
    for (auto& x : bf.filter(all, green_and_large)) {
        cout << "  " << x->name << " is green and large" << endl;
    }

    return 0;
}
