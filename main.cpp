#include <iostream>
#include <cstdlib>
using namespace std;

const int student_amount = 100;
const int student_per_page = 10;

string student_names[student_amount][student_per_page];
char student_grades[student_amount][student_per_page];

void Add_record(string student_name, char student_grade);
bool Remove_record(string student_name);
double Calculate_Average_Grade();
void Count_Grade(char grade, int &A_grades, int &B_grades, int &C_grades, int &D_grades, int &F_grades);
void Show_Highest_To_Lowest();
int GetGradeIndex(char grade);

int main()
{
    student_names[0][0] = "Kayra";
    student_grades[0][0] = 'F';
    student_names[0][1] = "Arda";
    student_grades[0][1] = 'A';

    string op;

    do
    {
        cout << "Welcome To Student Grade Manager! what would you like to do? (view_records/add_record/remove_record/show_average_grade/show_highest_to_lowest/exit):\n";
        getline(cin, op);

        if (op == "view_records")
        {
            cout << "All records:\n";
            for (int row = 0; row < student_amount; row++)
            {
                for (int column = 0; column < student_per_page; column++)
                {
                    if (!student_names[row][column].empty())
                    {
                        cout << "Student Name: " << student_names[row][column] << "\n";
                        cout << "Student Grade: " << student_grades[row][column] << "\n";
                    }
                }
            }
        }
        else if (op == "add_record")
        {
            string student_name;
            char student_grade;

            cout << "Enter Student Name: ";
            cin >> student_name;

            cout << "Enter Student Grade (A-F): ";
            cin >> student_grade;

            cin.ignore(); // clear newline from buffer

            Add_record(student_name, student_grade);
        }
        else if (op == "remove_record")
        {
            string student_name;
            cout << "Enter Student Name to Remove: ";
            cin >> student_name;
            cin.ignore();

            if (Remove_record(student_name))
                cout << "Student " << student_name << " removed successfully.\n";
            else
                cout << "Student " << student_name << " not found.\n";
        }
        else if (op == "show_average_grade")
        {
            double average_grade = Calculate_Average_Grade();
            cout << "Average Grade (Numeric): " << average_grade << "\n";
        }
        else if (op == "show_highest_to_lowest")
        {
            Show_Highest_To_Lowest();
        }
        else if (op != "exit")
        {
            cout << "Not a valid response! :  " << op << endl;
        }

    } while (op != "exit");

    return 0;
}

void Add_record(string student_name, char student_grade)
{
    for (int row = 0; row < student_amount; row++)
    {
        for (int column = 0; column < student_per_page; column++)
        {
            if (student_names[row][column].empty())
            {
                student_names[row][column] = student_name;
                student_grades[row][column] = student_grade;
                cout << "New Student Has been Successfully Registered!" << "\n";
                return;
            }
        }
    }
    cout << "Database Full! Cannot add more students." << endl;
}

bool Remove_record(string student_name)
{
    for (int row = 0; row < student_amount; row++)
    {
        for (int column = 0; column < student_per_page; column++)
        {
            if (student_names[row][column] == student_name)
            {
                student_names[row][column].clear();
                student_grades[row][column] = '\0';
                return true;
            }
        }
    }
    return false;
}

void Count_Grade(char grade, int &A_grades, int &B_grades, int &C_grades, int &D_grades, int &F_grades)
{
    switch (grade)
    {
    case 'A':
        A_grades++;
        break;
    case 'B':
        B_grades++;
        break;
    case 'C':
        C_grades++;
        break;
    case 'D':
        D_grades++;
        break;
    case 'F':
        F_grades++;
        break;
    default:
        break;
    }
}

double Calculate_Average_Grade()
{
    int A_grades = 0, B_grades = 0, C_grades = 0, D_grades = 0, F_grades = 0;
    int total_grades = 0;

    for (int row = 0; row < student_amount; row++)
    {
        for (int column = 0; column < student_per_page; column++)
        {
            char grade = student_grades[row][column];
            if (grade != '\0' && grade >= 'A' && grade <= 'F')
            {
                Count_Grade(grade, A_grades, B_grades, C_grades, D_grades, F_grades);
                total_grades++;
            }
        }
    }

    if (total_grades == 0)
        return 0.0;

    double total_points = (A_grades * 4) + (B_grades * 3) + (C_grades * 2) + (D_grades * 1);
    double average = total_points / total_grades;

    return average;
}

int GetGradeIndex(char grade)
{
    switch (grade)
    {
    case 'A':
        return 5;
    case 'B':
        return 4;
    case 'C':
        return 3;
    case 'D':
        return 2;
    case 'F':
        return 0;
    default:
        return -1;
    }
}

void Show_Highest_To_Lowest()
{
    // Create two arrays to store students and grades temporarily
    string temp_names[student_amount * student_per_page];
    char temp_grades[student_amount * student_per_page];
    int count = 0;

    // Flatten 2D arrays into 1D arrays
    for (int row = 0; row < student_amount; row++)
    {
        for (int col = 0; col < student_per_page; col++)
        {
            if (!student_names[row][col].empty())
            {
                temp_names[count] = student_names[row][col];
                temp_grades[count] = student_grades[row][col];
                count++;
            }
        }
    }

    // Simple bubble sort by grade descending
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (GetGradeIndex(temp_grades[j]) < GetGradeIndex(temp_grades[j + 1]))
            {
                // Swap grades
                char temp_grade = temp_grades[j];
                temp_grades[j] = temp_grades[j + 1];
                temp_grades[j + 1] = temp_grade;

                // Swap corresponding names
                string temp_name = temp_names[j];
                temp_names[j] = temp_names[j + 1];
                temp_names[j + 1] = temp_name;
            }
        }
    }

    // Print sorted list
    cout << "Grades Highest To Lowest:\n";
    for (int i = 0; i < count; i++)
    {
        cout << "Student Name: " << temp_names[i] << endl;
        cout << "Student Grade: " << temp_grades[i] << endl;
    }
}
