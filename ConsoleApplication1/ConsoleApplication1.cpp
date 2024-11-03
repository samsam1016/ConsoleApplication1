// ConsoleApplication1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <algorithm>
#include <forward_list>
#include <iostream>
#include <list>
#include <regex>
#include <string>
#include <vector>

using namespace std;

// 圖書結構
struct Book {
    string title;
    string author;
    string id;

    bool operator<(const Book& other) const {
        return id < other.id;
    }
};

// 借閱者結構
struct Borrower {
    string name;
    vector<string> borrowedBooks;
};

// 驗證圖書編號格式
bool isValidBookId(const string& id) {
    regex pattern("^[A-Za-z][0-9]{4}$");
    return regex_match(id, pattern);
}

// 圖書管理
class Library {
private:
    list<Book> books;

public:
    void addBook(const string& title, const string& author, const string& id) {
        if (!isValidBookId(id)) {
            cout << "無效的圖書編號，必須是1個字母開頭加上4位數字。" << endl;
            return;
        }
        books.push_back({ title, author, id });
        cout << "已添加圖書：" << title << " (" << id << ")" << endl;
    }

    void removeBook(const string& id) {
        auto it = find_if(books.begin(), books.end(), [&](const Book& book) { return book.id == id; });
        if (it != books.end()) {
            cout << "刪除圖書：" << it->title << " (" << it->id << ")" << endl;
            books.erase(it);
        }
        else {
            cout << "找不到圖書編號為 " << id << " 的圖書。" << endl;
        }
    }

    void searchBook(const string& id) const {
        auto it = find_if(books.begin(), books.end(), [&](const Book& book) { return book.id == id; });
        if (it != books.end()) {
            cout << "找到圖書：" << it->title << ", 作者：" << it->author << ", 圖書編號：" << it->id << endl;
        }
        else {
            cout << "找不到圖書編號為 " << id << " 的圖書。" << endl;
        }
    }

    void listBooks() const {
        list<Book> sortedBooks = books;
        sortedBooks.sort();
        cout << "所有圖書：" << endl;
        for (const auto& book : sortedBooks) {
            cout << "圖書編號：" << book.id << ", 書名：" << book.title << ", 作者：" << book.author << endl;
        }
    }
};

// 借閱者管理
class BorrowerList {
private:
    forward_list<Borrower> borrowers;

public:
    // 添加借閱者並借閱圖書
    void addBorrowerWithBook(const string& name, const string& bookId) {
        auto it = find_if(borrowers.begin(), borrowers.end(), [&](const Borrower& borrower) { return borrower.name == name; });
        if (it != borrowers.end()) {
            // 借閱者已存在，添加新借閱的圖書
            it->borrowedBooks.push_back(bookId);
            cout << "借閱成功：" << name << " 借閱了圖書編號 " << bookId << endl;
        }
        else {
            // 借閱者不存在，創建新借閱者並借閱圖書
            borrowers.push_front({ name, {bookId} });
            cout << "已添加新借閱者：" << name << "，並借閱了圖書編號 " << bookId << endl;
        }
    }

    void removeBorrower(const string& name) {
        borrowers.remove_if([&](const Borrower& borrower) { return borrower.name == name; });
        cout << "已刪除借閱者：" << name << endl;
    }

    void searchBorrower(const string& name) const {
        auto it = find_if(borrowers.begin(), borrowers.end(), [&](const Borrower& borrower) { return borrower.name == name; });
        if (it != borrowers.end()) {
            cout << "找到借閱者：" << it->name << endl;
            if (it->borrowedBooks.empty()) {
                cout << "該借閱者無借閱圖書。" << endl;
            }
            else {
                cout << "借閱的圖書編號：";
                for (const auto& bookId : it->borrowedBooks) {
                    cout << bookId << " ";
                }
                cout << endl;
            }
        }
        else {
            cout << "找不到借閱者：" << name << endl;
        }
    }

    void listBorrowers() const {
        cout << "所有借閱者：" << endl;
        for (const auto& borrower : borrowers) {
            cout << "借閱者姓名：" << borrower.name << ", 借閱的圖書：";
            if (borrower.borrowedBooks.empty()) {
                cout << "無";
            }
            else {
                for (const auto& bookId : borrower.borrowedBooks) {
                    cout << bookId << " ";
                }
            }
            cout << endl;
        }
    }
};

// 主程式
int main() {
    Library library;
    BorrowerList borrowerList;
    int choice;

    while (true) {
        cout << "\n圖書館管理系統選單：" << endl;
        cout << "1. 添加圖書\n2. 刪除圖書\n3. 搜索圖書\n4. 列出所有圖書" << endl;
        cout << "5. 新增借閱者並借閱圖書\n6. 刪除借閱者\n7. 搜索借閱者\n8. 列出所有借閱者" << endl;
        cout << "0. 退出" << endl;
        cout << "請選擇操作：";
        cin >> choice;

        if (choice == 0) break;

        string title, author, id, name;

        switch (choice) {
        case 1:
            cout << "輸入書名：";
            cin >> title;
            cout << "輸入作者：";
            cin >> author;
            cout << "輸入圖書編號：";
            cin >> id;
            library.addBook(title, author, id);
            break;
        case 2:
            cout << "輸入要刪除的圖書編號：";
            cin >> id;
            library.removeBook(id);
            break;
        case 3:
            cout << "輸入要搜索的圖書編號：";
            cin >> id;
            library.searchBook(id);
            break;
        case 4:
            library.listBooks();
            break;
        case 5:
            cout << "輸入借閱者姓名：";
            cin >> name;
            cout << "輸入要借閱的圖書編號：";
            cin >> id;
            borrowerList.addBorrowerWithBook(name, id);
            break;
        case 6:
            cout << "輸入要刪除的借閱者姓名：";
            cin >> name;
            borrowerList.removeBorrower(name);
            break;
        case 7:
            cout << "輸入要搜索的借閱者姓名：";
            cin >> name;
            borrowerList.searchBorrower(name);
            break;
        case 8:
            borrowerList.listBorrowers();
            break;
        default:
            cout << "無效選項，請重新選擇。" << endl;
            break;
        }
    }
    return 0;
}


// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
