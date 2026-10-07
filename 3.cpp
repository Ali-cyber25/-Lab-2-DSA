#include <iostream>
#include <string>
using namespace std;


template <typename T, int N>
int linearSearch(T(&arr)[N], T value)
{
    for (int i = 0; i < N; i++)
    {
        if (arr[i] == value)
        {
            return i;
        }
    }

    return -1;
}


template <typename T, int N>
int binarySearch(T(&arr)[N], T value)
{
    int low = 0;
    int high = N - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == value)
        {
            return mid;
        }
        else if (arr[mid] < value)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

class LibraryItem
{
public:

    virtual void display() const = 0;

    virtual bool lessThan(const LibraryItem& other) const = 0;

    virtual ~LibraryItem() {}
};

class Book : public LibraryItem
{
private:
    string title;
    string author;
    int pages;

public:

    Book(string t, string a, int p)
    {
        title = t;
        author = a;
        pages = p;
    }

    string getTitle() const
    {
        return title;
    }

    string getAuthor() const
    {
        return author;
    }

    int getPages() const
    {
        return pages;
    }

    void display() const override
    {
        cout << "Book: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
    }

    bool lessThan(const LibraryItem& other) const override
    {
        const Book& otherBook = dynamic_cast<const Book&>(other);
        return pages < otherBook.pages;
    }
};


class Newspaper : public LibraryItem
{
private:
    string name;
    string date;
    string edition;

public:

    Newspaper(string n, string d, string e)
    {
        name = n;
        date = d;
        edition = e;
    }

    string getName() const
    {
        return name;
    }

    string getDate() const
    {
        return date;
    }

    string getEdition() const
    {
        return edition;
    }

    void display() const override
    {
        cout << "Newspaper: " << name << endl;
        cout << "Date: " << date << endl;
        cout << "Edition: " << edition << endl;
    }

    bool lessThan(const LibraryItem& other) const override
    {
        const Newspaper& otherNewspaper =
            dynamic_cast<const Newspaper&>(other);

        return edition < otherNewspaper.edition;
    }
};


class Library
{
private:
    Book* books[100];
    Newspaper* newspapers[100];

    int bookCount;
    int newspaperCount;

public:

    Library()
    {
        bookCount = 0;
        newspaperCount = 0;
    }

    void addBook(const Book& book)
    {
        if (bookCount < 100)
        {
            books[bookCount] = new Book(book);
            bookCount++;
        }
    }

    void addNewspaper(const Newspaper& newspaper)
    {
        if (newspaperCount < 100)
        {
            newspapers[newspaperCount] = new Newspaper(newspaper);
            newspaperCount++;
        }
    }

    void displayCollection() const
    {
        cout << "\n----- BOOKS -----\n";

        for (int i = 0; i < bookCount; i++)
        {
            books[i]->display();
            cout << endl;
        }

        cout << "----- NEWSPAPERS -----\n";

        for (int i = 0; i < newspaperCount; i++)
        {
            newspapers[i]->display();
            cout << endl;
        }
    }

    void sortBooksByPages()
    {
        for (int i = 0; i < bookCount - 1; i++)
        {
            for (int j = 0; j < bookCount - i - 1; j++)
            {
                if (books[j]->getPages() > books[j + 1]->getPages())
                {
                    Book* temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }
    }

    void sortNewspapersByEdition()
    {
        for (int i = 0; i < newspaperCount - 1; i++)
        {
            for (int j = 0; j < newspaperCount - i - 1; j++)
            {
                if (newspapers[j]->getEdition() >
                    newspapers[j + 1]->getEdition())
                {
                    Newspaper* temp = newspapers[j];
                    newspapers[j] = newspapers[j + 1];
                    newspapers[j + 1] = temp;
                }
            }
        }
    }

    Book* searchBookByTitle(string title)
    {
        string titles[100];

        for (int i = 0; i < bookCount; i++)
        {
            titles[i] = books[i]->getTitle();
        }

        int index = linearSearch(titles, title);

        if (index != -1)
        {
            return books[index];
        }

        return nullptr;
    }


    Newspaper* searchNewspaperByName(string name)
    {
        string names[100];

        for (int i = 0; i < newspaperCount; i++)
        {
            names[i] = newspapers[i]->getName();
        }

        int index = linearSearch(names, name);

        if (index != -1)
        {
            return newspapers[index];
        }

        return nullptr;
    }

    ~Library()
    {
        for (int i = 0; i < bookCount; i++)
        {
            delete books[i];
        }

        for (int i = 0; i < newspaperCount; i++)
        {
            delete newspapers[i];
        }
    }
};

int main()
{

    Book book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book book2("To Kill a Mockingbird", "Harper Lee", 324);

    Newspaper newspaper1(
        "Washington Post",
        "2024-10-13",
        "Morning Edition"
    );

    Newspaper newspaper2(
        "The Times",
        "2024-10-12",
        "Weekend Edition"
    );

    Library library;

    library.addBook(book1);
    library.addBook(book2);

    library.addNewspaper(newspaper1);
    library.addNewspaper(newspaper2);

    cout << "Before Sorting:\n";
    library.displayCollection();

    library.sortBooksByPages();
    library.sortNewspapersByEdition();

    cout << "\nAfter Sorting:\n";
    library.displayCollection();

    Book* foundBook =
        library.searchBookByTitle("The Catcher in the Rye");

    if (foundBook)
    {
        cout << "\nFound Book:\n";
        foundBook->display();
    }
    else
    {
        cout << "\nBook not found.\n";
    }

    Newspaper* foundNewspaper =
        library.searchNewspaperByName("The Times");

    if (foundNewspaper)
    {
        cout << "\nFound Newspaper:\n";
        foundNewspaper->display();
    }
    else
    {
        cout << "\nNewspaper not found.\n";
    }

    return 0;
}
