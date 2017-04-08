#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Birthday.h"         
#include "Student.h"

using namespace std;

   template <typename T>
void Validate(string redoMsg, T reassignVar)
{
   while(true)
   {
      if(cin.fail())
      {
         cin.clear();
         cin.ignore(INT_MAX, '\n');
         cout << "Wrong input. Enter again" << endl;
         cout << redoMsg;
         cin >> reassignVar;
      }
      else
      {
         break;
      }
   }
}

void StudentList::ReadTxt()
{
   int size;
   cout << "Size: ";
   cin >> size;

   ifstream ifs("input.txt");
   int dummy;
   short day = 0, month = 0, year = 0;

   stdList.resize(size);

   ifs >> dummy;
   ifs.ignore();

   for(int i = 0; i < size; i++)
   {
      ifs >> stdList[i].mID;
      ifs.ignore();

      getline(ifs, stdList[i].mName);

      ifs >> day;
      ifs.ignore();
      ifs >> month;
      ifs.ignore();
      ifs >> year;
      ifs.ignore();
      ifs >> stdList[i].mAvgScore;
      ifs.ignore();

      stdList[i].mBirthday.SetDay(day);
      stdList[i].mBirthday.SetMonth(month);
      stdList[i].mBirthday.SetYear(year);
   }
   ifs.close();
}

int StudentList::GetLine(ifstream &ifs)
{
   int count = 0;
   string line;
   while(getline(ifs, line))
   {
      //skip empty line
      if(line.empty())
      {
         continue;
      }
      count++;
   }
   //set position to beginning of the file again
   ifs.clear();
   ifs.seekg(0, ios::beg);

   return count;
}

void StudentList::Write()
{
   if(stdList.empty())
   {
      cout << "Student list is empty. Please create new data first";
      cin.get();
      cin.get();
      return;
   }
   int total = stdList.size();
   ofstream ofs("DSSV.dat", ios::binary);
   short day, month, year;

   if(ofs.is_open())
   {
      ofs.write((char*)&total, sizeof(total));
      ofs << endl;

      for(int i = 0; i < stdList.size(); i++)
      {

         day   = stdList[i].mBirthday.GetDay();
         month = stdList[i].mBirthday.GetMonth();
         year  = stdList[i].mBirthday.GetYear();

         ofs.write((char*)&stdList[i].mID, sizeof(int));
         ofs << endl;
         ofs.write(stdList[i].mName.c_str(), stdList[i].mName.size());
         ofs << endl;
         ofs.write((char*)&day, sizeof(day));
         ofs << endl;
         ofs.write((char*)&month, sizeof(month));
         ofs << endl;
         ofs.write((char*)&year, sizeof(year));
         ofs << endl;
         ofs.write((char*)&stdList[i].mAvgScore, sizeof(double));
         ofs << endl;
      }
      cout << "File has been written successfully";
      cin.get();
      cin.get();
   }
   ofs.close();
}

void StudentList::Read()
{
   ifstream ifs("DSSV.dat", ios::binary);
   string strName;
   int size = (GetLine(ifs) - 1) / 6;
   short day = 0, month = 0, year = 0;

   stdList.resize(size);

   if(ifs.is_open())
   {
      //Skip first line
      int dummy;
      ifs.read((char*)&dummy, sizeof(dummy));
      ifs.ignore();

      for(int i = 0; i < stdList.size(); i++)
      {
         ifs.read((char*)&stdList[i].mID, sizeof(int));
         ifs.ignore();

         getline(ifs, stdList[i].mName);

         ifs.read((char*)&day, sizeof(day));
         ifs.ignore();
         ifs.read((char*)&month, sizeof(month));
         ifs.ignore();
         ifs.read((char*)&year, sizeof(year));
         ifs.ignore();
         ifs.read((char*)&stdList[i].mAvgScore, sizeof(double));
         ifs.ignore();

         stdList[i].mBirthday.SetDay(day);
         stdList[i].mBirthday.SetMonth(month);
         stdList[i].mBirthday.SetYear(year);
      }
      cout << "File has been read successfully";
      cin.get();
      cin.get();
   }
   ifs.close();
}

void StudentList::Input(void)
{
   int total;
   char keypressed;
   Student student;

   if(!stdList.empty())
   {
      cout << "Warning: All previous data in student list will be erased. Continue? (y/n): ";
      cin >> keypressed;
      Validate("Warning: All previous data in student list will be erased. Continue? (y/n): ", keypressed);

      while(keypressed != 'y' && keypressed != 'n')
      {
         cout << "Input wrong. Enter key again: ";
         cin.ignore(INT_MAX, '\n');
         cin >> keypressed;
      }
   }
   else
   {
      keypressed = 'y';
   }

   if(keypressed == 'y')
   {
      stdList.erase(stdList.begin(), stdList.end());

      cout << "Number of students: ";
      cin >> total;
      Validate("Number of students: ", total);

      for(int i = 0; i < total; i++)
      {
         cout << "_____________________________________________" << endl;

         cout << "ID: ";
         cin >> student.mID;
         Validate("ID: ", student.mID);
         ValidateID(student);

         cout << "Name: ";
         cin.ignore();
         getline(cin, student.mName);
         ValidateStr("Name: ", student.mName);

         cout << "Birthday: " << endl;
         student.mBirthday.Input();

         cout << "Average Score: ";
         cin >> student.mAvgScore;
         Validate("Average Score: ", student.mAvgScore);

         stdList.push_back(student);
      }

      cout << "Press Enter to continue";
      cin.get();
      cin.get();
   }
   else if(keypressed == 'n')
   {
      cout << "Canceled Operation. Press Enter to continue";
      cin.get();
      cin.get();
   }
}

void StudentList::Print(void)
{
   if(stdList.size() < 1)
   {
      cout << "There is no data available" << endl;
   }

   else
   {
      for(int i = 0; i < stdList.size(); i++)
      {
         cout << "_____________________________________________" << endl;
         cout << "ID: " << stdList[i].mID << endl;
         cout << "Name: " << stdList[i].mName << endl;
         cout << "Birthday: " << stdList[i].mBirthday << endl;
         cout << "Average Score: " << stdList[i].mAvgScore << endl;
      }
   }
   cout << "Press Enter to continue";
   cin.get();
   cin.get();
}

void StudentList::Add(void)
{
   Student student;

   cout << "ID: ";
   cin >> student.mID;
   Validate("ID: ", student.mID);
   ValidateID(student);

   cout << "Name: ";
   cin.ignore();
   getline(cin, student.mName);
   ValidateStr("Name: ", student.mName);

   cout << "Birthday: " << endl;
   student.mBirthday.Input();

   cout << "Average Score: ";
   cin >> student.mAvgScore;
   Validate("Average Score: ", student.mAvgScore);

   stdList.push_back(student);

   cout << "Updated successfully";
   cin.get();
   cin.get();
}

void StudentList::Update(void)
{
   if(stdList.empty())
   {
      cout << "Student list is empty. Please create new data first";
      cin.get();
      cin.get();
      return;
   }

   int ID;

   cout << "Enter ID of student to update: ";
   cin >> ID;
   Validate("Enter ID of student to update: ", ID);

   for(int i = 0 ; i < stdList.size(); i++)
   {
      if(ID == stdList[i].mID)
      {
         cout << endl;
         cout << "Student info: " << endl;
         cout << "ID: " << stdList[i].mID << endl;
         cout << "Name: " << stdList[i].mName << endl;
         cout << "Birthday: " << stdList[i].mBirthday << endl;
         cout << "Average Score: " << stdList[i].mAvgScore << endl << endl;

         int choice;
         cout << "Press 1 to update student's ID" << endl;
         cout << "Press 2 to update student's name" << endl;
         cout << "Press 3 to update student's birthday" << endl;
         cout << "Press 4 to update student's average score" << endl;
         cout << "Choice: ";
         cin >> choice;

         Validate("Choice: ", choice);

         while(choice != 1 && choice != 2 && choice != 3 && choice != 4)
         {
            cout << "Wrong input. Enter again" << endl;
            cout << "Choice: ";
            cin >> choice;
         }

         switch(choice)
         {
            case 1:
               cout << "New ID: ";
               cin >> stdList[i].mID;
               break;
            case 2:
               cout << "New name: ";
               cin.ignore();
               getline(cin, stdList[i].mName);
               break;
            case 3:
               cout << "New birthday: " << endl;
               stdList[i].mBirthday.Input();
               break;
            case 4:
               cout << "New score: ";
               cin >> stdList[i].mAvgScore;
               break;
         }
         if(choice == 2)
         {
            cout << "Info has been updated. Press Enter to continue" << endl;
            cin.get();
         }
         else
         {
            cout << "Info has been updated. Press Enter to continue" << endl;
            cin.get();
            cin.get();
         }
         return;
      }
   }
   cout << "There are no students with ID " << ID << endl;
   cin.get();
   cin.get();
   return;
}

void StudentList::DeleteOne(void)
{   
   if(stdList.empty())
   {
      cout << "There is no student in the list to delete";
      cin.get();
      cin.get();
      return;
   }

   int ID;

   cout << "Enter ID of student to update: ";
   cin >> ID;
   Validate("Enter ID of student to update: ", ID);

   for(int i = 0 ; i < stdList.size(); i++)
   {
      if(ID == stdList[i].mID)
      {
         stdList.erase(stdList.begin() + i);
         cout << "Student info has been deleted. Press Enter to continue" << endl;
         cin.get();
         cin.get();
         return;
      }
   }
   cout << "There are no students with ID " << ID << endl;
   cin.get();
   cin.get();
   return;

}

void StudentList::Delete(void)
{   
   if(stdList.empty())
   {
      cout << "There is no student in the list to delete";
      cin.get();
      cin.get();
      return;
   }

   char keypressed;
   cout << "Warning: All info about students will be erased. Continue? (y/n): ";
   cin >> keypressed;
   Validate("Warning: All info about students will be erased. Continue? (y/n): ", keypressed);

   while(keypressed != 'y' && keypressed != 'n')
   {
      cout << "Input wrong. Enter key again: ";
      cin.ignore(INT_MAX, '\n');
      cin >> keypressed;
   }
   if(keypressed == 'y')
   {
      stdList.erase(stdList.begin(), stdList.end());

      cout << "Student list has been deleted. Press Enter to continue" << endl;
      cin.get();
      cin.get();
      return;
   }
   else if(keypressed == 'n')
   {
      cout << "Canceled Operation. Press Enter to continue";
      cin.get();
      cin.get();
   }
}

void StudentList::Find()
{
   if(stdList.empty())
   {
      cout << "Student list is empty. Please create new data first";
      cin.get();
      cin.get();
      return;
   }

   int choice;
   cout << "Press 0 to find student by ID" << endl;
   cout << "Press 1 to find student by name" << endl;
   cout << "Choice: ";
   cin >> choice;

   Validate("Choice: ", choice);

   while(choice != 0 && choice != 1)
   {
      cout << "Wrong input. Enter again" << endl;
      cout << "Choice: ";
      cin >> choice;
   }

   switch(choice)
   {
      case 0:
         FindID();
         break;
      case 1:
         FindName();
         break;
   }
}

void StudentList::FindID(void)
{
   int id;

   cout << "Find student with ID: ";
   cin >> id;
   Validate("Find student with ID: ", id);

   for(int i = 0; i < stdList.size(); i++)
   {
      if(id == stdList[i].mID)
      {
         cout << "---Find result---" << endl;
         cout << "_____________________________________________" << endl;
         cout << "ID: " << stdList[i].mID << endl;
         cout << "Name: " << stdList[i].mName << endl;
         cout << "Birthday: " << stdList[i].mBirthday << endl;
         cout << "Average Score: " << stdList[i].mAvgScore << endl << endl;
         cout << "Press Enter to continue";
         cin.get();
         cin.get();
         return;
      }
   }
   cout << "There are no students with ID " << id << endl;
   cin.get();
   cin.get();
}

void StudentList::FindName(void)
{
   string name;
   bool flag = 0;
   cout << "Find student with name: ";
   cin.ignore();
   getline(cin, name);

   for(int i = 0; i < stdList.size(); i++)
   {
      if(name.compare(stdList[i].mName) == 0)
      {
         flag = 1;
         cout << "---File result---" << endl;
         cout << "_____________________________________________" << endl;
         cout << "ID: " << stdList[i].mID << endl;
         cout << "Name: " << stdList[i].mName << endl;
         cout << "Birthday: " << stdList[i].mBirthday << endl;
         cout << "Average Score: " << stdList[i].mAvgScore << endl;
      }
   }

   if(flag == 0)
   {
      cout << "There are no students with the name " << name << endl;
      cout << "Press Enter to continue";
   }
   else
   {
      cout << "Press Enter to continue";
   }
   cin.get();      
}

void StudentList::Sort()
{
   if(stdList.empty())
   {
      cout << "Student list is empty. Please create new data first";
      cin.get();
      cin.get();
      return;
   }

   int choice;
   cout << "Press 1 to sort student list by ID" << endl;
   cout << "Press 2 to sort student list by name" << endl;
   cout << "Press 3 to sort student list by average score" << endl;
   cout << "Choice: ";
   cin >> choice;

   Validate("Choice: ", choice);

   while(choice != 1 && choice != 2 && choice != 3)
   {
      cout << "Wrong input. Enter again" << endl;
      cout << "Choice: ";
      cin >> choice;
   }

   int left = 0;
   int right = stdList.size()-1;
   switch(choice)
   {
      case 1:
         SortID(left, right);
         break;
      case 2:
         {
            vector<string> nameList;
            string name;
            for(int i = 0; i < stdList.size(); i++)
            {
               name = GetName(stdList[i].mName);
               nameList.push_back(name);
            }
            SortName(left, right, nameList);
            break;
         }
      case 3:
         SortScore();
         break;
   }

   cout << "Sort done. Enter to continue";
   cin.get();
   cin.get();
}

void StudentList::SortID(int left, int right)
{
   int i, j, x;

   x = stdList[(left + right) / 2].mID;
   i = left;
   j = right;

   while(stdList[i].mID < x) 
      i++;
   while(stdList[j].mID > x)
      j--;
   if(i <= j)
   {
      swap(stdList[i].mID, stdList[j].mID);
      i++;
      j--;
   }
   if (left < j)
      SortID(left, j);
   if (right > i)
      SortID(i, right);
}

void StudentList::SortName(int left, int right, vector<string> &nameList)
{
   int i, j;
   string x;

   x = nameList[(left + right) / 2];
   i = left;
   j = right;

   while(nameList[i] < x) 
      i++;
   while(nameList[j] > x)
      j--;
   if(i <= j)
   {
      swap(stdList[i].mName, stdList[j].mName);
      swap(nameList[i], nameList[j]);
      i++;
      j--;
   }
   if (left < j)
      SortName(left, j, nameList);
   if (right > i)
      SortName(i, right, nameList);
}

bool Compare(const Student &x, const Student &y)
{
   return x.mAvgScore < y.mAvgScore;
}

void StudentList::SortScore()
{
   sort(stdList.begin(), stdList.end(), Compare);
}

string StudentList::GetName(string str)
{
   string name;
   int begin;

   //remove trailling whitespace
   while(isspace(str.back()))
   {
      str.pop_back();
   }

   for(int i = str.size()-1;; i--)
   {
      if(str[i] == ' ')
      {
         begin = i + 1;
         break;
      }
      if(str[i] != ' ' && i == 0)
      {
         return str;
      }
   }
   return str.substr(begin, str.size() - begin);
}

void StudentList::ValidateStr(string redoMsg, string reassignVar)
{
   while(true)
   {
      if(cin.fail())
      {
         cin.clear();
         cin.ignore(INT_MAX, '\n');
         cout << "Wrong input. Enter again" << endl;
         cout << redoMsg;
         getline(cin, reassignVar);
         cin.ignore();
      }
      else
      {
         break;
      }
   }
}

void StudentList::ValidateID(Student &st)
{
   for(int i = 0; i < stdList.size(); i++)
   {
      while(st.mID == stdList[i].mID)
      {
         cout << "ID is not unique. Enter again" << endl;
         cout << "ID: ";
         cin >> st.mID;
         i = 0;
      }
   }
}
