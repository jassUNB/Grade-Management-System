## Grade-Management-System

⸻


📌 Project Overview

The Student Grade Management System is a console-based C application designed for efficiently managing student academic records. It offers robust features for adding, updating, displaying, sorting, and persisting student data, with a user-friendly menu-driven interface.

⸻

## Features

## Student Record Management
	-       Add students with validated 7-digit unique IDs.
	-	Store names and grades for 5 subjects.
	-	Automatic GPA calculation upon entry.

## Search & Update
	•	Search student data by ID.
	•	Update grades and GPA by ID or name.

📂 Data Persistence
	•	Save/load records using structured CSV files.
	•	Auto-handling of headers and formatting.

🔃 Sorting
	•	Sort student list by:
	•	ID
	•	Name
	•	GPA
	•	Efficient in-place QuickSort on a linked list.

📊 Visualization
	•	Bar chart for:
	•	GPA distribution of all students.
	•	Subject-wise grades of a selected student.

⸻

💻 Technologies Used
	•	Language: C
	•	Data Structures: Structs, Arrays, Linked Lists
	•	File Handling: CSV Read/Write
	•	Sorting: Recursive QuickSort (in-place)
	•	Memory Management: malloc, free with Valgrind validation

⸻

🚀 How to Compile & Run
	1.	Ensure main.c, student.c, and student.h are in the same directory.
	2.	Compile using:

gcc main.c student.c -o output


	3.	Run the progom

./output



⸻

📋 Menu Options
	1.	Add a Student
	2.	Display All Students
	3.	Save and Exit
	4.	Sort Students (by ID / Name / GPA)
	5.	Search for a Student
	6.	Print GPA Bar Chart
	7.	Update GPA – by ID
	8.	Update GPA – by Name
	9.	Remove a Student

⸻

✅ Input Validation
	•	Valid 7-digit unique Student IDs
	•	Grades must be between 0 and 100
	•	No duplicate entries allowed

⸻

🧪 Testing & Debugging
	•	Edge Cases:
	•	Empty records
	•	Corrupted CSV files
	•	GPA on boundary grades
	•	Memory:
	•	Verified with Valgrind to ensure no leaks

⸻

🧠 Challenges & Lessons Learned
	•	Implementing QuickSort for linked lists
	•	Managing dynamic memory and avoiding leaks
	•	Parsing edge cases in CSV files

⸻

🔮 Future Improvements
	•	GUI or Web-based interface
	•	Error recovery for corrupted files
	•	User roles and login systems
	•	Data encryption for privacy

⸻

📌 Conclusion

The project successfully demonstrates fundamental and advanced C programming concepts. It is a reliable system for student academic management with structured data handling, visual feedback, and safe memory practices.

