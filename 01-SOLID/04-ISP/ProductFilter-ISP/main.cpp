#include <iostream>
#include <vector>

#include "product.h"
#include "BetterFilter.h"
#include "ColorSpecification.h"
#include "SizeSpecification.h"
#include "AndSpecification.h"
#include "ICombiner.h"

using namespace std;

// ══════════════════════════════════════════════════════
// ISP: Functions take ONLY what they need!
// ══════════════════════════════════════════════════════

// Takes ONLY ISpecification — doesn't know about filtering
bool checkProduct(ISpecification<Product>& spec, Product* product) {
    return spec.is_satisfied(product);
}

// Takes ONLY IFilter — doesn't define specifications
vector<Product*> filterProducts(IFilter<Product>& filter,
                                 vector<Product*> items,
                                 ISpecification<Product>& spec) {
    return filter.filter(items, spec);
}

int main() {

    // ── Create Products ──
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};
    Product car{"Car", Color::red, Size::medium};

    const vector<Product*> all { &apple, &tree, &house, &car };

    BetterFilter bf;

    // ── ISP: ISpecification used alone (no filter needed!) ──
    cout << "=== Check Single Product ===" << endl;
    ColorSpecification green(Color::green);

    cout << "Is Apple green? "
         << (checkProduct(green, &apple) ? "YES" : "NO") << endl;
    cout << "Is House green? "
         << (checkProduct(green, &house) ? "YES" : "NO") << endl;

    // ── ISP: IFilter used with ISpecification ──
    cout << "\n=== Green Products ===" << endl;
    for (auto& x : filterProducts(bf, all, green)) {
        cout << "  " << x->name << " is green" << endl;
    }

    // ── Filter by Size ──
    cout << "\n=== Large Products ===" << endl;
    SizeSpecification large(Size::large);
    for (auto& x : filterProducts(bf, all, large)) {
        cout << "  " << x->name << " is large" << endl;
    }

    // ── ICombiner: Combine specifications ──
    cout << "\n=== Green AND Large ===" << endl;
    auto green_and_large = green && large;
    for (auto& x : bf.filter(all, green_and_large)) {
        cout << "  " << x->name << " is green and large" << endl;
    }

    // ── ISP Benefit: Use ISpecification WITHOUT IFilter ──
    cout << "\n=== Check All Products (No Filter!) ===" << endl;
    SizeSpecification small_size(Size::small);
    for (auto& p : all) {
        if (checkProduct(small_size, p)) {
            cout << "  " << p->name << " is small" << endl;
        }
    }

    // ── ISP Benefit: Different filter, same specifications ──
    cout << "\n=== Red Products ===" << endl;
    ColorSpecification red(Color::red);
    for (auto& x : filterProducts(bf, all, red)) {
        cout << "  " << x->name << " is red" << endl;
    }

    return 0;
}
