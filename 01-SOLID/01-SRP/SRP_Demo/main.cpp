#include <iostream>
#include "journal/journal.h"
#include "journal/persistencemanager.h"

using namespace std;

int main()
{
    Journal journal("Awais Diary");
    journal.add("I am learning SPR");
    journal.add("I configured GitHub");
    journal.add("I am a Software engineer");

    cout <<"Journal: "<< journal.m_title << endl;
    cout <<"Entries: "<< journal.count() << endl;
    for(auto& entry: journal.m_entries)
    {
        cout << " "<<entry<<endl;
    }
    cout << endl;

    PersistenceManager::save(journal, "diary.txt");

    Journal load = PersistenceManager::load("diary.txt");
    cout <<"\n Loaded: "<<load.m_title<< endl;
    for (auto& entry: load.m_entries)
    {
        cout <<""<<entry<<endl;
    }
    return 0;
}
