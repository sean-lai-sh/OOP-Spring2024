#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
PrintedMaterial(unsigned numPages) : numberOfPages(numPages) {}
virtual void displayNumPages() const = 0;

private:
unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
using PrintedMaterial::PrintedMaterial;
void displayNumPages() const override { cout << "Pages: "; PrintedMaterial::displayNumPages(); }
private:
};

void PrintedMaterial::displayNumPages() const {
    cout << numberOfPages << endl;
}

class Book : public PrintedMaterial {
public:
using PrintedMaterial::PrintedMaterial;
virtual void displayNumPages() const override { cout << "Pages: "; PrintedMaterial::displayNumPages(); }
private:
};

class TextBook : public Book {
public:
TextBook(unsigned numPages, unsigned numIndxPgs) : 
Book(numPages), numIndexPages(numIndxPgs) {}
// void displayNumPages() const override { cout << numIndexPages << endl << getNumPages() << endl; }
void displayNumPages() const { cout << "Pages: ";
	PrintedMaterial::displayNumPages();
	cout << "Index pages: ";
	cout << numIndexPages << endl; }
private:
unsigned numIndexPages;
};

class Novel : public Book {
public:
using Book::Book;
void displayNumPages() const override { cout << "Pages: "; PrintedMaterial::displayNumPages(); }
private:
};

// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";

    // cout << "\nA PrintedMaterial material object!\n";
    // PrintedMaterial pm(2345);
    // pm.displayNumPages();

    // cout << "\nA PrintedMaterial variable containing a TextBook value\n";
    // pm = text; // like putting a Textbook into a PrintedMaterial
    // pm.displayNumPages();

    cout << "Try using pointer to base type\n";
    PrintedMaterial* pmPtr;
    pmPtr = &text; 

    pmPtr->displayNumPages(); 
    vector<PrintedMaterial*> allPrintedThings;
    allPrintedThings.push_back(&text);
    allPrintedThings.push_back(&novel);
    allPrintedThings.push_back(&mag);
    for( PrintedMaterial* pm : allPrintedThings ) {
        pm->displayNumPages();
        cout << endl;
    }
}