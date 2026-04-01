
#include "Tag.h"
#include "P.h"
#include "IMG.h"
#include "HtmlBuilder.h"

using namespace std;
using namespace html;

int main() {

    // ═══════════════════════════════════════
    // Method 1: Groovy Style (Direct Construction)
    // ═══════════════════════════════════════
    cout << "=== Groovy Style ===" << endl;

    cout<<
        P{
            IMG{"http://pokemon.com/pikachu.png"}
        }
         <<endl;

    // ═══════════════════════════════════════
    // Method 2: Groovy Style with Text
    // ═══════════════════════════════════════
    cout << "=== Groovy Style (Text) ===" << endl;

    cout <<
        P {"Hello world"}
         <<endl;

    // ═══════════════════════════════════════
    // Method 3: Groovy Style with Multiple Children
    // ═══════════════════════════════════════
    cout << "=== Groovy Style (Multiple Children) ===" << endl;

    cout <<
        P {
            IMG {"http://pokemon.com/pikachu.png"},
            IMG {"http://pokemon.com/bulbasaur.png"},
            IMG {"http://pokemon.com/charmander.png"}
        }
         << endl;

    // ═══════════════════════════════════════
    // Method 4: Builder Pattern (Step by Step)
    // ═══════════════════════════════════════

    HtmlBuilder builder("ul");
    builder.addChild("li","Item1")
        .addChild("li","Item2")
        .addChild("li","Item1");

    cout <<builder;

    // ═══════════════════════════════════════
    // Method 5: Builder with Tags
    // ═══════════════════════════════════════
    cout << "=== Builder with Tags ===" << endl;

    HtmlBuilder pageBuilder("div");
    pageBuilder.addChild(P{"Welcome to my page!"})
        .addChild(P{
            IMG{"http://example.com/photo.jpg"}
        });

    cout << pageBuilder << endl;

    // ═══════════════════════════════════════
    // Method 6: Get as String
    // ═══════════════════════════════════════
    cout << "=== As String ===" << endl;

    string html = builder.str();
    cout << "HTML string length: " << html.length() << endl;
    cout << html << endl;

    cout << "=== Builder with Grovy style ===" << endl;
    HtmlBuilder builder2("p");
    builder2.addChild(IMG("logo.png"))
        .addChild(IMG("banner.png"));
    cout << builder2;

    return 0;

}
