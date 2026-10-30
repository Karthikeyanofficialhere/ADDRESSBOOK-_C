                                          Address Book – C Programming Project

Overview

Address Book is a menu-driven contact management application developed using C as part of my Advanced C programming training at Emertxe Information Technologies.
The application allows users to manage contact details such as names, phone numbers, and email addresses. It supports creating, searching, editing, deleting, and listing contacts.
Contact information is stored in a text file, allowing the data to be loaded again when the application is restarted.

Features

- Create Contact: Add a new contact with name, phone number, and email address.
- Search Contact: Search for contacts using a keyword.
- Search Result Highlighting: Highlight matching text in the search results.
- Edit Contact: Modify the details of an existing contact.
- Delete Contact: Remove a contact from the address book.
- List Contacts: Display all stored contacts.
- File Handling: Save and retrieve contact information using a file.

Technologies Used

- Programming Language: C
- Compiler: GCC
- Code Editor: Visual Studio Code
- Environment: WSL

Concepts Applied

- Structures and arrays of structures
- Pointers
- Functions
- String handling
- Header files
- Modular programming
- File handling
- Input validation

Project Structure

Address-Book/
│
├── main.c
├── contact.c
├── contact.h
├── contacts.txt
├── README.md
├── .gitignore

Compilation and Execution

Prerequisites

- GCC compiler
- VS Code or any C-compatible code editor
- WSL or a Linux environment (if using the commands below)

Compile

```bash
gcc main.c contact.c -o address_book
```

Run

```bash
./address_book
```

Application Menu

The application provides the following operations:

1. Create Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Exit

Learning Outcomes

Through this project, I gained practical experience in:

- Organising a C application using multiple source and header files.
- Working with structures, pointers, and functions.
- Managing contact records using file handling.
- Implementing search and contact management operations.
- Debugging and testing a menu-driven application.

Future Enhancements

- Improve phone number and email validation.
- Enhance duplicate-contact handling.
- Explore database integration.
- Develop a graphical user interface.

Author

**Karthikeyan Eswaran**

Embedded Systems Trainee | Emertxe Information Technologies

