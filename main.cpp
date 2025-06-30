#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int student_amount = 100;
const int student_per_page = 10;

string student_names[student_amount][student_per_page];
char student_grades[student_amount][student_per_page];

void Add_record(string student_name, char student_grade);
double Calculate_Average_Grade();
void Count_Grade(char grade, int &A_grades, int &B_grades, int &C_grades, int &D_grades, int &F_grades);
void Show_Highest_To_Lowest();
int GetGradeIndex(char grade);

struct StudentRecord
{
    string name;
    char grade;
};

int main()
{
    student_names[0][0] = "Kayra";
    student_grades[0][0] = 'F';
    student_names[0][1] = "Arda";
    student_grades[0][1] = 'A';

    string op;

    do
    {
        cout << "Welcome To Student Grade Manager! what would you like to do? (view_records/add_record/show_average_grade/show_highest_to_lowest/exit):\n";
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

            Add_record(student_name, student_grade);
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
        // Ignore invalid grades
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
            if (grade != '\0' && grade >= 'A' && grade <= 'F') // check valid grade letters
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
        return -1; // Invalid grade
    }
}

bool CompareStudents(const StudentRecord &a, const StudentRecord &b)
{
    return GetGradeIndex(a.grade) > GetGradeIndex(b.grade);
}

void Show_Highest_To_Lowest()
{
    vector<StudentRecord> students;

    // Collect all valid students into vector
    for (int row = 0; row < student_amount; row++)
    {
        for (int column = 0; column < student_per_page; column++)
        {
            if (!student_names[row][column].empty())
            {
                char grade = student_grades[row][column];
                if (grade != 'N' && GetGradeIndex(grade) != -1) // skip invalid grades
                {
                    students.push_back({student_names[row][column], grade});
                }
            }
        }
    }

    // Sort students by grade descending
    sort(students.begin(), students.end(), CompareStudents);

    cout << "Grades Highest To Lowest:\n";
    for (const auto &student : students)
    {
        cout << "Student Name: " << student.name << endl;
        cout << "Student Grade: " << student.grade << endl;
    }
}
