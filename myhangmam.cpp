#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;

const int MAX_SLOT = 7;      //có 7 lượt chơi tối thiểu.
string guessWord;            //Từ cần đoán
int sizeOfGuessWord = 0;     //Kích thước từ cần đoán
string referenceWord;        //Là từ cần đoán. được hiển thị theo '----'
char body[7];                //Mảng chứa các ký tự bộ phận của cơ thể.
int score = 0;               //Điểm của người chơi. Đạt max = kích thước từ cần đoán, min =0.
int slot = 0;                //Số lượt chơi hiện tại.
vector<string> Dictionary(); //Đọc list từ vào vector
void ReIntination();         //Chuẩn bị từ hiển thị theo '----'
void Running();              //Hàm chính, chạy chương trình.
void Draw(int slot);         //Vẽ hình.
int main()
{
    vector<string> lists;
    lists = Dictionary();
    srand(time(NULL));
    long sizeOfList = lists.size();
    long n = rand() % sizeOfList + 0;
    guessWord = lists[n];
    sizeOfGuessWord = guessWord.size();
    cout << guessWord;
    ReIntination();
    Running();
    lists.clear();
    return 0;
}
void Draw(int count)
{
    std::system("cls");
    //cout << guessWord;

    cout << "Welcome to Hangman Game" << endl;
    printf("You have %d turns \n", MAX_SLOT-slot);
    if (count == 1)
    {
        body[0] = 'o';
    }
    if (count == 2)
    {
        body[1] = '|';
    }
    if (count == 3)
    {
        body[2] = '/';
    }
    if (count == 4)
    {
        body[3] = '|';
    }
    if (count == 5)
    {
        body[4] = '\\';
    }
    if (count == 6)
    {
        body[5] = '/';
    }
    if (count == 7)
    {
        body[6] = '\\';
    }

    printf("________________________\n"
           "|                      |\n"
           "|                      |\n"
           "|                      %c\n"
           "|                      %c\n"
           "|                     %c%c%c\n"
           "|                     %c %c\n",
           body[0], body[1], body[2], body[3], body[4], body[5], body[6]);
    cout << "WordLetter: " << referenceWord << endl;
}

void CorrectLetter(char letter)
{
    int check1 = 0;
    int check2 = 0;
    //Kiểm tra ký tự đó đã tồn tại trong từ - reference word, nếu đã tồn tại thì tính là một lần nhập sai.
    for (int i = 0; i < sizeOfGuessWord; i++)
    {
        if (letter == referenceWord[i])
        {
            check1 = 1;
        }
    }
    //Kiểm tra ký tự có tồn tại trong SecretWord hay không?
    for (int i = 0; i < sizeOfGuessWord; i++)
    {
        if (letter == guessWord[i])
        {
            referenceWord[i] = letter;
            check2++;
        }
    }

    if (check2 >= 1 && check1==0)
    {
        score = score + check2;
    }
    else
    {
        slot++;
    }
}
void ReIntination()
{
    for (int i = 0; i < sizeOfGuessWord; i++)
    {
        referenceWord += "-";
    }
}
vector<string> Dictionary()
{
    vector<string> list;
    ifstream readFile;
    readFile.open("dictionary_1.txt");
    if (readFile.fail())
    {
        cout << "Not found dictionary";
    }
    else
    {
        while (!readFile.eof())
        {
            string words;
            readFile >> words;
            list.push_back(words);
        }
    }
    return list;
}

void Running()
{
    while (slot <= MAX_SLOT)
    {
        Draw(slot);
        //Nếu đã đoán đúng từ: Thông báo bạn đã chiến thắng và đưa ra từ bí mật.

        if (score == sizeOfGuessWord)
        {
            cout << "You win!" << endl;
            break;
        }
        //Trường hợp chưa đoán đúng nhưng vẫn còn slot chơi.
        else
        {
            if (slot < MAX_SLOT)
            { //Vẫn còn slot chơi thì cho người chơi nhập tiếp ký tự, nếu không thì người chơi thua.
                cout << "GuessLetter: ";
                char leter;
                cin >> leter;
                CorrectLetter(leter);
            }
            else
            {
                cout << "You lose!" << endl;
                cout << "Secret Word: " << guessWord << endl;
                break;
            }
        }
    }
}
