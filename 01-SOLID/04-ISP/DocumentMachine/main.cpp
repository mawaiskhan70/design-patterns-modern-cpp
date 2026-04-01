#include <iostream>
#include "document.h"
#include "printer.h"
#include "scanner.h"
#include "machine.h"

using namespace std;

// Takes ONLY IPrinter — doesn't care about scanning
void printDocument(IPrinter& printer, Document& doc) {
    printer.print(doc);
}

// Takes ONLY IScanner — doesn't care about printing
void scanDocument(IScanner& scanner, Document& doc) {
    scanner.scan(doc);
}

int main() {

    Document doc("Report.pdf", "Quarterly sales report 2024");

    // ── Simple Printer (only prints) ──
    cout << "=== Simple Printer ===" << endl;
    Printer printer;
    printDocument(printer, doc);

    // ── Simple Scanner (only scans) ──
    cout << "\n=== Simple Scanner ===" << endl;
    Scanner scanner;
    scanDocument(scanner, doc);

    // ── Multi-function Machine (prints AND scans) ──
    cout << "\n=== Multi-function Machine ===" << endl;
    Machine machine(printer, scanner);
    //              So IPrinter& can HOLD reference to Printer!
    printDocument(machine, doc);    // Works as printer!
    scanDocument(machine, doc);     // Works as scanner!

    // ── ISP Benefit: Pass machine to print-only function ──
    cout << "\n=== Machine used as Printer only ===" << endl;
    printDocument(machine, doc);    // Only uses print capability!
    // machine CAN scan, but this function doesn't care!

    return 0;
}
